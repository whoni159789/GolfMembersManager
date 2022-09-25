#include "Listener.h"
#include <string.h>

Listener::Listener(Controller *controller)
{
    rfid = new CardReader(new SPI(10, 3000000));
    modeButton = new ManageButton(27, "ModeButton");
    checkButton = new ManageButton(28, "CheckButton");
    resetButton = new ManageButton(29, "ResetButton");
    saveButton = new ManageButton(6, "SaveButton");
    this->controller = controller;
}

Listener::~Listener()
{
    delete rfid;
    delete modeButton;
    delete checkButton;
    delete controller;
}

// CardReader(mfrc522) & ManageButton(Button) -> Listener -> Controller
void Listener::checkEvent()
{
    if(checkRFID())
    {
        controller->updateEvent(rfid->getCardNumber());
    }
    if(modeButton->checkButton())
    {
        controller->updateEvent(modeButton->getButtonData());
    }
    if(checkButton->checkButton())
    {
        controller->updateEvent(checkButton->getButtonData());
    }
    if(resetButton->checkButton())
    {
        controller->updateEvent(resetButton->getButtonData());
    }
    if(saveButton->checkButton())
    {
        controller->updateEvent(saveButton->getButtonData());
    }

}

// CardReader(mfrc522) -> Listener
bool Listener::checkRFID()
{
    static unsigned int prevCheckTime = 0;

    if(millis() - prevCheckTime < 1000)
        return false;

    prevCheckTime = millis();

    if(rfid->isCard())  return true;

    return false;
}
