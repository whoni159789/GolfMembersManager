#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once

#include "DeviceData.h"
#include "MembersManageService.h"

class Controller
{
private:
    MembersManageService *membersmanageservice;

public:
    Controller(MembersManageService *membersmanageservice);
    ~Controller();
    void updateEvent(DeviceData data);
    
};

#endif