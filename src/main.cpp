#include <iostream>
#include <cstring>
#include <thread>
#include "golfMembershipManager.h"
#include "MembersEntity.h"
#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "MembersEntity.h"
#include "ComDev.h"
#include "tcpServer.h"

void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccpet() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {        
            recvBuff[recvLen+1] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);   
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
    }
}

int main(void)
{
    tcpServer *cardtcpserver = new tcpServer(5100);
    ComDev *comdev = new ComDev(cardtcpserver);
    MembersManageService *membersmanagerservice = new MembersManageService(comdev);
    Controller *controller = new Controller(membersmanagerservice);
    Listener *listener = new Listener(controller);
    std::thread threadFunc(serverThread, cardtcpserver);
    // golfMembershipManager golfMembershipManager;
    // golfMembershipManager.run();
    while(1)
    {
        listener->checkEvent();
        delay(50);
    }
    
    return 0;
}
