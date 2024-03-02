/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



struct {
    int decNum; // unsigned long long instead?
    int length;
    char binNum[62]; //  TODO: Smoothly assign binary number to this variable
} typedef NumberUnit;


void getBinaryLength(NumberUnit* nuP);
void iterateThroughBinary(NumberUnit* nuP);



int main()
{
    /*
    printf("%d\n", 1 & 0);
    printf("%d\n", 0 & 1);
    printf("%d\n", 1 & 1); // 1
    printf("%d\n", 0 & 0);
    
    printf("\n\n");
    
    printf("%d\n", 0 ^ 0);
    printf("%d\n", 1 ^ 1);
    printf("%d\n", 0 ^ 1); // 1
    printf("%d\n", 1 ^ 0); // 1
    
    printf("\n\n");
    
    printf("%d\n", (108 >> 7) ^ 1); // True if not 1 (true only if 0)
    
    printf("\n\n");
    
    int a = (108 >> 5); // 11 --> 3
    int b = (108 >> 4); // 110 --> 6
    
    printf("%d, %d\n", a, b);
    
    printf("%d\n", (108 >> 6) ^ 1); // F
    printf("%d\n", ((108 >> 5) ^ 1));
    printf("%d\n", ((108 >> 4) ^ 1));
    */
    
    NumberUnit* nuP = malloc(sizeof(NumberUnit)); // 4 + 4 + 62 = 70    72
    nuP->decNum = 108;
    getBinaryLength(nuP);
    iterateThroughBinary(nuP);

    return 0;
}

/*
    Two approaches:
        * Log base 2 of decimal
        * Retrieve MSB and return position
*/
void getBinaryLength(NumberUnit* nuP) { // TODO: Check 62-bit boundary error
    bool hasAssigned = false;
    
    for (int i = 31; i >= 0; i--) {
        if ((nuP->decNum >> i) & 1) {
            nuP->length = i;
            hasAssigned = true;
            break;
        }
    }
    
    if (!hasAssigned) {
        nuP->length = 0;
    }
    
    printf("Gs: %d\n", nuP->length);
}


void iterateThroughBinary(NumberUnit* nuP) {
    
    // Print current bin-digit in sequence
    for (int i = nuP->length; i >= 0; i--) { // n - 1?
        
        if ((nuP->decNum >> i) & 1) { // TODO: Concat string to nuP->binNum
            printf("1");
        } else {
            printf("0");
        }
    }
}
