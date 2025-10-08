#ifndef MOTOR_H
#define MOTOR_H

// Function prototypes
void initMotor(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);
void runForward();
void runBackward();
void runLeft();
void runRight();
void stopMotor();

#endif