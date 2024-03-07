// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 6
// Submission code: 2346743

#include <stdio.h> // include the standard io library
#include <stdlib.h> // include the standard library
#include <string.h> // include the string library
#include <unistd.h> // include the POSIX system library

#define MAX_CHAR 20 // define max number of characters allowed in the string

void copyString(char *, char *); // define copyString function, takes in a string and copies it


// define main function, takes in arg count and args
int main(int argc, char **argv)
{

    char content[MAX_CHAR + 1]; // define content of length max_char +1 for terminator

    // check if a file has been redirected
    if (!isatty(0)) // A file has been redirected
    {
        // if it has been, read the stream via fgets
        // +1 to account for null terminator
        fgets(content, MAX_CHAR + 1, stdin);
    }
    // otherwise no file has been redirected
    else {
        printf("Enter a string: ");
        // scan the standard input for a string up to 20 chars
        scanf("%20s", content);
        content[20] = '\0'; // terminate the string
    }

    // define string to copy original string to  
    char content2[MAX_CHAR + 1];

    // use the library function to copy the string
    strcpy(content2, content);
    printf("Using Library: %s\n", content2);

    // define string to copy original string to
    char content3[MAX_CHAR + 1];

    // use custom function to copy the string
    copyString(content3, content);

    printf("Using Function: %s\n", content3);

    return 0; // exit the program
}

// define a function copyString takes in string pointers
// param1: the destination string
// param2: the source string
void copyString(char *destination, char *source)
{
    while (*source != '\0') // go through the source while its not terminated
    {
        *destination++ = *source++; // set the current char of the destination
        // to the current source char
        // then increment both pointers to get to the next char
    }
    *destination = '\0'; // terminate the destination string
}
