#ifndef TCPSERVER_H
#define TCPSERVER_H

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

class tcpServer
{
private:
    int serverSocket_fd;
    int clientSocket_fd;
    int portNum;
    bool clientState;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;

    char mesg[BUFSIZ];

public:
    tcpServer(int port);
    ~tcpServer();
    int getServerSocket();
    int getClientSocket();
    bool getClientState();
    void setClientState(bool state);
    void createSocket();
    int waitAccpet();
    int recvData(char *recvBuff, size_t size);
    int sendData(char *recvBuff, size_t size);
    void closeSocket(int socket);
    


};

#endif