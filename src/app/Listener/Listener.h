#ifndef LISTENER_H
#define LISTENER_H

#pragma once

#include "CardReader.h"
#include "ManageButton.h"
#include "Controller.h"

class Listener
{
private:
    CardReader *rfid;
    ManageButton *modeButton;
    ManageButton *checkButton;
    ManageButton *resetButton;
    ManageButton *saveButton;
    Controller *controller;
    uint8_t rfidData[16];

public:
    Listener(Controller *controller);
    ~Listener();
    void checkEvent();
    bool checkRFID();

};

#endif