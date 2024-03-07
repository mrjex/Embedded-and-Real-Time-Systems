// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 4
// Submission code: 888141

// Use libraries
#include <stdio.h> // Standard input output
#include <stdlib.h> // Dynamic memory allocation
#include <stdbool.h> // Boolean datatype
#include <string.h> // String operations
#include <math.h> // Math operations

#define ARGUMENTS 5 // The number of accepted arguments
#define A_ASCII 65

/*
    The size of a 'char' is 1 byte
*/
typedef unsigned char byte; // 0-255

/*
    Synchronize each argument with its associated number of bits in
    sequential order from start to finish (engine_on is is at index 0
    and brake2 at index 4).
*/
byte reqBits[ARGUMENTS] = {1, 3, 2, 1, 1};


// - - - - - FUNCTION PROTOTYPES - - -  - -
byte calculateBitChunkSum(char* arg, byte* exp, byte reqBits);
byte decToBin(byte dec, byte* exp, byte reqBits);
byte* decToHexFormat(byte dec);
void printHex(byte* hex);

int main(int argc, char* argv[]) {
    /*
        End program and inform user that the number of
        inputted elements was incorrect.
    */
    if (argc != (ARGUMENTS + 1)) { // Add by one to account for that argv[0] is the file path
        printf("Program only accepts %d arguments.\n", ARGUMENTS);
        return 0;
    }

    /*
        Set the exponent value to -1 to synchronize it with 'reqBits' array. Since
        the bit to the left always is tied to 2^0 (where the exponent is 0), we assign
        it -1, so that we can add positive values representing the nth exponent-position
        which has (n - 1) as the exponent (the exponent range is 0-7 for a byte).
    */
    byte expValue = -1;
    byte* exp = &expValue; // Assign a pointer variable to keep track of the value when its locally modified in the method 'calculateBitChunkSum'
    byte finalDecimal = 0; // Declare variable that represents the decimal equivalent of the inputted arguments
    
    /*
        Iterate through each of the 5 inputted arguments. The loop starts at the specified
        number of arguments and ends at the last one, which allows us to incrementally
        add the variable 'exp' (current exponent) from 0 to 7
    */
    for (byte i = ARGUMENTS; i >= 1; i--) {
        /*
            DESCRIPTION:
                * Systematically unpack each argument from the numerical packed value to
                  its decimal value, and add each argument's decimal equivalent to
                  the variable that stores the final sum (the sum of all arguments
                  equates to the representative decimal number).
            
            PARAMETERS:
                * In the line below, we pass 3 parameters: the argument, the current
                  exponent, and the current number of bits that the current argument
                  consumes (for instance, gear_pos takes 3 bits and key_pos 2).
        */
        finalDecimal += calculateBitChunkSum(argv[i], exp, reqBits[i - 1]); // Pass the current argument, 2-base-exponent and the corresponding bit-length of the component
    }

    /*
        After the decimal value is derived, we convert it to hexadecimal
        by checking each nibble of the byte. Finally, the value is printed
        to the console in which decode.c reads from the pipeline.
    */
    printHex(decToHexFormat(finalDecimal));
    // printf("%X\n", finalDecimal);
    return 0;
}

/*
    Take an argument, the starting exponent and the number of bits
    consumed by the current argument and return the decimal value.
*/
byte calculateBitChunkSum(char* arg, byte* exp, byte reqBits) {
    byte result; // Declare the local variable that keeps track of the value to be returned
    
    byte numArg = atoi(arg); // Convert argument to from array of characters to byte
    result = decToBin(numArg, exp, reqBits);

    return result;
}

/*
    Convert a decimal number to its binary equivalent
    with 'reqBits' many bits regardless of trailing
    zeros. The method starts with 2^(*exp), meaning
    that pointer parameter is synchronized with the
    previous arguments' bit-lengths.
*/
byte decToBin(byte decArg, byte* exp, byte reqBits) {

    byte result = 0; // Declare local output variable

    /*
        Declare the counter variable that makes sure the function
        always returns a binary with 'reqBits' length.
    */
    byte counter = 0;

    /*
        Generate the next binary number as long as the decimal
        is greater 0 (as long as there is a possiblity that a
        '1' can be derived), or until the number of bits for the
        argument has been accounted for
    */

   byte initialExp = (*exp); // Store the initial exponent

    while (decArg > 0) { // Iterate for as long as the number contains a factor of 2 that can be converted to binary
        byte current = decArg % 2; // Current binary (0 or 1)
        (*exp)++; // Increment expontent to sync binary values

        if (current == 1) { // Only increment result when the current binary is 1W
            result += (byte)pow(2, *exp);
        }

        decArg >>= 1; // Divide by 2^1
    }

    (*exp) = initialExp + reqBits; // Sync the exponent's value with consideration to the required bits from the previously calculated components
    return result; // Return the result
}

/*
    Calculates the sum of each 4-bit in a byte and returns it as a pointer to 2 elements.
    Each element is numerically constrained: 0 =< x <= 15, which makes it highly
    convertible to hexadecimal (which is done in 'printHex()').
*/
byte* decToHexFormat(byte dec) {
    // byte nibbleSums[2] = {0, 0}; // A byte consists of 2 nibbles, each of which is 4 bits
    // dec --> 1010 1011 = AB --> 65,66

    /*
        Since the task specified numerical constraints of one byte combined with
        functionality covering hexa-conversions, it's appropriate to divide the
        byte into nibbles to faciliate the conversions.
    */
    byte* nibbleSums = malloc(sizeof(byte) * 2);
    nibbleSums[0] = 0; // Initiate sum to 0
    nibbleSums[1] = 0; // Initiate sum to 0

    byte currentExp = 0; // Initiate the exponent to 0

    for (byte i = 0; i < 8; i++) { // Iterate through one byte
        byte current = dec % 2; // Get current least significant binary digit
        dec >>= 1; // Divide by 2

        if (current == 1) { // If the binary digit is 1, then increment the corresponding sum
            if (i <= 3) { // Increment sum of first nibble, we still haven't traversed its length
                nibbleSums[0] += pow(2, currentExp); // Increment sum with current exponent
            } else { // Increment second nibble if all 4 bits are contributing to the sum of the first nibble
                nibbleSums[1] += pow(2, currentExp); // Increment sum with current exponent
            }
        }

        currentExp++; // Increment the exponent after each bit is travsersed

        /*
            If we have traversed 4 bits in a byte, the exponent resets to 0
            to represent the first value in the new nibble.
        */
        if (i == 3) {
            currentExp = 0;
        }
    }

    return nibbleSums; // Returns a pointer to a byte with 2 values, each one ranging from 0-15.
}

/*
    PARAMETER:
        * 'hex': A byte pointer to two elements that represents the sum of each nibble, which
                 combined make up for a byte.
    
    FUNCTIONALITY:
        * Convert an array of integers on the presumption that each element is between 0 and 15
*/
void printHex(byte* hex) { 

    for (byte i = 2; i >= 1; i--) { // Cannot do -1 with bytes: Avoid by incrementing index by one for the loop and start loop from 2 instead of 1
        if (hex[i - 1] >= 10) { // If the current number represents A-F in hex
            printf("%c", (hex[i - 1] - 10) + A_ASCII); // Subtract with -10 to sync the ascii and numerical values
        } else { // If current represent 0-9
            printf("%d", hex[i - 1]);
        }
    }

    printf("\n");
}