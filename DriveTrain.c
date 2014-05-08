#include "DriveTrain.h"
//#include "abdrive.h" //Y U NO WORK
#include "servo.h"
#include "Tess.h"

#define DRIVE_COG 1
#define DRIVE_SPEED 64

extern volatile int leftSpeed;
extern volatile int rightSpeed;

unsigned int stack[40 + 50];
static int driveCog;

void initDrive()
{
    leftSpeed = 0;
    rightSpeed = 0;
    debug("Start driveCog\n", 0);
    driveCog = cogstart(&drive, NULL, stack, sizeof(stack));
    debug("driveCog Started!\n", 0);
}
void drive(void *x)
{
    while (1)
    {
        leftSpeed++;
        rightSpeed++;
        //debug("Left: %d ", leftSpeed);
        //debug("Right: %d\n", rightSpeed);
        //TODO find out why abdrive wont compile and use drive_speed to set the speed to the volatile speed ints
        //pause(250);
    }
}
void testDrive()
{
    //while (1)
        leftSpeed++;
        rightSpeed--;
        debug("Left: %d ", leftSpeed);
        debug("Right: %d\n", rightSpeed);
        //TODO find out why abdrive wont compile and use drive_speed to set the speed to the volatile speed ints
        //pause(250);
}
