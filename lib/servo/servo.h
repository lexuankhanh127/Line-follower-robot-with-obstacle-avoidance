#ifndef SERVO_H
#define SERVO_H

// L298N Motor Driver Pins
#define MOTOR_LEFT_IN1   6
#define MOTOR_LEFT_IN2   9
#define MOTOR_RIGHT_IN3  10
#define MOTOR_RIGHT_IN4  11

// Function prototypes
void initMotor();
void runForward();
void runBackward();
void runLeft();
void runRight();
void stopServo();

#endif // SERVO_H