#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXBUFFER 200


void clearBuffer();
bool bitIsSet(int dec, int n);
bool bitIsSetV2(int dec, int n);


int main(int argc, char* argv[])
{
    int dec = atoi(argv[1]);
    int n = atoi(argv[2]);
    
    // printf("Contains 1 = %s\n", bitIsSet(dec, n) ? "True" : "False");
    // printf("%d\n", dec & (1 << n));
    
    // 263 = 100000111
    
    printf("%s\n", bitIsSet(263, 0) ? "True" : "False"); // true
    printf("%s\n", bitIsSet(263, 1) ? "True" : "False"); // true
    printf("%s\n", bitIsSet(263, 2) ? "True" : "False"); // true
    printf("%s\n", bitIsSet(263, 3) ? "True" : "False"); // false
    printf("%s\n", bitIsSet(263, 4) ? "True" : "False");
    printf("%s\n", bitIsSet(263, 5) ? "True" : "False");
    printf("%s\n", bitIsSet(263, 6) ? "True" : "False");
    printf("%s\n", bitIsSet(263, 7) ? "True" : "False");
    printf("%s\n", bitIsSet(263, 8) ? "True" : "False"); // true
    
    printf("\n\n");
    
    
    printf("%s\n", bitIsSetV2(263, 0) ? "True" : "False"); // true
    printf("%s\n", bitIsSetV2(263, 1) ? "True" : "False"); // true
    printf("%s\n", bitIsSetV2(263, 2) ? "True" : "False"); // true
    printf("%s\n", bitIsSetV2(263, 3) ? "True" : "False"); // false
    printf("%s\n", bitIsSetV2(263, 4) ? "True" : "False");
    printf("%s\n", bitIsSetV2(263, 5) ? "True" : "False");
    printf("%s\n", bitIsSetV2(263, 6) ? "True" : "False");
    printf("%s\n", bitIsSetV2(263, 7) ? "True" : "False");
    printf("%s\n", bitIsSetV2(263, 8) ? "True" : "False"); // true
    
    return 0;
}


void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {};
}

/*
    If current bit is 1, we get the bit value, meaning that if it is greater than 0, a '1' is identified
*/
bool bitIsSet(int dec, int n) {
    int bitValue = dec & (1 << n);
    return bitValue > 0 ? true : false;
}

/*
 If we want to check the bit was the n:th positon, we can shift
 the decimal by n positions such that the first (least significant bit at position 0)
 is the value we are searching for
*/
bool bitIsSetV2(int dec, int n) {
    return (dec >> n) & 1; // Always either 1 or 0
}