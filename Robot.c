/**
 * This is the main Robot program file.
 */
#include "simpletools.h"
#include "DriveTrain.h"
#include "Ports.h"
int main(void)
{
    int operating = 1;
    while (operating == 1)
    {
        //print("Hello World");
        high(LED_1);
        low(LED_2);
        pause(500);
        low(LED_1);
        high(LED_2);
        pause(500);
    }
    return 0;
}

