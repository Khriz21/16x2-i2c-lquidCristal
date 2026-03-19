#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../../include/PinConfig.h"

#include "Display.h"
#include "Menu.h"
#include "Encoder.h"
#include "MenuItem.h"

class App
{
private:
    LiquidCrystal_I2C _lcd;
    Display _display;
    Menu _menu;

    Encoder _encoder;
    

    enum AppMode
    {
        HOME_SCREEN,
        MAIN_MENU,
        SET_TEMPERATURE,
        SET_SPEED
    } 
    _appMode;

    MenuItem _motorItem;
    MenuItem _heaterItem;
    MenuItem _setTempItem;
    MenuItem _setSpeedItem;
    MenuItem _tuningPIDItem;
    MenuItem _exitItem;

    uint8_t _targetTemperature;
    uint8_t _targetSpeed;

    static App *_instance;

    void handleUI();

    static void onSetToggle();
    static void onSetUpdateValue();
    static void onSetAction();


public:
    App();
    void begin();
    void run();
};

#endif