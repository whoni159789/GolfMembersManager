#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#pragma once

#include <string>
#include "MembersEntity.h"
#include "MemberInfo.h"

enum {CARD_READER, CARD_REGISTER};

class MembersManageService
{
private:
    int membersManagerState;
    MembersEntity *membersentity;

public:
    MembersManageService();
    ~MembersManageService();
    void updateStateEvnet(std::string devName);
    void checkCard(int *cardNum);

};

#endif