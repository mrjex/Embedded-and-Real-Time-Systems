#include <stdio.h> // Include standard input output library
#include <stdlib.h> // Include lib library for dynamic memory allocation
#include <string.h> // Include string-operation library

// Prototypes
int getFactorial(int n);
void swapCharacters(char* a, char* b);
void recursivePermutationsHelper(char* s, char** permutations, int* idxP);
void calculatePermutations(char* s, int start, int end, char** permutations, int* idxP);

// Main: Logic
int main(int argc, char* argv[]) {
    
    if (argc != 2) { // If no argument or excessive amounts of arguments provided
        printf("invalid");
        return 0;
    }
    
    int argLength = strlen(argv[1]); // Get length of first argument
    int totalCombinations = getFactorial(argLength) - 1; // Subtract with one to neglect the inputted combination
    
    char** permutations = malloc(sizeof(char*) * totalCombinations);
    // char* permutations[totalCombinations]; //
    
    int idx = 0;
    int* idxP = &idx;
    
    recursivePermutationsHelper(argv[1], permutations, idxP);
    
    printf("All permutations of the string abcd are: ");
    for (int i = 0; i < totalCombinations; i++) {
        printf("%s", permutations[i]);
        
        if (i != totalCombinations - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    
    // Free dynamically allocated memory
    for (int i = 0; i < totalCombinations; i++) {
        free(permutations[i]);
    }
    
    free(permutations);
    
    return 0;
}


// Dereferences two strings into the characters at first index
void swapCharacters(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void recursivePermutationsHelper(char* s, char** permutations, int* idxP) {
    calculatePermutations(s, 0, strlen(s) - 1, permutations, idxP);
}

void calculatePermutations(char* s, int start, int end, char** permutations, int* idxP) {
    
    // Base case
    if (start == end) { // When the starting and end index are equal, the base case is reached
        
        if (*idxP > 0) { // Don't store the first combination (the inputted string)
            permutations[(*idxP) - 1] = malloc(sizeof(char) * strlen(s)); // Dynamically allocate memory for the current valid permutation
            strcpy(permutations[(*idxP) - 1], s); // Assign value to the big permutation array at proper index
        }
        
        (*idxP)++; // Always increment index when a new permutation was found
        return; // Base case: Terminate the sub-branch of recursive execution
    }
    
    
    // This substring allows us to trace the recursive pattern since it represents the diverging branches of distinct combinations
    char* fixedSubString = s + start; // Get the current substring in the recursive function (ranging from index 'start' of the string 's')
    
    for (int i = start; i <= end; i++) {
        char* dynamicSubString = s + i; // Note that 'i' always is greater or equal to start. In other words, this substring are the 'loose' characters that will be swapped.
        
        swapCharacters(fixedSubString, dynamicSubString);
        calculatePermutations(s, start + 1, end, permutations, idxP);
        swapCharacters(fixedSubString, dynamicSubString); // "backtrack"??
    }
}

int getFactorial(int n) {
    int factorialN = 1;
    for (int i = n; i >= 1; i--) {
        factorialN *= i;
    }

    return factorialN;
}