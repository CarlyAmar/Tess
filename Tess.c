//By Zack Alfakir


#define DEBUG
//#define BUTTON
//#define DRIVE
//#define LEFT_ENCODER
//#define RIGHT_ENCODER
//#define TEST //THIS WILL NEGATE MOST OF MAIN AND JUST CALL test()
#define ULTRASONIC
#define ULTRASONIC_PARALLEL
//#define ULTRASONIC_FILTER
#define LOG
#define PLAYBACK


#include "Tess.h"
#include "simpletools.h"
#include "Distance.c"
#include "DriveTrain.c"
#include "Ports.h"
#include "servo.h"
#include "ping.h"
#include "Logger.c"

int main(void)                    
{
    FILE* file;
    logInit();
    pause(1000);

    #ifdef TEST
    test();
    return 0;
    #endif
    
    #ifdef PLAYBACK //make sure this is before LOG because it will reopen file with write
    file = fileInit("Main.txt", "r");
    playback(file, "Main.txt", LOG_SIZE);
    pause(5000);
    #endif

    #ifdef LOG
    logInit();
    file = fileInit("Main.txt", "w");
    logData(file, "Hello File World!\n", 0);
    #endif

    #ifdef DRIVE
    debug("Initializing Drivetrain\n", 0);
    initDrive();
    #endif

    filter_count = 0;
    counter = 0;
    print("Hello Robot\n");
    low(LED_2);
    low(LED_1);

    while(1)//main loop
    {
        //debug("Loop\n", 0);
        button();
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

void navigate()
{
    distance();
    if (tess_ping == 0)
    {
        debug("Ultrasonic Error!\n", 0);
    }
    else
    {    
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
void test()
{
    logInit();
    FILE* file = fileInit("Main.txt", "w");
    logData(file, "This is a Test! %i \n", 42);
    
    FILE* test = fileInit("Main.txt", "r");
    playback(test, "Main.txt", 100);
    pause(5000);                 // Close the file
    print("Finished!\n");
}
