// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 1
// Submission code: 271323

#include <stdio.h>  //include standard input output library
#include <stdlib.h> //include standard library

/**
 * This program takes an integer between 1 and 5 from the user
 * and prints a fact about that number
*/

// Main function in program, no command line arguments in this one
int main(void)
{
    int num = 0; // initialize num to 0
    while (1) // while true loop to keep program running
    {
        // prompt user for input
        printf("Please enter an integer between 1 and 5: ");
        // read user input, max 2 digits
        scanf("%2d", &num);
        // print user intput
        printf("You have entered: %d\n", num);                    // print user input

        // if, else-if, else statements to print fact about number
        if (num == 1)
        {                                                                                    // case: num is 1
            printf("Mount Everest is the tallest mountain in the world. Its elevation is "); // start print
            printf("8,840 m (29,003 ft) to 8,848 m\n");                                      // cont print
        }
        else if (num == 2)
        {                                                              // case: num is 2
            printf("Conjoined twins occur at a frequency of one in "); // start print
            printf("49,000 births to one in 189,000 births.\n");       // cont print
        }
        else if (num == 3)
        {                                                                                    // case: num is 3
            printf("There is no general closed-form solution to the three-body problem!\n"); // print
        }
        else if (num == 4)
        {                                                                      // case: num is 4
            printf("The four seasons are Spring, Summer, Fall, and Winter. "); // start print
            printf("The order is reversed in the Southern hemisphere.\n");     // cont print
        }
        else if (num == 5)
        {                                         // case: num is 5
            printf("Five is 0b101 in binary.\n"); // print Five
        }
        else
        {                                              // case: num is not between 1 and 5
            printf("Number is not between 1 and 5.\n"); // print error message
            printf("Exiting Program.\n"); // print error message
            return 0; // Exiting the Program
        }
        
    }
    return 0; // Exiting the program
}