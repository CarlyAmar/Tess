#ifndef DISTANCE_H
#define DISTANCE_H

#include "Tess.h"
#include "Ports.h"

int distance(); //changes the distance variable based on the ultrasonic
void distance_background(void *x); //used on another cog
void distance_parallel(); //Will start ultrasonic on a new cog

#endif
