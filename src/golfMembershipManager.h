#ifndef GOLFMEMBERSHIPMANAGER_H
#define GOLFMEMBERSHIPMANAGER_H

#pragma once

#include "Listener.h"
#include "View.h"

class golfMembershipManager
{
private:
    Listener *listener;

public:
    golfMembershipManager();
    ~golfMembershipManager();
    void run();
};

#endif