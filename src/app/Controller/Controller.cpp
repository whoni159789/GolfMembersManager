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
        membersmanageservice->updateStateEvnet(data.devName);
    }

    if(data.devName == "CheckButton")
    {
        membersmanageservice->updateStateEvnet(data.devName);
    }
}