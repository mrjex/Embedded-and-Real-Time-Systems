#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
// #include <limits.h>

#define MAXBUFFER 200
#define MSBVERSION 1

#define CONSTANTBYTES 1 // 0 = false, 1 = true
#define BYTECONSTANT 4 // Only used if the variable above is true

#define ADDBINARIES true


void readInput(char* s);
uint64_t getMsbIdxV1(uint64_t dec);
uint64_t getMsbIdxV2(uint64_t dec);
uint64_t addBinaries(uint64_t mostSignificant, uint64_t leastSignificant);

int main(int argc, char* argv[])
{
    char input[MAXBUFFER];
    readInput(input);
    
    uint64_t dec;
    
    if (ADDBINARIES) {
        char* token = strtok(input, ", ");
        uint64_t nums[2];
        int x = -1;
        while (token != NULL && ++x < 2) {
            nums[x] = strtol(token, NULL, 10);
            token = strtok(NULL, ", ");
        }
        
        dec = addBinaries(nums[0], nums[1]);
    } else {
        dec = strtol(input, NULL, 10);
    }
    
    // printf("Dec: %lu\n", (unsigned long) dec);
    
    
    // STEP 1: Retrieve the position of the MSB to know how many bytes the output should be
    uint64_t msbIdx; // Number of bits
    if (MSBVERSION == 1) {
        msbIdx = getMsbIdxV1(dec);
    } else {
        msbIdx = getMsbIdxV2(dec);
    }
    
    
    // STEP 2: Calculate requried bytes based on 'msbIdx'
    uint64_t numBytes = msbIdx / 8;
    if (msbIdx % 8 != 0) { // Add excessive bits as a new byte
        numBytes++;
    }
    
    int startIdx;
    if (CONSTANTBYTES == 1) {
        startIdx = (BYTECONSTANT * 8) - 1;
    } else {
        startIdx = (numBytes * 8) - 1;
    }
    
    // STEP 3: Print the binary with the expected number of bytes
    // int startIdx = (numBytes * 8) - 1;
    for (int i = startIdx; i >= 0; i--) {
        if ((i + 1) % 8 == 0 && i != startIdx) {
            printf(".");
        }
        
        if ((dec >> i) & 1) { // TODO: Try with '|' operator and try with condition for checking if '0'
            printf("1");
        } else {
            printf("0");
        }
    }
    
    printf("\n");
    return 0;
}

void readInput(char* s) {
    fgets(s, MAXBUFFER, stdin);
    s[strlen(s) - 1] = '\0';
}

uint64_t getMsbIdxV1(uint64_t dec) {
    for (int i = 63; i >= 0; i--) {
        if ((dec >> i) & 1) { // Check if the current digit is the first msb
            return i + 1;
        }
    }
    return 0;
}

uint64_t getMsbIdxV2(uint64_t dec) {
    return log2l(dec);
}


// Add two 8-bit binaries into a 16-bit
uint64_t addBinaries(uint64_t mostSignificant, uint64_t leastSignificant) {
    return (mostSignificant << 8) | leastSignificant;
}