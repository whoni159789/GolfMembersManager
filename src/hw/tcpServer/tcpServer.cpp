#include "tcpServer.h"

tcpServer::tcpServer(int port)
{
    portNum = port;
    clientState = false;
    createSocket();
}

tcpServer::~tcpServer()
{
    close(serverSocket_fd);
}

int tcpServer::getServerSocket()
{
    return serverSocket_fd;
}

int tcpServer::getClientSocket()
{
    return clientSocket_fd;
}

void tcpServer::createSocket()
{
    if((serverSocket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket()");
        return;
    }
    
    int option = 1;
    setsockopt(serverSocket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // INADDR_ANY : All Local IP
    server_addr.sin_port = htons(portNum);

    if(bind(serverSocket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind()");
        return;
    }

    if(listen(serverSocket_fd, 8) < 0)
    {
        perror("listen()");
        return;
    }
}

int tcpServer::waitAccpet()
{
    client_addr_size = sizeof(client_addr);

    clientSocket_fd = accept(serverSocket_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if(clientSocket_fd < 0)
    {
        perror("accept() error\n");
        return -1;
    }

    inet_ntop(AF_INET, &client_addr.sin_addr, mesg, BUFSIZ);
    printf("Client is connected : %s\n", mesg);

    return clientSocket_fd;
}

int tcpServer::recvData(char *recvBuff, size_t size)
{
    int len = read(clientSocket_fd, recvBuff, size);
    return len;
}

int tcpServer::sendData(char *sendBuff, size_t size)
{
    if(!getClientState())   return -1;

    int len = write(clientSocket_fd, sendBuff, size);
    return len;
}

void tcpServer::closeSocket(int socket)
{
    close(socket);
}

bool tcpServer::getClientState()
{
    return clientState;
}

void tcpServer::setClientState(bool state)
{
    clientState = state;
}