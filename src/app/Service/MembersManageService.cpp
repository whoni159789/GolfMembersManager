#include "MembersManageService.h"
#include <stdio.h>
#include <cstring>

MembersManageService::MembersManageService()
{
    membersentity = new MembersEntity();
    membersManagerState = CARD_READER;
}

MembersManageService::~MembersManageService() {}

void MembersManageService::updateStateEvnet(std::string devName)
{
    switch(membersManagerState)
    {
        case CARD_READER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REGISTER;
                printf("Changed to CARD_REGISTER State\n");
            }
        break;

        case CARD_REGISTER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                printf("Changed to CARD_READER State\n");
            }
        break;
    }
}

void MembersManageService::checkCard(int *cardNum)
{
    switch(membersManagerState)
    {
        case CARD_READER:
            if(membersentity->findMemberInfo(cardNum))
            {
                printf("Registered Member\n");
                membersentity->printMemberInfo(cardNum);
            }
            else
            {
                printf("Not Registered Member\n");
            }
        break;

        case CARD_REGISTER:
            MemberInfo tempMember;
            tempMember.id = 100001;
            strcpy(tempMember.name, "LeeSoonSin");
            strcpy(tempMember.address, "LotteTower 100dong-10000ho");
            strcpy(tempMember.phoneNumber, "010-1234-5678");
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));

            membersentity->addMemberInfo(tempMember);
            printf("Member Registered!\n");   
        break;
    }
}