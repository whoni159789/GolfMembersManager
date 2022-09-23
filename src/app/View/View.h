#ifndef VIEW_H
#define VIEW_H

#pragma once

#include "LCD.h"
#include "CardState.h"

class View
{
private:
    LCD *lcd;
    int viewState;

public:
    View();
    ~View();
    void setViewState(int state);
    void lcdView();

};

#endif