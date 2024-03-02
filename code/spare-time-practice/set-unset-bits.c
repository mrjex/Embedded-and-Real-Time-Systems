#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define COMMAND1 "set"
#define COMMAND2 "unset"

typedef unsigned char byte;

long setBit(long dec, byte n);
long unsetBit(long dec, byte n);
byte getMostSignificantPos(long dec);
void printBinary(long dec);
void printOutput(long dec);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Only 3 inputted arguments accepted.\n");
        return 0;
    }
    
    char* endPointer;
    long decInput = strtol(argv[1], &endPointer, 16); // Convert from hex
    
    if (*endPointer != '\0') {
        printf("Input could not be converted to a number.");
        return 0;
    }
    
    if (strcmp(argv[2], COMMAND1) != 0 && strcmp(argv[2], COMMAND2) != 0) {
        printf("Only '%s' and '%s' are the supported commands of this program.", COMMAND1, COMMAND2);
        return 0;
    }
    
    /*
        Use byte for the position with respect to sustainability and space
        efficiency, since the program supports max 64-bit integers.
    */
    byte pos = (byte)atoi(argv[3]); // TODO: Try to input negative value in 3rd argument and improve safety
    
    
    if (pos > getMostSignificantPos(decInput) || pos <= 0) {
        printf("Inputted bit position is out of bounds.");
        return 0;
    }
    
    
    long finalDec;
    
    if (strcmp(argv[2], COMMAND1) == 0) {
        finalDec = setBit(decInput, pos);
    } else {
        finalDec = unsetBit(decInput, pos);
    }
    
    printOutput(finalDec);
    
    return 0;
}

void printOutput(long dec) {
    printf("0x%X === ", (int)dec);
    printBinary(dec);
}

void printBinary(long dec) { // Print binary in MSB-fashion
    int msbPos = getMostSignificantPos(dec) - 1;
    
    printf("0b");
    for (int i = msbPos; i >= 0; i--) {
        if ((dec >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

/*
    Returns the decimal number of the inputted 'dec' when setting
    a bit at position n
*/
long setBit(long dec, byte n) { // Since n >= 1, and the real positions ranges from 0, add 1
    return dec | (1 << (n -  1));
}

/*
    Returns the decimal number of the inputted 'dec' when unsetting
    a bit at position n
*/
long unsetBit(long dec, byte n) {
    return dec & ~(1 << (n - 1));
}

byte getMostSignificantPos(long dec) {
    return log2(dec) + 1;
}