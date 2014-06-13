#ifndef PORTS
#define PORTS

//Define pins here
#define IR_1 0

#define ULTRASONIC_PIN 2
#define BUTTON 10

#define RIGHT_SERVO 12
#define LEFT_SERVO 13

#define IR_2 13

#define LEFT_ENCODER_PIN 14
#define RIGHT_ENCODER_PIN 15

#define LED_1 26
#define LED_2 27


//SD card
#define DO 22
#define CLK 23
#define DI 24
#define CS 25

//SETTINGS
#define OBJECT_DISTANCE 20
#define LEFT_SPEED 1
#define RIGHT_SPEED 1
#define FILTER_AMOUNT 30
#define DISTANCE_SIZE 10
#define LOG_SIZE 100
#define DRIVE_SPEED 50
#define WHEEL_CIRCUMFERENCE 25 //in cm
static int count_const = 100;
#endif