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
    tess_drive_state = MOVING;
    if (x < 0)
    {
        setServo(DRIVE_SPEED*2,-DRIVE_SPEED,debug("Error: In void driveForward(int %i)\n",x));
    }
    else if (x == 0)
    {
        stop();
    }
    else
    {
        setServo(DRIVE_SPEED,DRIVE_SPEED,debug("Error: in void driveForward(int %i)\n",x));
    }
}
int stop()
{
    tess_drive_state = IDLE;
    debug("Stop called!\n", 0);
    int c = setServo(0,0,"Error: in int stop()\n");
    debug("C = %i\n", c);
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
    debug("Turn function called!\n", 0);
    tess_drive_state = TURNING;
    #ifdef DRIVE
    if (side == LEFT)
    {
        debug("Turning LEFT\n", 0);
        int s1 = servo_angle(LEFT_SERVO, -1800);//negative 
        int s2 = servo_angle(RIGHT_SERVO, 1800);
        servoCheck(s1,s2,"Error: in void turn(enum direction LEFT)\n");
    }
    else if (side == RIGHT)
    {
        debug("Turning RIGHT\n", 0);
        int s1 = servo_angle(LEFT_SERVO, 1800);
        int s2 = servo_angle(RIGHT_SERVO, -1800);
        servoCheck(s1,s2,"Error: in void turn(enum direction RIGHT)\n");
    }
    #else //still pre-compile
        debug("Drive not defined\n", 0);
    #endif
}
int setServo(int l, int r, char* x)
{
    int ll = servo_speed(LEFT_SERVO, l);
    int rr = servo_speed(RIGHT_SERVO, r);
    int ret = servoCheck(ll,rr,x);
    return ret;
}
int servoCheck(int l, int r, char* x)
{
    #ifdef DRIVE
    if (l != LEFT_SERVO || r != RIGHT_SERVO)
    {
        debug(x,0);
        if (l != LEFT_SERVO)
        {
            debug("Left Servo Error Code: %i\n", l);
        }
        if (r != RIGHT_SERVO)
        {
            debug("Right Servo Error Code: %i\n", r);
        }
        debug("Now Exiting!\n", 0);
        robot_status = DISABLED;
        return -1;
    }
    else
    {
        return 0;
    }
    #else
    debug("DRIVE not defined\n", 0);
    debug("servoCheck\n", 0);
    return 0;
    #endif
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
