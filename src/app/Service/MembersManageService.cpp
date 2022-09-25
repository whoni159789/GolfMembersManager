#include "MembersManageService.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

MembersManageService::MembersManageService(ComDev *comdev)
{
    membersentity = new MembersEntity();
    membersManagerState = CARD_INIT;
    memberSetState = SET_OFF;
    view = new View();
    view->lcdInitView();
    this->comdev = comdev;
}

MembersManageService::~MembersManageService() 
{
    delete membersentity;
    delete view;
    delete comdev;
}

void MembersManageService::updateModeStateEvent(std::string devName)
{
    if(memberSetState != SET_OFF)   return;

    switch(membersManagerState)
    {
        case CARD_INIT:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                view->setModeState(membersManagerState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;

        case CARD_READER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REGISTER;
                view->setModeState(membersManagerState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;

        case CARD_REGISTER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_REMOVER;
                view->setModeState(membersManagerState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;

        case CARD_REMOVER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_MODIFIER;
                view->setModeState(membersManagerState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;

        case CARD_MODIFIER:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_SAVE;
                view->setModeState(membersManagerState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;

        case CARD_SAVE:
            if(devName == "ModeButton")
            {
                membersManagerState = CARD_READER;
                view->setModeState(membersManagerState);
                view->setSetState(memberSetState);
                view->lcdModeView();
                view->lcdSetView();
            }
        break;
    }
}

void MembersManageService::updateSetStateEvent(std::string devName)
{
    if(membersManagerState == CARD_SAVE) return;

    switch(memberSetState)
    {
        case SET_OFF:
            if(devName == "CheckButton")
            {
                memberSetState = SET_READY;
                view->setSetState(memberSetState);
            }
            view->lcdSetView();
        break;

        case SET_RUN_ERROR:
            if(devName == "CheckButton")
            {
                memberSetState = SET_OFF;
                view->setSetState(memberSetState);
            }
            view->lcdSetView();
        break;

        case SET_RUN_NORMAL:
            if(devName == "CheckButton")
            {
                memberSetState = SET_OFF;
                view->setSetState(memberSetState);
            }
            view->lcdSetView();
        break;
    }
}

void MembersManageService::updateResetEvent(std::string devName)
{
    if(devName == "ResetButton")
    {
        membersManagerState = CARD_READER;
        memberSetState = SET_OFF;
        view->setModeState(membersManagerState);
        view->setSetState(memberSetState);
        view->lcdModeView();
        view->lcdSetView();
    }
}

void MembersManageService::checkCard(int *cardNum)
{
    char* tempName;
    switch(membersManagerState)
    {
        case CARD_READER:

            switch(memberSetState)
            {
                case SET_READY:
                    if(!membersentity->findMemberInfo(cardNum))
                    {
                        memberSetState = SET_RUN_ERROR;             // LCD State
                        view->setSetState(memberSetState);          // LCD
                        view->lcdSetView();
                        return;
                    }

                    tempName = membersentity->searchMemberName(cardNum);
                    membersentity->printMemberInfo(cardNum);    // Monitor
                    comdev->sendData(cardNum);                  // Server -> Client
                    memberSetState = SET_RUN_NORMAL;            // LCD State
                    view->setName(tempName);
                    view->setSetState(memberSetState);          // LCD
                    view->lcdSetView();                         // LCD
                break;
            }
        break;

        case CARD_REGISTER:

            switch(memberSetState)
            {
                case SET_READY:
                    if(membersentity->findMemberInfo(cardNum))
                    {
                        memberSetState = SET_RUN_ERROR;
                        view->setSetState(memberSetState);
                        view->lcdSetView();
                        return;
                    }

                    memberSetState = SET_RUN;
                    view->setSetState(memberSetState);
                    view->lcdSetView();
                    membersentity->registerMember(cardNum);
                    tempName = membersentity->searchMemberName(cardNum);
                    view->setName(tempName);
                    memberSetState = SET_RUN_NORMAL;
                    view->setSetState(memberSetState);
                    view->lcdSetView();
                break;
            }
        break;

        case CARD_REMOVER:
            switch(memberSetState)
            {
                case SET_READY:
                    if(!membersentity->findMemberInfo(cardNum))
                    {
                        memberSetState = SET_RUN_ERROR;
                        view->setSetState(memberSetState);
                        view->lcdSetView();
                        return;
                    }
                    view->lcdSetClear();
                    tempName = membersentity->searchMemberName(cardNum);
                    view->setName(tempName);
                    memberSetState = SET_RUN_NORMAL;
                    view->setSetState(memberSetState);
                    view->lcdSetView();
                    membersentity->delMeberInfo(cardNum);

                break;
            }
        break;

        case CARD_MODIFIER:
            switch(memberSetState)
            {
                case SET_READY:
                    if(!membersentity->findMemberInfo(cardNum))
                    {
                        memberSetState = SET_RUN_ERROR;
                        view->setSetState(memberSetState);
                        view->lcdSetView();
                        return;
                    }

                    memberSetState = SET_RUN;
                    view->setSetState(memberSetState);
                    view->lcdSetView();

                    membersentity->modifyMemberInfo(cardNum);
                    memberSetState = SET_RUN_NORMAL;
                    view->setSetState(memberSetState);
                    view->lcdSetView();
                break;
            }
        break;
    }
}

void MembersManageService::updateSaveEvent(std::string devName)
{
    if(membersManagerState == CARD_SAVE && memberSetState == SET_OFF)
    {
        if(devName == "SaveButton")
        {
            std::cout << "\nmemberLists.txt, memberLists.bin Update!!\n";
            membersentity->memoryToDB();
        }
    }   
}