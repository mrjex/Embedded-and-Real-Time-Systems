// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 4
// Submission code: 271323

#include <stdio.h>  //include standard input output library
#include <stdlib.h> //include standard library
#include <errno.h>  //include error library
#include <limits.h> //include limits library
#include <string.h> //include string library
#include <math.h>   //include math library

/**
 * This program takes a non-negative integer as command line argument
 * and converts it to binary.
 * 
 * To compile, you need to link the math library:
 * gcc -o bin2hec bin2hec.c -lm
 * 
 * Example usage:
 * ./bin2hec 00001100
 * Using pipes to convert ULLONG MAX to Hex:
 * ./dec2bin 18446744073709551615 | ./bin2hec
 */

// Main function in program, taking command line arguments
int main(int argc, char **argv)
{
    char *x;        // pointer to pipe input or command line argument (string)
    char input[65]; // this should be 65 because we need the null terminator at the end (64-bit system)

    // Check if input is given from stdin (pipe) or from command line argument, prioritize pipe
    if (argc == 1 && fgets(input, sizeof(input), stdin) != NULL)  // no command line arguments, check if pipe is not null
    {
        // Assign pointer x to pipe input string
        x = input;
    }
    else    // pipe is empty, so check command line arguments
    {
        // No argument given
        if (argc == 1)
        {
            printf("No command line argument given.\n");
            printf("Exiting program.\n");
            return 2;  // Exit program
        }

        // Too many arguments
        if (argc > 2)
        {
            printf("Too many command line arguments given.\n");
            printf("Exiting program.\n");
            return 2;  // Exit program
        }

        // Check if command line argument is -h
        if (strcmp(argv[1], "-h") == 0)
        {
            printf("This program returns the binary representation of a decimal number.\n");
            printf("To run it, type ./bin2hec <binary number>. ");
            printf("Or pipe an input using ./dec2bin <decimal number> | ./bin2hec \n");
            printf("Exiting program.\n");
            return 2;  // Exit program
        }

        // Check if command line argument is negative
        if (*argv[1] == '-')
        {
            printf("The argument must be a positive integer.\n");
            printf("Exiting program.\n");
            return 2;  // Exit program
        }

        // Assign pointer x to command line argument
        x = argv[1];
    }

    // Begin conversion of binary to hexadecimal
    int sum;      // integer sum of 4 bits aka one nibble, to be converted to hexadecimal
    int count;    // count of bits in nibble when looping through 4 bits

    // Loop through string x, 4 bits at a time
    for (int i = 0; i < strlen(x)-1; i+=4)
    {
        sum = 0;   // reset sum to 0
        count = 0; // reset count to 0
        
        for (int j = 0; j < 4; j++)            // Iterate through 4 bits aka one nibble
        {
            if (x[i+j] != 48)                  // if bit is 1, add 2^(3-count) to integer sum
            {
                sum += pow(2, (3 - count));    // add 2^(3-count) to integer sum
            }
            count++;                           // increment count by 1
        }
        printf("%X", sum);                     // print hexadecimal representation of 4 bits aka one nibble
    }
    printf("\n");                             // print newline

    return 0;                                  // Exit program
}