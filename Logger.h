#ifndef LOGGER_H
#define LOGGER_H

int logData(FILE* file, char *string, int data); //log with file pointer, and a string, the data is opional (this int will be put into the print if
                                                 //there is a corresponding % for it in print
void logInit(); //needs to be exectuted once per program run for logging capabilities
FILE* fileInit(char *filename, char *permission); //w = write, r = read, a = append
void playback(FILE* file, char *fileName, int chars); //Needs a file pointer, which can be obtained by fileInit(), 
                                                      //the name of the file, and the amount of characters it will print

#endif
