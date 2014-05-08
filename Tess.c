//By Zack Alfakir

#define DEBUG
#define DRIVE
//#define LEFT_ENCODER
//#define RIGHT_ENCODER
//#define TEST

static volatile int leftSpeed;
static volatile int rightSpeed;
static volatile int counter;

#include "simpletools.h"
#include "DriveTrain.h"
#include "DriveTrain.c"
#include "Ports.h"
#include "servo.h"
#include "ping.h"
#include "Tess.h"

int main()                    
{
    counter = 0;
    print("Hello Robot\n");
    low(LED_2);
    low(LED_1);

    #ifdef DRIVE
    debug("Initializing Drivetrain\n", 0);
    initDrive();
    #endif

    while(1)
    {
        #ifdef TEST
        testDrive();
        #endif
        debug("Loop\n", 0);

        setEncoders();

        checkDriveTrain();
        //pause(100);   
        counter++;
    }
}    
void stop()
{
    leftSpeed = 0;
    rightSpeed = 0;
}
void distance_parallel(void *z)
{
    
}
int distance()
{
    int ping = ping_cm(ULTRASONIC_PIN);
    debug("Distance: %d\n", ping);
    return ping;
}
void debug(char *string, int data)
{
    #ifdef DEBUG
    if (counter % count_const == 0)
    {
        char asdf[128];
        sprintf(asdf,string,data);
        print(asdf);
    }
    #endif
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
void navigate()
{
    int ping = distance();

    if (ping < OBJECT_DISTANCE)
    {
        leftSpeed = 0;
        rightSpeed = 0;
        debug("Object in front\n", 0);
        high(LED_1);
    }
    else
    {
        low(LED_1);
        leftSpeed = LEFT_SPEED;
        rightSpeed = RIGHT_SPEED;
    }
}
