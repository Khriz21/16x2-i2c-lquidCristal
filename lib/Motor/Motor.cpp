#include "Motor.h"
Motor* Motor::_instance = nullptr;
Motor::Motor(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin) 
    : _stepPin(stepPin),
    _dirPin(dirPin),
    _enablePin(enablePin),
    _pulseState(LOW),
    _targetSpeed(0),
    _pulpserInterval(2000), // Default to 1ms step interval
    _enabled(false)
{
    _instance = this; // Set the static instance pointer for ISR
}

void Motor::begin()
{
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, HIGH); // Disable motor by default
    Timer1.initialize(_pulpserInterval);
    Timer1.attachInterrupt([]() {
        if (Motor::_instance) Motor::_instance->generateStepPulse();
    });
}

void Motor::generateStepPulse()
{
    if (_enabled)
    {
        _pulseState = !_pulseState; // Toggle pulse state
        digitalWrite(_stepPin, _pulseState);
    }
}

void Motor::updateSpeed(uint8_t speed)
{
    // Map speed (0-255) to step interval (maxInterval to minInterval)
    _pulpserInterval = map(speed, 0, 255, _maxInterval, _minInterval);
    if (!_enabled) return;
    Timer1.initialize(_pulpserInterval);
}


void Motor::changeDirection()
{
    _direction = !_direction;
    digitalWrite(_dirPin, _direction ? HIGH : LOW);
}

void Motor::enableState()
{
    _enabled = !_enabled; // Toggle enabled state
    digitalWrite(_enablePin, _enabled ? LOW : HIGH); // LOW to enable, HIGH to disable
    if (_enabled) {
        Timer1.resume();
    } else {
        Timer1.stop();
    }
}