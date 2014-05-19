#include "Distance.h"

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
    #ifdef ULTRASONIC_PARALLEL
    tess_ping = distances[filter_count];    
    #elif ULTRASONIC_FILTER
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
            #ifdef DEBUG
            print("Filtered!\n");
            #endif
            return distances[9];
        }
        else
        {
            #ifdef DEBUG
            print("Filtered!\n");
            #endif
            return distances[filter_count-1];
        }
    }
    else
    {
        return distances[filter_count];
    }
    
}
int calculateAverage()
{
    int average = 0;
    for (int i=0;i<DISTANCE_SIZE;i++)
    {
         average += distances[i];
    }
    average = average/DISTANCE_SIZE;
    return average;
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
