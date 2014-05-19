#include "Logger.h"

void logInit(void)
{
    sd_mount(DO,CLK,DI,CS);
}
FILE* fileInit(char *filename, char permission) //w = write, r = read, a = append
{
    FILE* filePointer = fopen(filename, permission);
    return filePointer;
}   

int logData(FILE* file, char *string, int data)
{
    //char toWrite = combine(string, data);

    fwrite(string, 1, 15, file);      // Add contents to the file
    fclose(file);                                 // Close the file

    return 0;                    
}
/*
char[] combine(char *string, int data)
{
    char asdf[128];
    sprintf(asdf,string,data);
    return(asdf);
}
*/
void playback(FILE* file, char *fileName)
{
    char s[15];
    file = fopen(fileName, "r");                // Reopen file for reading
    fread(s, 1, 15, file);                        // Read 15 characters

    fclose(file);                                 // Close the file
    print("First 15 chars in test.txt:\n");     // Display heading
    print("%s", s);                             // Display characters
    print("\n");
}