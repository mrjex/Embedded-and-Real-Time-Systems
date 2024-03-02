// (C) Joel Mattsson(2024)
// Work package 1 - Bonus Task

// Include the neccessary libraries
#include <stdio.h> // Standard library
#include <stdlib.h> // Used for atoi() method that converts a string to an integer
#include <stdbool.h> // Use bools

#define MAXBITS 32 // The maximum number of bits that the program is capable of dealing with

void decimalToBinary(int n); // Prototype function used in the process of compiling the program

// Main: The main execution thread
int main(int argc, char* argv[]) { // Read the inputted arguments and the integer representing their quantity
    if (argc > 1) { // If user has inputted at least one manual argument

        char* refP; // Declare a pointer that can be referenced to access the value by address
        int decimalParameter = strtol(argv[1], &refP, 10); // Convert the string to an integer in base 10

        if (refP == argv[1] || (*refP != '\0')) { // Check if the inputted argument is a valid number
            printf("Error: Invalid number.");
        } else {
            printf("Number: %d\n", decimalParameter); // Comply to given format and print the numerical argument
            decimalToBinary(decimalParameter); // Run the method where the inputted argument is converted to its binary equivalent in base 2
        }
    } else { // No arguments were passed, inform user
        printf("Error: No number provided. Please provide a number as a command line argument.");
    }

    return 0; // Program executed without encountering unexpected errors
}

/*
    Converts a decimal number to its binary equivalent, while using bitwise
    operators (<<, &) as well as neglecting trailing zeros and arrays that
    consume space.
*/
void decimalToBinary(int n) {

    printf("Binary: 0b");

    int numberOfZeros = 0; // Declare the variable with an initial value of 0 since it serves the role of a counter
    int numberOfOnes = 0; // Set the quantity of found '1's to 0 before we start searching for them
    int numberOfBits = (MAXBITS - 1); // Since the for-loop accounts for 0, we subtract by 1 to maintain the range of bits

    /*
        If we have found the first '1' in the decimal's binary format,
        we know that the remaining '0's aren't trailing. In other words,
        only display the '0' that appear after the decimal's biggest 2^x factor
    */
    bool hasFoundBiggestBinary = false; // Before the search/inherent algorithm is performed, we set it to false to indicate that it hasn't been located

    for (int i = numberOfBits; i >= 0; i--) { // Iterate through every bit that has potential of becoming a '1' in the binary output
        int x = (1 << i); // Retrieve the integer 2^i that represents the value of the currently inspected bit

        // If user's inputted argument contains 2^i as an addable term, it implies that we can add it to the final binary output
        if (n & x) {
            printf("1");
            numberOfOnes++; // Register the action of resolving a '1' in the binary equivalent
            hasFoundBiggestBinary = true; // Tell the code to allow addition of '0's in the binary string, since they no longer are trailing
        } else {
            if (hasFoundBiggestBinary || i == 0) { // If the '0' isn't trailing or if no '1' was identified (edge case where input = 0), register a '0' in the final output
                printf("0");
                numberOfZeros++; // Increment the number of involved '0's
            }
        }
    }

    printf("\nNumber of 0s: %d\n", numberOfZeros); // Comply to given format by displaying the number of '0's in the binary number
    printf("Number of 1s: %d\n", numberOfOnes); // Comply to given format by displaying the number of '1's in the binary number
}