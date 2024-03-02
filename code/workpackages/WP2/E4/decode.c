// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 4
// Submission code: 888141


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ARGUMENTS 5 // Arguments from code.c
#define A_ASCII 65

typedef unsigned char byte;

byte reqBits[ARGUMENTS] = { 1, 3, 2, 1, 1 }; // Represents the required bits for each of the 5 bit-packaged components
char* bitPackageComponents[ARGUMENTS] = { "engine_on", "gear_pos", "key_pos", "brake1", "brake2" }; // The defined components in the task

// - - - FUNCTION PROTOTYPES - - -
byte hex2Dec(char hex);
void dec2BinMSB(byte** bP, byte startIdx, byte endIdx, byte dec);

// - - - MAIN LOGIC - - -
int main(int argc, char* argv[]) {
    char input[65];
    char* hex;

    if (fgets(input, sizeof(input), stdin) != NULL) { // Read from terminal
        hex = input; //  Set hex to the input

            /*
                FOR TAs (if wanting to verify that the output from code.c is correct),
                uncommnt the line below:
            */
            printf("hex from code.c: %s\n", hex); // Print hex from code.c

            int length = strlen(hex); // Read length of the hex (in the scope of the given task, this value will always equate to 2)
            byte* bin = malloc(sizeof(byte) * 8); //  Dynamically allocate memory
            byte idx = 0; // The starting index of the first nibble

            // Iterate through each hexa-character one at a time
            for (int i = 0; i < length; i++) {
                byte dec = hex2Dec(hex[i]); // Convert the current hexa character to decimal
                dec2BinMSB(&bin, idx, idx + 4, dec);
                idx += 4;
            }

            idx = 0; // Reset the variable and use it as the index for 'reqBits[]'
            byte counter = 0; // Controls bit segment is currently being calculated
            byte sum = 0;
            byte currentExp;

            for (byte i = 0; i < 8; i++) { // Iterate through all 8 bits
                currentExp = reqBits[idx] - 1 - counter; // Calculate current exponent based on position in bit-segment

                if (bin[i] == 1) { // Only increment sum if the current binary is '1'
                    sum += pow(2, currentExp); // Add with 2 to the power of the current exponent
                }

                counter++; // Increase counter to indicate that the next bit will be processed

                // If the length of the required amount of bits for the current segment is reached, print the output and reset it
                if (counter == reqBits[idx]) {
                    printf("%s: %d\n", bitPackageComponents[idx], sum); // Print desired output

                    sum = 0;
                    counter = 0;
                    idx++;
                }        
            }

            free(bin); // Free dynamically allocated memory
        }
    
    return 0;
}

/*
    FUNCTIONALITY:
        * Convert decimal to binary from most significant bit
    
    PARAMETERS:
        * 'bP': Points to 8 bytes, that each make up for a bit.
        * startIdx: The starting index of the field of 'bP' (In the given task, this value will only be 0 or 3 to indicate start of respective nibbles)
        * endIdx: The ending index of the field of 'bP' (Either 4 or 7)
        * dec: The inputted decimal, that inside this method, continiously decreases
*/
void dec2BinMSB(byte** bP, byte startIdx, byte endIdx, byte dec) {
    /*
        Since this method always deals with 4 bits (the current nibble of the byte),
        the maximal and starting k-value will always be 3.
    */
    byte k = 3; // The value of the max exponent in a nibble
    byte kV; // The value of 2^k

    byte i = startIdx;

    while (i < endIdx) {

        /*
            Raise 2 to the power of k to get max possible term of 2^k
            that is contained within the current decimal 'dec'.
        */
        kV = pow(2, k); // Raise 2 to the power of k to 

        /*
            If the value expressed in decimal is greater than zero, then store it as 1 at the
            current exponential position, since it implies that it contains the factor 2^k.
        */
        if ((dec & kV) > 0) {
            (*bP)[i++] = 1; // Store binary value at current position as 1

            /*
                Only substract value when the decimal number has a binary equivalent of base 2 that can be subtracted.
                In other words, systematically utilize 'dec' as the current decimal remainder, where we in each iteration
                try to remove 2^k from it.
            */
            dec -= kV; // 
        } else {
            (*bP)[i++] = 0; // Store binary value at current position as 0
        }

        k--;
    }
}

/*
    Converts a hexa-character to its decimal equivalent
*/
byte hex2Dec(char hex) {
    byte dec;

    /*
        Since "0" and "9" are within the ascii interval 48-57, the if-statement
        below is only entered if the hex-char is between A-F.
    */
    if (hex >= A_ASCII) {
        dec = (hex - A_ASCII) + 10; // Substract ascci with 'A' and add it by 10 to get the number (Ex: A = 10, C = 12, F = 15)
    } else {
        dec = atoi(&hex); // Convert character ('0'-'9') to a byte
    }

    return dec;
}