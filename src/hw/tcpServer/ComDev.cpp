#include "ComDev.h"
#include <thread>



ComDev::ComDev(tcpServer *cardTCPServer)
{
    this->cardTCPServer = cardTCPServer;
}

ComDev::~ComDev()
{
    delete cardTCPServer;
}

void ComDev::sendData(int *cardNum)
{
    char sendBuff[1000];
    sprintf(sendBuff, "%02x-%02x-%02x-%02x-%02x", cardNum[0], cardNum[1], cardNum[2], cardNum[3], cardNum[4]);
    cardTCPServer->sendData(sendBuff, strlen(sendBuff));
}