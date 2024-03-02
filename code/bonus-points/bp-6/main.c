#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXBUFFER 100
#define NUMSTRINGS 5

void clearBuffer();
void endString(char* s);
void readString(char* s);

void removeShortestString(char** arr);
void deleteElement(char** arr, int idx);

int main(int argc, char* argv[])
{
    // Alternative 1
    // char* arr[5];
    
    // clearBuffer(); // Only goes A,B,C but not C,D
    
    // Alternative 2
    char** arr;
    arr = malloc(sizeof(char*) * NUMSTRINGS); // Store 5 strings inside the array
    
    for (int i = 0; i < NUMSTRINGS; i++) {
        
        // printf("AAAAA\n");
        char* currentString = malloc(sizeof(char) * MAXBUFFER);
        readString(currentString);
        
        // printf("BBBBB\n");
        
        arr[i] = malloc(sizeof(char) * MAXBUFFER);
        // arr[i] = malloc(sizeof(char) * strlen(currentString));
        strcpy(arr[i], currentString);
        
        
        // printf("CCCCC\n");
        // clearBuffer();
        // printf("Current string in array: %s\n", arr[i]);
    }
    
    removeShortestString(arr);
    clearBuffer();
    return 0;
}

void removeShortestString(char** arr) {
    int minIdx = 0;
    int minLength = INT_MAX;
    int currentLength;
    
    for (int i = 0; i < 5; i++) {
        currentLength = strlen(arr[i]);
        
        if (currentLength < minLength) {
            minLength = currentLength;
            minIdx = i;
        }
    }
    
    deleteElement(arr, minIdx);
}

void deleteElement(char** arr, int idx) {
    printf("Shortest string removed: %s\n", arr[idx]);
    
    for (int i = idx; i < (NUMSTRINGS - 1); i++) {
        strcpy(arr[i], arr[i + 1]);
    }
    strcpy(arr[4], ""); // Mark that the last index is removed
    
    printf("Array after removal:\n");
    for (int i = 0; i < (NUMSTRINGS - 1); i++) {
        printf("%s\n", arr[i]);
    }
}

void readString(char* s) {
    // clearBuffer();
    fgets(s, MAXBUFFER, stdin);
    // endString(s);
}

void endString(char* s) {
    s[strlen(s) - 1] = '\0';
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}