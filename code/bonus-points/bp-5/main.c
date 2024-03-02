#include <stdio.h>
#include <stdlib.h>
// #include <math.h>

char decToHex(int dec);
// int reqBits[] = {1, 3, 2, 1, 1};

int main(int argc, char* argv[])
{
    if (argc != 6) {
        printf("invalid\n");
        return 0;
    }
    
    /*
    // Math library not allowed by your code grade, otherwise, this is the general solution for checking the bits
    for (int i = 1; i <= 5; i++) {
        if (atoi(argv[i]) >= pow(2, reqBits[i - 1])) {
            printf("invalid\n");
            return 0;
        }
    }
    */
    
    if (atoi(argv[5]) > 1) {
        printf("invalid\n");
        return 0;
    }
    
    
    int finalNibble1;
    int finalNibble2;
    
    finalNibble1 = (atoi(argv[1]) << 3);
    finalNibble1 = finalNibble1 | atoi(argv[2]);
    
    // printf("Final Nibble 1: %d\n", finalNibble1); // 15
    
    
    finalNibble2 = (atoi(argv[3]) << 2);
    finalNibble2 = finalNibble2 | (atoi(argv[4]) << 1);
    finalNibble2 = finalNibble2 | atoi(argv[5]);
    
    
    // printf("Final Nibble 2: %d\n", finalNibble2); // 6
    
    
    char hexA = decToHex(finalNibble1);
    char hexB = decToHex(finalNibble2);
    
    printf("0x%c%c", hexA, hexB);
    
    printf("\nExiting program...\n");
    return 0;
}


char decToHex(int dec) {
    int asciiZero = '0';
    int asciiA = 'A';
    
    if (dec < 10) {
        return asciiZero + dec;
    }
    
    return asciiA + (dec - 10);
}