#include "MembersManageService.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

MembersManageService::MembersManageService()
{
    membersentity = new MembersEntity();
    membersManagerState = CARD_READER;
    view = new View();
    view->lcdView();
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
                view->setViewState(membersManagerState);
            }
            view->lcdView();
        break;

        case CARD_REGISTER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REMOVER;
                printf("Changed to CARD_REMOVER State\n");
                view->setViewState(membersManagerState);
            }
            view->lcdView();
        break;

        case CARD_REMOVER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                printf("Changed to CARD_READER State\n");
                view->setViewState(membersManagerState);
            }
            view->lcdView();
        break;

        case CARD_MODIFIER:

        break;
    }
}

void MembersManageService::checkCard(int *cardNum)
{
    static int idCount = 100001;

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
            tempMember.id = idCount;
            std::cout << "Name : ";
            std::cin >> tempMember.name;
            std::cout << "Address : ";
            std::cin >> tempMember.address;
            std::cout << "PhoneNumber : ";
            std::cin >> tempMember.phoneNumber;
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            membersentity->addMemberInfo(tempMember);
            std::cout << tempMember.name << " Registered!!\n"; 
            idCount++;
        break;

        case CARD_REMOVER:
            membersentity->delMeberInfo(cardNum);
            printf("%s Removed!\n", tempMember.name);
        break;

        case CARD_MODIFIER:

        break;
    }
}