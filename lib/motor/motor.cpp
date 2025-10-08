#include <Arduino.h>
#include "motor.h"

// store active pins so other functions use configured pins
uint8_t pinL1, pinL2, pinR3, pinR4;

void initMotor(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
    // Save configured pins
    pinL1 = in1;
    pinL2 = in2;
    pinR3 = in3;
    pinR4 = in4;

    pinMode(pinL1, OUTPUT);
    pinMode(pinL2, OUTPUT);
    pinMode(pinR3, OUTPUT);
    pinMode(pinR4, OUTPUT);

    // Ensure motors are stopped initially
    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, LOW);
    digitalWrite(pinR3, LOW);
    digitalWrite(pinR4, LOW);
}

// Drive both motors forward
void runForward()
{
    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, HIGH);

    digitalWrite(pinR3, LOW);
    digitalWrite(pinR4, HIGH);
}

// Drive both motors backward
void runBackward()
{
    digitalWrite(pinL1, HIGH);
    digitalWrite(pinL2, LOW);

    digitalWrite(pinR3, HIGH);
    digitalWrite(pinR4, LOW);
}

// Turn left (pivot by running right motor forward)
void runLeft()
{
    // Stop or slow left motor, run right motor forward
    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, LOW);

    digitalWrite(pinR3, LOW);
    digitalWrite(pinR4, HIGH);
}

// Turn right (pivot by running left motor forward)
void runRight()
{
    // Stop or slow right motor, run left motor forward
    digitalWrite(pinR3, LOW);
    digitalWrite(pinR4, LOW);

    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, HIGH);
}

// Stop
void stopMotor()
{
    digitalWrite(pinR3, LOW);
    digitalWrite(pinR4, LOW);

    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, LOW);
}