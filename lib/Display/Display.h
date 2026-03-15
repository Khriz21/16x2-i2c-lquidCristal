#ifndef DISPLAY_H
#define DISPLAY_H

#include<Arduino.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include"Menu.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
class Display
{
private:
    /* data */
public:
    Display(/* args */);
    ~Display();
};

Display::Display(/* args */)
{
}

Display::~Display()
{
}


#endif