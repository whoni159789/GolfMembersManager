#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "View.h"
#include "CardState.h"

class MembersManageService
{
private:
    int membersManagerState;
    MembersEntity *membersentity;
    View *view;

public:
    MembersManageService();
    ~MembersManageService();
    void updateStateEvnet(std::string devName);
    void checkCard(int *cardNum);

};

#endif