#include "DriveTrain.h"
#include "abdrive.h"
#include "servo.h"
#include "Tess.h"

#define DRIVE_COG 1
#define DRIVE_SPEED 64

extern volatile int leftSpeed;
extern volatile int rightSpeed;

unsigned int stack[40 + 25];
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
        //servo_speed(LEFT_SERVO, leftSpeed);
        //servo_Speed(RIGHT_SERVO, rightSpeed);
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
void turn()
{
    leftSpeed = -1;
    rightSpeed = 1;
}
void setLeftEncoder()
{
    set_output(LED_1, input(LEFT_ENCODER_PIN)); //This encoder does not work
}
void setRightEncoder()
{
    set_output(LED_2, input(RIGHT_ENCODER_PIN));
}
void checkDriveTrain()
{
    debug("Left: %d", leftSpeed);
    debug(" Right: %d\n", rightSpeed);
}
void setEncoders()
{
    //Will set present encoder outputs to the LED's
    #ifdef LEFT_ENCODER
    setLeftEncoder();
    #endif

    #ifdef RIGHT_ENCODER
    setRightEncoder();
    #endif
}

