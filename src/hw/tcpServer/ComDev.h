#ifndef COMDEV_H
#define COMDEV_H

#pragma once

#include "tcpServer.h"

class ComDev
{
private:
    tcpServer *cardTCPServer;

public:
    ComDev(tcpServer *cardTCPServer);
    ~ComDev();
    void sendData(int *cardNum);
};

#endif