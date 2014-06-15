#include "Logger.h"
#include <stdio.h>

volatile long int logged_data_count = 0;
int initialized = 0;

int logInit(void)
{
    if (initialized == 0)
    {
        sd_mount(DO,CLK,DI,CS);
        initialized = 1;
    }
    return 1;
}
int getInitialization()
{
    return initialized;
}
FILE* fileInit(char *filename, char *permission) //w = write, r = read, a = append
{
    FILE* filePointer = fopen(filename, permission);
    return filePointer;
}   

int logData(char *fileName, char *string, int data, volatile long int* char_sum)
{
    //char toWrite = combine(string, data);
    FILE* file = fileInit(fileName, "w");
    if (file != NULL)
    {
        logged_char_count = logged_char_count + getNumElements(string);        

        char buffer[sizeof(char)*sizeof(string)];
        sprintf(buffer, string, data);
        fwrite(buffer, 1, 15, file);
        fclose(file);
        debug(buffer, data);
        *char_sum = *char_sum + sizeof(buffer);
        return logged_data_count;
    }
    else
    {
        return 0;
    }
}

void playback(char *fileName, int chars)
{
    FILE* file = fileInit(fileName, "r");
    char buffer[chars*sizeof(char)];
    fread(buffer, sizeof(char), chars, file);    
    fclose(file);
    //char s[chars];
    print("%s", buffer);
}
int getNumElements(char* x)
{
    if (x[0] == NULL)
    {
        return 0;
    }
    else
    {
        int n = sizeof(x) / sizeof(x[0]);
        return n;
    }
}    



/*
    fread(s, 1, chars, file);                        // Read 15 characters
//    fread(char buffer[20], strlen()+1, 1, fp);

    fclose(file);                                 // Close the file
    printf("First %i chars in file:\n", chars);     // Display heading
    print("%s", (char*)s);                             // Display characters
    print("\n");
*/
 
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
