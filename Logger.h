#ifndef LOGGER_H
#define LOGGER_H

int logged_char_count = 0;

int logData(char *fileName, char *string, int data, volatile long int*); //log with file pointer, and a string, the data is opional (this int will be put into the print if
                                                                         //there is a corresponding % for it in print
                                                                         //returns 0 if file is not NULL, 1 if file is NULL
int logInit(); //needs to be exectuted once per program run for logging capabilities
FILE* fileInit(char *filename, char *permission); //w = write, r = read, a = append
void playback(char *fileName, int chars); //Needs a file pointer, which can be obtained by fileInit(), 
                                                      //the name of the file, and the amount of characters it will print
int getNumElements(char* x); //returns size of a char array


#endif
