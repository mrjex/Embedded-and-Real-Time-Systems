#include <stdio.h>
#include <stdlib.h>

int addBinariesV1(int leastSignificant, int mostSignificant, int bitSize);

int main()
{
    printf("The G: %d\n", addBinariesV1(8, 6, -1));
    printf("The G: %d\n", addBinariesV1(8, 255, -1));
    printf("test: %d\n", 0x0F);
    
    // Another learning lesson: Do i & k, where i is an arbitrary number and k is the number only consisting of 1s to fill all other positions at 0

    return 0;
}

/*
    'bitSize': The number of bits contained in the two other parameters
*/
int addBinariesV1(int leastSignificant, int mostSignificant, int bitSize) { // BITWISE SOLUTION 1
    // IMPORTANT NOTES:
    // int result = (b << 4) | (a << 1); // Insert 'a' such that one bin-digit overlaps with 'b'
    // Build 32-bit value from two 16-bits: result = (b << 16) | a;
    
    return (mostSignificant << 4) | leastSignificant; // Insert 4 zeros behind 'mostSignificant' and then insert the bin-digits of 'leastSignificant'
}
