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
    volatile long int logged_data_count;
    volatile long int char_count = 0;
    volatile long int* char_count_pointer = &char_count;

    robot_status = ENABLED;

    logInit();
    pause(1000);

    #ifdef TEST
    test(char_count_pointer);
    return 0;
    #endif
    
    #ifdef PLAYBACK //make sure this is before LOG because it will reopen file with write
    playback("Main.txt", LOG_SIZE);
    pause(5000);
    #endif

    #ifdef LOG
    logData("Main.txt", "Hello File World!\n", 0, char_count_pointer);
    #endif

    #ifdef DRIVE
    initDrive();
    #endif

    filter_count = 0;
    counter = 0;
    print("Hello Robot\n");
    low(LED_2);
    low(LED_1);

    while(robot_status == ENABLED)//main loop
    {
        //debug("Loop\n", 0);
        button();
        navigate();
        //checkDriveTrain();
        //pause(100);   
        counter++;
    }
}
void test(volatile long int* char_count)
{
    *char_count = 5;
    print("char_count = %d\n", (int)*char_count);
    logInit();
    logData("Main.txt", "This is a Test! %i \n", (int)char_count, char_count);
    
    //playback("Main.txt", 50);
    pause(5000);
    print("Finished!\n");
}
char* debug(char *string, int data)
{
    char asdf[128];
    #ifdef DEBUG
    if (counter % count_const == 0)
    {        
        sprintf(asdf,string,data);
        print(asdf);
    }
    #endif
    return asdf;
}

void navigate()
{
    distance();
    if (tess_ping == 0)
    {
        debug("Ultrasonic Error!\n", 0);
        int s1 = servo_speed(LEFT_SERVO, 0);
        int s2 = servo_speed(RIGHT_SERVO, 0);
        servoCheck(s1,s2,"Error: in void navigate()\n");
    }
    else
    {    
        if (tess_ping < OBJECT_DISTANCE)
        {
            //TODO stop and turn
            stop();
            high(LED_1);
            turn(LEFT); //enum from drivetrain
        }
        else
        {
            
            low(LED_1);
        }
    }
}
int detect_object()
{
    if (tess_ping < OBJECT_DISTANCE)
    {
        return 1; //object is close
        debug("Object in front\n", 0);
    }
    else if (tess_ping == 0)
    {
        debug("Ultrasonic malfunction\n", 0);
        return -1; //malfunction
    }
    else
    {
        return 0; //no object
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
