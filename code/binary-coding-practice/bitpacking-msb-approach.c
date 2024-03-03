#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define NUMARGS 5
#define BYTELENGTH 8 // Number of bits in a byte

typedef unsigned char byte;

byte reqBits[] = {1, 3, 2, 1, 1};

int byteSum; // The total sum of the byte (all 8 bits)

int getBitChunkSum(int argNum, byte reqBit, byte* eP);

int main(int argc, char* argv[]) {
    byte currentExponent = BYTELENGTH - 1; // Set initial exponent to MSB of a byte, which is 7
    byte* eP = &currentExponent; // Exponent Pointer points to 'currentExponent'
    
    // TODO: Implement the reverse of this, where i starts at NUMARGS (meaning that the binary conversion changes in 'getBitChunkSum()')
    
    // STEP 1: Get bit sum
    for (int i = 1; i <= NUMARGS; i++) {
        int argNum = atoi(argv[i]);
        byteSum += getBitChunkSum(argNum, reqBits[i - 1], eP);
    }
    
    printf("Byte sum: %d\n", byteSum);
    printf("%X\n", byteSum);
    
    return 0;
}

/*
    NOTE: This function only supports bit-chunks that contain only one '1' (which is the calculated msb 'initMsbPos')
*/
int getBitChunkSum(int argNum, byte reqBit, byte* eP) {
    byte initialEP = *eP;
    byte initMsbPos = initialEP - (reqBit - (log2(argNum) + 1)); // Get the msb bit position (0-7) based on the current but-chunk's length and the argument decimal
    *eP = initialEP - reqBit;
    return pow(2, initMsbPos);
}
