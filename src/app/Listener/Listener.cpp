#include "Listener.h"
#include <string.h>

Listener::Listener()
{
    rfid = new CardReader(new SPI(10, 3000000));
    modeButton = new ManageButton(27, "ModeButton");
    checkButton = new ManageButton(28, "CheckButton");
    controller = new Controller();
}

Listener::~Listener(){}

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
