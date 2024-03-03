#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define NIBLENGTH 4 // Nibble length

void binaryToHex(char* binaryNum);
char* charToString(char character);
void appendCharacterN(char* s, char character, int n);
char* decimalToHex(int decimalNum);

int getHexLength(int dec);
int log_a_to_base_b(int a, int b);

int main()
{
    // Binary Numbers
    char binaryNum1[] = "0001101011000101";
    char binaryNum2[] = "1010101010111000";
    
    binaryToHex(binaryNum1); // Hex: 1AC5 (0001 1010 1100 0101 --> 1AC5)
    binaryToHex(binaryNum2); // Hex: AAB8 (1010 1010 1011 1000 --> AAB8)
    
    printf("\n");
    printf("Yoooo: %s\n", decimalToHex(28));
    printf("\n");

    return 0;
}

void binaryToHex(char* binaryNum) {
    int i = -1;
    
    int count = 0;
    int currentExp = 3;
    int currentNibbleSum = 0;
    
    int nibblesInBinary = (sizeof(binaryNum) / sizeof(char)) / NIBLENGTH; // Get the number of nibbles that are contained in the binary, by checking how many '4's fit in the length of the binary
    char hexNum[nibblesInBinary];
    
    while (binaryNum[++i] != '\0') {
        // printf("My char: %c\n", binaryNum[i]);
        
        if (binaryNum[i] == 49) { // If current is '1'
            currentNibbleSum += pow(2, currentExp);
        }
        
        currentExp--;
        count++;
        
        if (count == NIBLENGTH) { // Reset exponent at new nibble
            
            // 'A' = 65
            // '0' = 48
            char hexChar = currentNibbleSum >= 10 ? 65 + (currentNibbleSum - 10) : 48 + currentNibbleSum;
            hexNum[i / 4] = hexChar;
            
            currentExp = 3;
            currentNibbleSum = 0;
            count = 0;
        }
    }
    
    printf("Hex: %s\n", hexNum);
}

char* decimalToHex(int decimalNum) {
    int i = 1, j, temp; 

    // char* hex = malloc(sizeof(char) * numNibbles); // One character in hex is representative of 1 nibble (4 bits in a byte)
    // char* hex = malloc(sizeof(char) * 10);
    
    int hexCharNum = getHexLength(decimalNum);
    char* hex = malloc(sizeof(char) * hexCharNum);
    
    printf("Hex num chars: %d\n", getHexLength(decimalNum));
    
    int hexIdx = hexCharNum - 1;
    
    while (decimalNum != 0) {
        temp = decimalNum % 16; 
        
        if (temp < 10) 
            temp = temp + 48; 
        else
            temp = temp + 55; 
        hex[hexIdx--] = temp;
        decimalNum /= 16;
    } 

    return hex;
}

// Calculates the char-length of a decimal's value
int getHexLength(int dec) {
    // Since hex is in base 16
    // 16^x = dec   --->   Find out how many hex-chars fit in the decimal, resolve 'x'
    // Resolve x    --->   x = log16(dec)
    int x = log_a_to_base_b(dec, 16) + 1;
    return x;
}

int log_a_to_base_b(int a, int b) {
    return log2(a) / log2(b);
}

void appendCharacterN(char* s, char character, int n) {
    for (int i = 0; i < n; i++) {
        strcat(s, charToString(character));
    }
}

char* charToString(char character) {
    char* str = malloc(sizeof(char) * 2);
    
    str[0] = character;
    str[1] = '\0';
    return str;
}

