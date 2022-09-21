#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once

#include "DeviceData.h"
#include "Monitor.h"
#include "MembersManageService.h"

class Controller
{
private:
    Monitor *monitor;
    MembersManageService *membersmanageservice;

public:
    Controller();
    ~Controller();
    void updateEvent(DeviceData data);
    
};

#endif