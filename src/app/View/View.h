#ifndef VIEW_H
#define VIEW_H

#pragma once

#include "LCD.h"
#include "CardState.h"
#include "SetState.h"

class View
{
private:
    LCD *modelcd;
    LCD *setlcd;
    int modeState;
    int setState;
    char* Name;

public:
    View();
    ~View();
    void setModeState(int state);
    void setSetState(int state);
    void setName(char* name);
    void lcdInitView();
    void lcdModeView();
    void lcdSetView();
    void lcdSetClear();

};

#endif