// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 4
// Submission code: 271323

#include <stdio.h>  //include standard input output library
#include <stdlib.h> //include standard library
#include <errno.h>  //include error library
#include <limits.h> //include limits library
#include <string.h> //include string library

/**
 * This program takes a non-negative integer as command line argument
 * and converts it to binary.
 * 
 * Example usage:
 * ./dec2bin 12
 * ./dec2bin 18446744073709551615
 * Using pipes to convert ULLONG MAX to Hex:
 * ./dec2bin 18446744073709551615 | ./bin2hec
*/

// Main function in program, taking command line arguments
int main(int argc, char **argv)
{
    // No argument given
    if(argc == 1){
        printf("No command line argument given.\n");
        printf("Exiting program.\n");
        return 2;   // Exiting the Program
    }

    // Too many arguments
    if (argc > 2){
        printf("Too many command line arguments given.\n");
        printf("Exiting program.\n");
        return 2;   // Exiting the Program
    }

    // Check if command line argument is -h
    if (strcmp(argv[1], "-h") == 0){
        printf("This program returns the binary representation of a decimal number.\n");
        printf("To run it, type ./dec2bin <decimal number>.\n");
        printf("Exiting program.\n");
        return 2;   // Exiting the Program
    }

    // Check if command line argument is negative
    if(*argv[1] == '-'){
        printf("The argument must be a positive integer.\n");
        printf("Exiting program.\n");
        return 2;  // Exiting the Program
    }

    // Convert command line argument to int, using strtoull (unsigned long long, should be 64 bit)
    char *endptr; // pointer used by strtoull, helps check for conversion errors or if there are non-digit characters
    unsigned long long num = strtoull(argv[1], &endptr, 10); // convert argument to unsigned long long (64 bit), base 10

    // Check the number after conversion attempt for errors, endptr should point to null terminated == '\0' if no errors
    if(*endptr != '\0'){    // check if there are non-digit characters in the string
        printf("You have provided an invalid character or string.\n");
        printf("Exiting program.\n");
        return 2;       // Exiting the Program
    }

    // check for overflow errors using errno, errno is set to ERANGE if number is too large, and num is set to ULLONG_MAX
    if(errno == ERANGE && num == ULLONG_MAX){  // checks for overflow errors, meaning number exceeds 18446744073709551615
        printf("Argument is too large.\n");
        printf("Exiting program.\n");
        return 2;       // Exiting the Program
    }

    // Begin conversion of decimal to binary
    int msb = 0; // initialize most significant bit to 0
    int numBits = 0; // initialize bits counter
    int numBytes = 0; // initialize bytes counter

    // Calculate number of bits in msb
    for(int i = 63; i >= 0; i--){ // loop through all 64-bits from msb to lsb
        numBits = i + 1; // calculate number of bits
        if(num >> i & 1){ // check if bit is 1
            msb = 1; // set msb to 1
            break;   // break out of loop after finding msb
        }
    }

    // Calculate number of bytes
    if(numBits % 8 == 0){         // check if number of bits is divisible by 8
        numBytes = numBits / 8;   // if yes, then number of bytes is number of bits divided by 8
    }
    else{                            // if no, then number of bits is not divisible by 8
        numBytes = numBits / 8 + 1;  // assign number of bytes to number of bits divided by 8 plus 1
    }

    // Print binary representation
    for(int i = numBytes*8-1; i>=0; i--){       // loop through all bits from msb to lsb
        if(num >> i & 1){     // check if bit is 1
            printf("1");
        }
        else{                 // bit is 0
            printf("0");
        }
    }
    printf("\n");  // print newline

    return 0;   // Exiting the Program
}