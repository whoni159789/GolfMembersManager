#include "Controller.h"
#include <iostream>

Controller::Controller(MembersManageService *membersmanageservice)
{
    this->membersmanageservice = membersmanageservice;
}

Controller::~Controller()
{
    delete membersmanageservice;
}

void Controller::updateEvent(DeviceData data)
{
    if(data.devName == "CardReader")
    {
        int cardNumber[5];
        for(int i=0; i<5; i++)
            cardNumber[i] = data.devData[i];
        membersmanageservice->checkCard(cardNumber);
    }

    if(data.devName == "ModeButton")
    {
        membersmanageservice->updateModeStateEvent(data.devName);
    }

    if(data.devName == "CheckButton")
    {
        membersmanageservice->updateSetStateEvent(data.devName);
    }

    if(data.devName == "ResetButton")
    {
        membersmanageservice->updateResetEvent(data.devName);
    }

    if(data.devName == "SaveButton")
    {
        membersmanageservice->updateSaveEvent(data.devName);
    }


}