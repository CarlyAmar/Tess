//By Zack Alfakir


#define DEBUG
//#define BUTTON
//#define DRIVE
//#define LEFT_ENCODER
//#define RIGHT_ENCODER
//#define TEST
//#define ULTRASONIC
#define ULTRASONIC_PARALLEL
#define ULTRASONIC_FILTER


#include "Tess.h"
#include "simpletools.h"
#include "DriveTrain.h"
#include "DriveTrain.c"
#include "Ports.h"
#include "servo.h"
#include "ping.h"

unsigned volatile int distances[10];
unsigned volatile int filter_count;
volatile int tess_ping;
int distCog;

int main()                    
{
    filter_count = 0;
    counter = 0;
    print("Hello Robot\n");
    low(LED_2);
    low(LED_1);

    #ifdef DRIVE
    debug("Initializing Drivetrain\n", 0);
    initDrive();
    #endif

    while(1)//main loop
    {
        debug("Loop\n", 0);
        button();
        setEncoders();
        navigate();
        //checkDriveTrain();
        //pause(100);   
        counter++;
    }
}    
void stop()
{
    leftSpeed = 0;
    rightSpeed = 0;
}
void distance_parallel()
{
    unsigned int stack[40 + 25];
    debug("Starting Distance Cog!\n", 0);
    distCog = cogstart(&distance_background, NULL, stack, sizeof(stack));
    debug("Distance Cog Started! %d\n", distCog);
}
void distance_background(void *x)
{
    distance();
}
int distance()
{
    if (filter_count >= 10)
    {
        filter_count = 0;
    }
    distances[filter_count] = ping_cm(ULTRASONIC_PIN);
    //todo
    #ifdef ULTRASONIC_FILTER
    tess_ping = filter();
    #endif

    debug("Distance: %d\n", tess_ping);
    filter_count++;
    return tess_ping;
}
int filter()
{
    //int outliers = 0;
    int next_check = filter_count - 1;
    if (filter_count == 0)
    {
        next_check = 9;
    }
    //will create a variable for he distance and find the absolute value
    int difference = distances[filter_count] - distances[next_check];
    if (difference < 0)
    {
        difference = difference * -1;
    }
    if (difference > FILTER_AMOUNT)
    {
        if (filter_count == 0)
        {
            return distances[9];
        }
        else
        {
            return distances[filter_count-1];
        }
    }
    else
    {
        return distances[filter_count];
    }
    
}
void average()
{
    if (filter_count >= 10)
    {
        filter_count = 0;
    }
    distances[filter_count] = ping_cm(ULTRASONIC_PIN);
    tess_ping = 0;
    for (int i=0;i<10;i++)
    {
        tess_ping += distances[filter_count];
    }
    tess_ping = tess_ping/10;
    debug("Distance: %d\n", tess_ping);
    filter_count++;
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
    distance();
    if (tess_ping < OBJECT_DISTANCE)
    {
        leftSpeed = 0;
        rightSpeed = 0;
        debug("Object in front\n", 0);
        high(LED_1);
        turn();
    }
    else
    {
        low(LED_1);
        leftSpeed = LEFT_SPEED;
        rightSpeed = RIGHT_SPEED;
    }
}
void button()
{
    #ifdef BUTTON
    if (input(BUTTON) > 0)
    {
        high(LED_2);
    }
    else
    {
        low(LED_2);
    }
    #endif
}
