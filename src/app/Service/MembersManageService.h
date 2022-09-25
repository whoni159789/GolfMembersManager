#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "View.h"
#include "ComDev.h"
#include "CardState.h"
#include "SetState.h"

class MembersManageService
{
private:
    int membersManagerState;
    int memberSetState;
    MembersEntity *membersentity;
    View *view;
    ComDev *comdev;

public:
    MembersManageService(ComDev *comdev);
    ~MembersManageService();
    void updateModeStateEvent(std::string devName);
    void updateSetStateEvent(std::string devName);
    void updateResetEvent(std::string devName);
    void checkCard(int *cardNum);
    void updateSaveEvent(std::string devName);
};

#endif