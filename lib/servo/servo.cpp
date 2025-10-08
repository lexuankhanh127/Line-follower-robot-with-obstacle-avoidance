// Implementation of motor control functions for L298N driver
#include <Arduino.h>
#include "servo.h"

// Initialize motor driver pins
void initMotor()
{
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_IN3, OUTPUT);
    pinMode(MOTOR_RIGHT_IN4, OUTPUT);

    // Ensure motors are stopped initially
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);
}

// Drive both motors forward
void runForward()
{
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);

    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, HIGH);
}

// Drive both motors backward
void runBackward()
{
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, LOW);

    digitalWrite(MOTOR_RIGHT_IN3, HIGH);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);
}

// Turn left (pivot by running right motor forward)
void runLeft()
{
    // Stop or slow left motor, run right motor forward
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);

    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, HIGH);
}

// Turn right (pivot by running left motor forward)
void runRight()
{
    // Stop or slow right motor, run left motor forward
    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);

    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);
}

// Stop
void stopServo()
{
    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);

    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
}