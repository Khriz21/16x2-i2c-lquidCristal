#include "Encoder.h"

Encoder *Encoder::instance = nullptr;
Encoder::Encoder(uint8_t clk, uint8_t dt, uint8_t sw)
    : pinCLK(clk), pinDT(dt), pinSW(sw)
{
    instance = this;
}

//? <=====Iniciar Pines he interruptor de tiempo=====>
void Encoder::begin()
{
    pinMode(pinCLK, INPUT_PULLUP);
    pinMode(pinDT, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinDT), isrMovement, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinSW), isrSW, FALLING);
}

// ? <===== Detectar movimiento del encoder =====>

void Encoder::isrMovement()
{
    unsigned long now = millis();

    if (now - instance->lastInterrupTime < 150) return;
    bool clkState = digitalRead(instance->pinCLK);

    if (clkState == LOW)
        instance->position++;
    else
        instance->position--;

    instance->lastInterrupTime = now;
}

void Encoder::isrSW()
{
    unsigned long currentTime = millis();

    if (currentTime - instance->lastButtonPress > 200)
    {
        instance->buttonClicked = true;
        instance->lastButtonPress = currentTime;
    }
}

int32_t Encoder::getDelta()
{
    noInterrupts();
    int32_t tem = position;
    position = 0;
    interrupts();
    return tem;
}

bool Encoder::wasClicked()
{
    if (instance->buttonClicked)
    {
        instance->buttonClicked = false;
        return true;
    }

    return false;
}
