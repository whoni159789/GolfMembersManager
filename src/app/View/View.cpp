#include "View.h"

View::View()
{
    modelcd = new LCD(new I2C("/dev/i2c-1", 0x25));
    setlcd = new LCD(new I2C("/dev/i2c-0", 0x27));
    modeState = CARD_INIT;
    setState = SET_OFF;
}

View::~View() 
{
    delete modelcd;
    delete setlcd;
}

void View::setModeState(int state)
{
    modeState = state;
}

void View::setSetState(int state)
{
    setState = state;
}

void View::setName(char* name)
{
    Name = name;
}

void View::lcdInitView()
{
    modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER  ");
    modelcd->WriteStringXY(1, 0, "PUSH MODE BTN   ");
    setlcd->WriteStringXY(0, 0, "                ");
    setlcd->WriteStringXY(1, 0, "                ");
}

void View::lcdModeView()
{
    switch(modeState)
    {
        case CARD_READER:
            modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER ");
            modelcd->WriteStringXY(1, 0, "MODE : READER   ");
        break;

        case CARD_REGISTER:
            modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER ");
            modelcd->WriteStringXY(1, 0, "MODE : REGISTER ");
        break;

        case CARD_REMOVER:
            modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER ");
            modelcd->WriteStringXY(1, 0, "MODE : REMOVER  ");
        break;

        case CARD_MODIFIER:
            modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER ");
            modelcd->WriteStringXY(1, 0, "MODE : MODIFIER ");
        break;

        case CARD_SAVE:
            modelcd->WriteStringXY(0, 0, "MEMBERS MANAGER ");
            modelcd->WriteStringXY(1, 0, "MODE : SAVE     ");
        break;
    }
}

void View::lcdSetView()
{
    /* modeState : CARD_READER*/
    if(modeState == CARD_READER && setState == SET_OFF)
    {
        setlcd->WriteStringXY(0, 0, "MODE SELECTION  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }
    else if(modeState == CARD_READER && setState == SET_READY)
    {
        setlcd->WriteStringXY(0, 0, "MODE : READER   ");
        setlcd->WriteStringXY(1, 0, "SWIPE THE CARD  ");
    }
    else if(modeState == CARD_READER && setState == SET_RUN_NORMAL)
    {
        lcdSetClear();
        setlcd->WriteStringXY(0, 0, "HELLO OUR MEMBER");
        char buf[40];
        sprintf(buf, "%s", Name);
        setlcd->WriteStringXY(1, 0, buf);
    }
    else if(modeState == CARD_READER && setState == SET_RUN_ERROR)
    {
        setlcd->WriteStringXY(0, 0, "NOT REGISTERED ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }

    /* modeState : CARD_REGISTER*/
    if(modeState == CARD_REGISTER && setState == SET_OFF)
    {
        setlcd->WriteStringXY(0, 0, "MODE SELECTION  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }
    else if(modeState == CARD_REGISTER && setState == SET_READY)
    {
        setlcd->WriteStringXY(0, 0, "MODE : REGISTER ");
        setlcd->WriteStringXY(1, 0, "SWIPE THE CARD  ");
    }
    else if(modeState == CARD_REGISTER && setState == SET_RUN)
    {
        setlcd->WriteStringXY(0, 0, "ENTER YOUR INFO ");
        setlcd->WriteStringXY(1, 0, "NAME, ADDR, TEL ");
    }
    else if(modeState == CARD_REGISTER && setState == SET_RUN_NORMAL)
    {
        lcdSetClear();
        setlcd->WriteStringXY(0, 0, "WELCOME MEMBER!");
        char buf[40];
        sprintf(buf, "%s", Name);
        setlcd->WriteStringXY(1, 0, buf);
    }
    else if(modeState == CARD_REGISTER && setState == SET_RUN_ERROR)
    {
        setlcd->WriteStringXY(0, 0, "ALREADY MEMBER  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }

    /* modeState : CARD_REMOVER*/
    if(modeState == CARD_REMOVER && setState == SET_OFF)
    {
        setlcd->WriteStringXY(0, 0, "MODE SELECTION  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }
    else if(modeState == CARD_REMOVER && setState == SET_READY)
    {
        setlcd->WriteStringXY(0, 0, "MODE : REMOVER  ");
        setlcd->WriteStringXY(1, 0, "SWIPE THE CARD  ");
    }
    else if(modeState == CARD_REMOVER && setState == SET_RUN_NORMAL)
    {
        lcdSetClear();
        setlcd->WriteStringXY(0, 0, "DELETED MEMBER  ");
        char buf[40];
        sprintf(buf, "%s", Name);
        setlcd->WriteStringXY(1, 0, buf);
    }
    else if(modeState == CARD_REMOVER && setState == SET_RUN_ERROR)
    {
        setlcd->WriteStringXY(0, 0, "NOT REGISTERED  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }

    /* modeState : CARD_MODIFIER*/
    if(modeState == CARD_MODIFIER && setState == SET_OFF)
    {
        setlcd->WriteStringXY(0, 0, "MODE SELECTION  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }
    else if(modeState == CARD_MODIFIER && setState == SET_READY)
    {
        setlcd->WriteStringXY(0, 0, "MODE : MODIFIER ");
        setlcd->WriteStringXY(1, 0, "SWIPE THE CARD  ");
    }
    else if(modeState == CARD_MODIFIER && setState == SET_RUN)
    {
        setlcd->WriteStringXY(0, 0, "ENTER YOUR INFO ");
        setlcd->WriteStringXY(1, 0, "NAME, ADDR, TEL ");
    }
    else if(modeState == CARD_MODIFIER && setState == SET_RUN_NORMAL)
    {
        setlcd->WriteStringXY(0, 0, "YOUR INFO UPDATE");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }
    else if(modeState == CARD_MODIFIER && setState == SET_RUN_ERROR)
    {
        setlcd->WriteStringXY(0, 0, "NOT REGISTERED  ");
        setlcd->WriteStringXY(1, 0, "PUSH CHECK BTN  ");
    }

    /* modeState : CARD_MODIFIER*/
    if(modeState == CARD_SAVE && setState == SET_OFF)
    {
        setlcd->WriteStringXY(0, 0, "FOR FILE SAVE   ");
        setlcd->WriteStringXY(1, 0, "PUSH SAVE BTN   ");
    }
}

void View::lcdSetClear()
{
    setlcd->WriteStringXY(0, 0, "                ");
    setlcd->WriteStringXY(1, 0, "                ");
}