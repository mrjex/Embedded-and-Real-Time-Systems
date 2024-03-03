#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
    BITS - Terminology:
    
    Setting a bit:   a | b   --->   OR operator
    
    Clearing a bit:  a & b   --->   AND operator
    
    Toggle a bit:    a ^ b   ---> XOR operator
*/



int toggleBit(int dec, int n);
int flipBit(int dec, int n);
int setBit(int dec, int n);
int clearBit(int dec, int n);
int reverseByte(int dec);

int getBit(int dec, int n);
int getBitValue(int dec, int n);

void swap(int* a, int* b);


int main()
{
    printf("Toggle bit: %d\n", toggleBit(22, 0)); // 23
    printf("Toggle bit: %d\n", toggleBit(22, 1)); // 20
    printf("Toggle bit: %d\n", toggleBit(22, 2)); // 18
    printf("Toggle bit: %d\n", toggleBit(22, 3)); // 30
    printf("Toggle bit: %d\n", toggleBit(22, 4)); // 6

    printf("\n\n");
    
    // 12 = 1100
    printf("%d\n", getBit(12, 3)); // 1
    printf("%d\n", getBit(12, 2)); // 1
    printf("%d\n", getBit(12, 1)); // 0
    printf("%d\n", getBit(12, 0)); // 0
    
    printf("\n\n");
    
    // 12 = 1100
    printf("%d\n", getBitValue(12, 3)); // 8
    printf("%d\n", getBitValue(12, 2)); // 4
    printf("%d\n", getBitValue(12, 1)); // 0
    printf("%d\n", getBitValue(12, 0)); // 0
    
    
    printf("\n\n");
    
    // 12 = 1100
    printf("Flip bit: %d\n", flipBit(12, 3)); // 0100 = 4
    printf("Flip bit: %d\n", flipBit(12, 2)); // 1000 = 8
    printf("Flip bit: %d\n", flipBit(12, 1)); // 1110 = 14
    printf("Flip bit: %d\n", flipBit(12, 0)); // 1101 = 13
    
    
    int myV = 29;
    int myV2 = 45;

    int* p1 = &myV;
    int* p2 = &myV2;

    swap(p1, p2);
    
    printf("\n");
    printf("SWAP:\n\n");
    printf("%d, %d\n", *p1, *p2); // 45, 29
    
    
    
    printf("\n\n");
    printf("REVERSE\n");
    printf("%d\n", reverseByte(22)); // 13
    printf("%d\n", reverseByte(5)); // 5
    printf("%d\n", reverseByte(8)); // 1
    

    return 0;
}

// Returns the value of the n:th bith
int getBitValue(int dec, int n) {
    return getBit(dec, n) * pow(2, n); // Multiply '0' or '1' with the associated exponential power
}

// Returns '1' or '0'
int getBit(int dec, int n) {
    return (dec >> n) & 1;
}


// Learning lesson: Insert '1's using OR operator '|'
int setBit(int dec, int n) {
    return dec | (1 << n);
}

// Learning lesson: use '&' / AND operator to clear bits (set them to 0)
// Use negation
int clearBit(int dec, int n) { // Insert '0' at n:th position
    return dec & ~(1 << n);
}


int toggleBit(int dec, int n) { // Switches between 0 and 1 at the current bit
    int selectedBit = (1 << n);
    return dec ^ selectedBit;
}

void swap(int* a, int* b) {
    *a = *a ^ *b; // a = c
    *b = *a ^ *b; // b = c ^ b = a
    *a = *a ^ *b; // a = c ^ a = b
}


// Flips or inverts a bit either from '0' to '1' or from '1' to '0' at a given position
int flipBit(int dec, int n) {
    if (getBit(dec, n) == 1) { // Control the current bit-value to flip it to its opposite
        return clearBit(dec, n);
    } else {
        return setBit(dec, n);
    }
}

// Reverse an entire byte
int reverseByte(int dec) {
    int result = 0;
    int currentBit;
    
    int numBits = log2(dec) + 1;
    
    // SOLUTION 1:
    for (int i = 0; i < numBits; i++) {
        currentBit = (dec >> i) & 1; // getBit()
        result = result | (currentBit << (numBits - i - 1)); // setBit()
    }
    
    /*
    // SOLUTION 2:
    for (int i = 0; i < numBits; i++) {
        result |= ((dec >> i) & 1) << (numBits - i - 1);
    }
    */
    
    return result;
}