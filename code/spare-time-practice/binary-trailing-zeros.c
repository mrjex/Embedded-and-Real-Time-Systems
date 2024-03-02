#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int getNumberOfTrailingZeros(int dec);
void getBinaryStats(int* binStats, int dec);
bool isEven(int dec);

int findMostSignificantBitPosV1(int dec);
int findMostSignificantBitPosV2(int dec);

int main()
{
    printf("%d\n", getNumberOfTrailingZeros(22)); // 22 = 10110 --> 1
    printf("%d\n", getNumberOfTrailingZeros(8)); // 8 = 1000 --> 3
    printf("%d\n", getNumberOfTrailingZeros(18)); // 18 = 10010 --> 1
    printf("%d\n", getNumberOfTrailingZeros(256)); // 256 = 100000000 --> 8
    
    
    int* binStats = malloc(sizeof(int) * 2);
    int myDec = 22;
    getBinaryStats(binStats, myDec);
    printf("Bin stats: 0s: %d, 1s: %d\n", *binStats, *(binStats + 1));
    
    
    printf("%s\n", isEven(12) ? "True" : "False");
    printf("%s\n", isEven(7) ? "True" : "False");
    
    
    printf("%d\n", findMostSignificantBitPosV2(22)); // 4
    printf("%d\n", findMostSignificantBitPosV1(8)); // 3
    printf("%d\n", findMostSignificantBitPosV1(256)); // 8
    
    
    free(binStats);
    return 0;
}


/*
    Prints the number of starting '0's found in the uninterrupted sequence
    at the start (right to left check) of a binary number
*/
int getNumberOfTrailingZeros(int dec) {
    
    int numberOfBits = log2(dec) + 1;
    int i = -1;
    int num = 0;
    
    while (++i < numberOfBits) {
        if (dec & 1) {
            break;
        }
        
        num++;
        dec >>= 1;
    }
    
    return num;
}


// Print number of '1's and '0's in a 32-bit
void getBinaryStats(int* binStats, int dec) {
    int num0 = 0;
    int num1 = 0;
    
    for (int i = 31; i >= 0; i--) {
        if ((dec >> i) & 1) {
            num1++;
        } else {
            num0++;
        }
    }
    
    binStats[0] = num0;
    binStats[1] = num1;
}

bool isEven(int dec) {
    return !(dec & 1);
}


int findMostSignificantBitPosV1(int dec) {
    for (int i = 31; i >= 0; i--) {
        if ((dec >> i) & 1) {
            return i;
        }
    }
    
    return -1;
}

int findMostSignificantBitPosV2(int dec) {
    return log2(dec);
}