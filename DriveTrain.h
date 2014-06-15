#ifndef DRIVETRAIN
#define DRIVETRAIN

//#include "servo.h"
#include "Ports.h"
#include "fdserial.h"

struct servo_motor {
    int speed;
    int port;
} left, right;

enum driveState{
    TURNING,
    MOVING,
    IDLE
} tess_drive_state;

enum direction{
    LEFT,
    RIGHT
};


void driveForward(int);
void driving(int, int);
void driveBackward(float);
void drive(void *x);
int getLeftTicks();
int getRightTicks();
float getLeftDistance();
float getRightDistance();
void turn(); //default 90 degrees
int stop();
void stopLeftSide();
void stopRightSide();
void setEncoders(); //enables defined encoders
void checkDriveTrain(); //prints the speeds given
int distToAngle(int); //changes a distance to an angle for the Servo's
int setServo(int, int, char*);
int servoCheck(int, int, char*);
#endif