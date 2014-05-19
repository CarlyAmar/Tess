#ifndef LOGGER_H
#define LOGGER_H

const int DO = 22, CLK = 23, DI = 24, CS = 25;

int logData(FILE* file, char *string, int data);
void logInit();
FILE* fileInit(char *filename, char permission); //w = write, r = read, a = append
void playback();

#endif
