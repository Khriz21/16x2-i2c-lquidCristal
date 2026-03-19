#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <TimerOne.h>

class Motor
{
private:
    uint8_t _stepPin;
    uint8_t _dirPin;
    uint8_t _enablePin;

    uint8_t _minInterval; // Minimum step interval for max speed
    uint8_t _maxInterval; // Maximum step interval for min speed
    bool _direction; // true for clockwise, false for counterclockwise
    uint8_t _targetSpeed;   // Target speed for acceleration/deceleration
    volatile uint8_t _pulseState;
    volatile uint8_t _pulpserInterval; // Step delay in microseconds
    bool _enabled;

    // Static pointer for ISR
    static Motor* _instance;

    // ISR function to generate step pulses
    void generateStepPulse();

public:
    // Constructor
    Motor(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);

    // Initialization
    void begin();
    void changeDirection();
    void updateSpeed(uint8_t speed);
    void enableState();

};

#endif
