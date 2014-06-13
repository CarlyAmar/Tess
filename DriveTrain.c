#include "DriveTrain.h"
#include "abdrive.h"
#include "servo.h"
#include "Tess.h"

#define DRIVE_COG 1

extern volatile int leftSpeed;
extern volatile int rightSpeed;
extern volatile enum status robot_status;

unsigned int stack[40 + 25];
static int driveCog;

void driveForward(int x)
{
    if (x < 0)
    {
        int s1 = servo_speed(LEFT_SERVO, DRIVE_SPEED);
        int s2 = servo_speed(RIGHT_SERVO, DRIVE_SPEED);
        servoCheck(s1,s2,debug("Error: In void driveForward(int %i)",x));
    }
    else if (x == 0)
    {
        stop();
    }
    else
    {
        int s1 = servo_angle(LEFT_SERVO, distToAngle(x));
        int s2 = servo_angle(RIGHT_SERVO, distToAngle(x));
        servoCheck(s1,s2,debug("Error: in void driveForward(int %i)",x));
    }
}
int stop()
{
    int c;
    {
        int s1 = servo_speed(LEFT_SERVO, 0);
        int s2 = servo_speed(RIGHT_SERVO, 0);

        c = servoCheck(s1,s2,"Error: In void stop()\n");
    }
    if (c !=0)
    {
        return -1;
    }    
    else
    {
        return 0;
    }   
}

void initDrive()
{
    debug("Initializing Drivetrain\n", 0);
    /*
    servo_motor left;
    servo_motor right;
    */
    leftSpeed = 0;
    rightSpeed = 0;
    debug("Start driveCog\n", 0);
    driveCog = cogstart(&drive, NULL, stack, sizeof(stack));
    debug("driveCog Started!\n", 0);
    setEncoders();
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
void turn(enum direction side)
{
    if (side == LEFT)
    {
        int s1 = servo_angle(LEFT_SERVO, -1800);//negative 
        int s2 = servo_angle(RIGHT_SERVO, 1800);
        servoCheck(s1,s2,"Error: in void turn(enum direction LEFT)\n");
    }
    else if (side == RIGHT)
    {
        int s1 = servo_angle(LEFT_SERVO, 1800);
        int s2 = servo_angle(RIGHT_SERVO, -1800);
        servoCheck(s1,s2,"Error: in void turn(enum direction RIGHT)\n");
    }
    else
    {
        debug("Error: Cannot Turn, Error unknown\n", 0);
    }
}
int servoCheck(int l, int r, char* x)
{
    if (l != LEFT_SERVO || r != RIGHT_SERVO)
    {
        if (l != LEFT_SERVO)
        {
            debug("Left Servo Error Code: %i\n", l);
        }
        if (r != RIGHT_SERVO)
        {
            debug("Right Servo Error Code: %i\n", r);
        }
        debug(x, 0);
        debug("Now Exiting!\n", 0);
        robot_status = DISABLED;
        return -1;
    }
    else
    {
        return 0;
    }
}

int distToAngle(int x)//TODO check this
{
    int i = 360 / WHEEL_CIRCUMFERENCE; //how many degrees for each cm
    int angle = i*x;
    return angle;
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
    set_output(LED_1, input(LEFT_ENCODER_PIN)); //This encoder does not work
    #endif

    #ifdef RIGHT_ENCODER
    set_output(LED_2, input(RIGHT_ENCODER_PIN));
    #endif
}
