// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 3
// Exercise 5
// Submission code: 2346743

#include <stdio.h> // include the standard io library
#include <stdlib.h> // include the standard library
#include <time.h> // include the time library

#define MAX 50 // define max number of elements in the array

int main(void) // declarea main function
{

    int arr[MAX]; // declare an array of elements max (50)
    srand(time(NULL)); // seed the random function with the current time

    for (int i = 0; i < MAX; i++) // go from i to MAX
    {
        arr[i] = 1 + (rand() % 99); // set the current array element to random number between 1 and 99
    }

    printf("The value of the address of the array (pointer) is: %p\n", &arr);
    printf("First integer in the array is (array[0]): %d\n", arr[0]);
    printf("The size of an integer (number of bytes is) is: %ld\n", sizeof(int));
    printf("The size of the whole array in bytes is: %ld\n", sizeof(arr));

    int* ptr = &arr[0]; // initialise an pointer to the first element of the array
    int i = 0; // declare variable i and set it to 0
    while(i < MAX) { // iterate MAX times
        int num = *ptr++; // get the value of the current pointer and then increment the pointer
        printf("%d - Num: %d X2: %d\n", i + 1, num, num * 2); // print i, the value, and the value * 2
        i++; // increment i
    }

    return 0; // exit out of the program
}
