#include "Distance.h"
#include "ping.h"

void distance_parallel()
{
    unsigned int stack[40 + 25];
    debug("Starting Distance Cog!\n", 0);
    distCog = cogstart(&distance_background, NULL, stack, sizeof(stack));
    debug("Distance Cog Started! %d\n", distCog);
}
void distance_background(void *x)
{
    {
        tess_ping = ping_cm(ULTRASONIC_PIN);
        debug("Distance: %d\n", tess_ping);
    }
}
