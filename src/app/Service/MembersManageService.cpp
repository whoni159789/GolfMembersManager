#include "MembersManageService.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

MembersManageService::MembersManageService(ComDev *comdev)
{
    membersentity = new MembersEntity();
    membersManagerState = CARD_READER;
    view = new View();
    view->lcdView();
    this->comdev = comdev;
}

MembersManageService::~MembersManageService() 
{
    delete membersentity;
    delete view;
    delete comdev;
}

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
                membersManagerState = CARD_MODIFIER;
                printf("Changed to CARD_MODIFIER State\n");
                view->setViewState(membersManagerState);
            }
            view->lcdView();
        break;

        case CARD_MODIFIER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                printf("Changed to CARD_READER State\n");
                view->setViewState(membersManagerState);
            }
            view->lcdView();
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
                comdev->sendData(cardNum);
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
            if(!membersentity->findMemberInfo(cardNum))
                printf("Not Registered Card!\n");
            membersentity->searchMemberInfo(cardNum);
            if(membersentity->delMeberInfo(cardNum))
                printf(" Removed!\n");
        break;

        case CARD_MODIFIER:
            membersentity->modifyMemberInfo(cardNum);
        break;
    }
}