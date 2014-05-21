#include "Logger.h"

void logInit(void)
{
    sd_mount(DO,CLK,DI,CS);
}
FILE* fileInit(char *filename, char *permission) //w = write, r = read, a = append
{
    FILE* filePointer = fopen(filename, permission);
    return filePointer;
}   

int logData(FILE* file, char *string, int data)
{
    //char toWrite = combine(string, data);

    fwrite(string, 1, 15, file);      // Add contents to the file
    fclose(file);                                 // Close the file
    debug(string, 0);

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
void playback(FILE* file, char *fileName, int chars)
{
    fclose(file);
    char s[chars];
    file = fopen(fileName, "r");                // Reopen file for reading
    fread(s, 1, chars, file);                        // Read 15 characters

    fclose(file);                                 // Close the file
    printf("First %i chars in file:\n", chars);     // Display heading
    print("%s", s);                             // Display characters
    print("\n");
}   
 
/*
void example()
{
  int DO = 22, CLK = 23, DI = 24, CS = 25;      // SD card pins on Propeller BOE

  sd_mount(DO, CLK, DI, CS);                  // Mount SD card

  FILE* fp = fopen("test.txt", "w");          // Open a file for writing
  fwrite("Testing 123...\n", 1, 15, fp);      // Add contents to the file
  fclose(fp);                                 // Close the file
 
  char s[15];                                 // Buffer for characters
  fp = fopen("test.txt", "r");                // Reopen file for reading
  fread(s, 1, 15, fp);                        // Read 15 characters
  fclose(fp);                                 // Close the file

  print("First 15 chars in test.txt:\n");     // Display heading
  print("%s", s);                             // Display characters
  print("\n");                                // With a newline at the end
}    
*/
