#include "View.h"

View::View()
{
    lcd = new LCD(new I2C("/dev/i2c-1", 0x25));
    viewState = CARD_READER;
}

View::~View() {}

void View::setViewState(int state)
{
    viewState = state;
}

void View::lcdView()
{
    switch(viewState)
    {
        case CARD_READER:
            lcd->WriteStringXY(0, 0, " MembersManager ");
            lcd->WriteStringXY(1, 0, "MODE : READER   ");
        break;

        case CARD_REGISTER:
            lcd->WriteStringXY(0, 0, " MembersManager ");
            lcd->WriteStringXY(1, 0, "MODE : REGISTER ");
        break;

        case CARD_REMOVER:
            lcd->WriteStringXY(0, 0, " MembersManager ");
            lcd->WriteStringXY(1, 0, "MODE : REMOVER  ");
        break;

        case CARD_MODIFIER:

        break;
    }
}