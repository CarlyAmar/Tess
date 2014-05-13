#ifndef TESS
#define TESS

static volatile int leftSpeed;
static volatile int rightSpeed;
static volatile int counter;

void distance_background(void *x); //used on another cog
void distance_parallel(); //Will start ultrasonic on a new cog
void stop(); //sets speeds to zero
void button(); //turns LED 2 on if a button is pressed
void debug(char *string, int data); //Will print every 100 times, include the string with the % symbols and no % if no variable is needed, 
                                    //in which case the second parameter is  filler
int distance(); //changes the distance variable based on the ultrasonic
void setEncoders(); //enables defined encoders
void setLeftEncoder(); //enables lefts
void setRightEncoder(); //enables right
void navigate(); //prints, turns on a light, and turns if soimething is close to it
void checkDriveTrain(); //prints the speeds given
void average(); //averages ultrasonic values, not very effective
int filter(); //will get rid of outliers in the distances array
               //if current value is an outlier, it will report the last value

#endif