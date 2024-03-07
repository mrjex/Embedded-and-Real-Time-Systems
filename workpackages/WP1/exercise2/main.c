// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 2
// Submission code: 271323

#include <stdio.h>  //include standard input output library
#include <stdlib.h> //include standard library
#include <string.h> //include string library

/**
 * This is a simple encryption program based on the Caesar cipher.
 * It takes a command line argument for right-shift, and then user inputs a string.
 * The program then prints the encrypted string.
 */

// Main function in program, taking command line arguments
int main(int argc, char **argv)
{
    char inputString[100];     // initalize inputString buffer to 100 chars
    char encryptedString[100]; // initialize encryptedString buffer to 100 chars
    int shift = -1;            // set shift to -1 to distinguish from command line argument 0

    // Check if command line argument is given
    if (argc == 1)
    {
        printf("No command line argument given.\n");
        printf("Exiting program.\n");
        return 0; // Exiting the Program
    }

    // Check if too many command line arguments are given
    if (argc > 2)
    {
        printf("Too many command line arguments given.\n");
        printf("Exiting program.\n");
        return 0; // Exiting the Program
    }

    // Check if command line argument is -h
    if (strcmp(argv[1], "-h") == 0)
    {
        printf("Usage: ./main <shift>\n");
        printf("Where <shift> is an integer.\n");
        printf("Exiting program.\n");
        return 0; // Exiting the Program
    }

    // Check if command line argument is "0", and not "00" or "000" etc. 
    if (*argv[1] == '0' && argv[1][1] == '\0') // argv[1][1] == '\0' checks for the null terminator
    {
        shift = 0; // set encryption shift to zero (no encryption case), recall default value of shift was -1
    }

    // Convert command line argument to int
    int convertedArgument = atoi(argv[1]);

    // Check if command line argument is an integer, and not a string (atoi returns 0 if not an integer)
    if (convertedArgument == 0 && shift != 0) //shift != 0 is to distinguish from command line argument 0
    {
        printf("Command line argument is not an integer.\n");
        printf("Exiting program.\n");
        return 0; // Exiting the Program
    }
    else
    {
        // Command line argument is an integer, assign it to shift amount
        shift = convertedArgument % 26; // take modulo 26 for english alphabet
        printf("You have entered %d\n", shift);
    }

    // Infinite loop to keep program running, as instructed
    while (1)
    {
        // Prompt user for input, max 99 chars because we need 1 char for the null terminator
        scanf("%99s", inputString);

        // Check  string length, and assign it to a variable (recall null terminator "\0" is not counted with strlen)
        int length = strlen(inputString);

        int i; // initialize i for loop
        char charAtI; // initialize charAtI for loop

        // Iterate through all characters in the string
        for (i = 0; i < length; i++)
        {
            charAtI = inputString[i]; // assign current character to charAtI

            // Compare letters with ASCII values
            if (charAtI >= 'A' && charAtI <= 'Z')       // Check if character is an UpperCase letter
            {
                if (shift < 0)                          // Check if shift is negative
                {
                    charAtI = 'Z' + (charAtI - 'Z' + shift) % 26;  // Shift the character by the shift amount
                }
                else if (shift > 0)                      // Check if shift is positive
                {
                    charAtI = 'A' + (charAtI - 'A' + shift) % 26;  // Shift the character by the shift amount
                }
            }
            else if (charAtI >= 'a' && charAtI <= 'z')    // Check if character is an UpperCase letter
            {
                if(shift < 0)                            // Check if shift is negative
                    charAtI = 'z' + (charAtI - 'z' + shift) % 26; // Shift the character by the shift amount
                else if(shift > 0){                      // Check if shift is positive
                    charAtI = 'a' + (charAtI - 'a' + shift) % 26; // Shift the character by the shift amount
                }
            }
            else                                // Character is not a letter in the English alphabet
            {
                printf("Character %c is not a letter.\n", charAtI);
                printf("Exiting program.\n");
                return 0;                       // Exiting the Program
            }
            encryptedString[i] = charAtI;       // Assign the encrypted character to the encrypted string
        }
        encryptedString[i] = '\0'; // Add null terminator to the end of the encrypted string

        // Print the encrypted string
        printf("%s\n", encryptedString);

        // Clear the input buffer
        while ((getchar()) != '\n');
    }

    return 0;    // Exiting the Program
}