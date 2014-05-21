#ifndef TESS
#define TESS

static volatile int leftSpeed;
static volatile int rightSpeed;
static volatile int counter;

unsigned volatile int distances[10];
unsigned volatile int filter_count;
volatile int tess_ping;
int distCog;

void stop(); //sets speeds to zero
void button(); //turns LED 2 on if a button is pressed
void debug(char *string, int data); //Will print every 100 times, include the string with the % symbols and no % if no variable is needed, 
                                    //in which case the second parameter is  filler

void navigate(); //prints, turns on a light, and turns if soimething is close to it
void test(); //Shove test code in here and define TEST it will only fun this function, not the rest of main()

#endif