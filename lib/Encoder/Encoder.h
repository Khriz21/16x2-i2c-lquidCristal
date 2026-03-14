#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
private:
    uint8_t pinCLK;
    uint8_t pinDT;
    uint8_t pinSW;

    static Encoder *instance;
    static void isrMovement();
    static void isrSW();

    volatile int32_t position = 0;
    volatile bool buttonClicked = false;
    volatile unsigned long lastInterrupTime;
    unsigned long lastButtonPress = 0;

public:
    Encoder(uint8_t clk, uint8_t dt, uint8_t sw);

    void begin();

    int32_t getDelta();
    bool wasClicked();
};

#endif