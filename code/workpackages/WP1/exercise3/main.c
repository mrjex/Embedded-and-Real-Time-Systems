// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 3
// Submission code: 271323

#include <stdio.h>  //include standard input output library
#include <stdlib.h> //include standard library
#include <time.h> // use time.h header file to use time  

#define MAX_NUMBER 10 // define max number of guesses

/**
 * This is a guessing game for the user to guess a random number between 1 and 100.
 */

// Main function in program, no command line arguments in this one
int main(void)
{
        printf("Welcome to the guessing game!\n");
        char playAgain = 'y';   // initialize playAgain to 'y' (default to keep loop going)
        int randomNumber;       // initialize randomNumber
        int countGuesses;       // initialize countGuesses
        int guess;              // initialize guess of user

        // use time.h library to use time as seed for rand() - pseudo-random number generator
        srand(time(NULL)); // srand() provides seed for rand() so that it generates different integers every time

    // while loop to keep program running        
    while(playAgain == 'y'){
        randomNumber = rand() % 100 + 1;          // create random number between 1 and 100
        countGuesses = 0;                         // set countGuesses to 0
        guess = -1;                               // set guess to -1 to distinguish from 0
        
        // while loop that runs until user guesses the correct number or runs out of guesses
        while(1){
            printf("Please enter an integer between 1 and 100: ");
            scanf("%3d", &guess);           // read user input, max 3 digits
            countGuesses++;                 // increment countGuesses by 1

            // Clear the input buffer
            while ((getchar()) != '\n');

            // check if guess is 0 or greater than 100
            if(guess == 0 || guess > 100){
                printf("Your guess is not within 1-100!\n");
                printf("Exiting program.\n");
                return 0; // Exiting the Program
            }

            // check if guess is correct, too high, too low, or not a number
            if (guess == randomNumber)    // case: guess is correct
            {
                printf("You have guessed %d times and your guess is correct!\n", countGuesses);
                printf("Would you like to play again? (y/n): ");
                scanf("%c", &playAgain); // space before %c to ignore whitespace
                
                // Clear the input buffer
                while ((getchar()) != '\n');

                if(playAgain == 'y'){     // case: user wants to play again 
                    break;                // break out of while loop
                }
                else if(playAgain == 'n'){ // case: user does not want to play again
                    printf("Thank you for playing!\n");
                    printf("Exiting program.\n");
                    return 0; // Exit the Program
                }
                else{         // case: user enters invalid option
                    printf("You have entered an invalid option.\n");
                    printf("Exiting program.\n");
                    return 0; // Exit the Program
                }
            }
            else if (guess > randomNumber)      // case: guess is too high
            {
                printf("Your guess is too high!\n");
            }
            else if (guess < randomNumber)      // case: guess is too low
            {
                printf("Your guess is too low!\n");
            }
            else                                // case: guess is not a number
            {
                printf("Your guess is not a number!\n");
                printf("Exiting program.\n");
                return 0; // Exiting the Program
            }

            // check if user has no guesses left at the end of this round
            if(countGuesses == MAX_NUMBER){   // case: user has no guesses left
                printf("GAME OVER. You have no guesses left.\n");
                printf("Would you like to play again? (y/n): ");
                scanf("%c", &playAgain);    // space before %c to ignore whitespace

                // Clear the input buffer
                while ((getchar()) != '\n');

                if(playAgain == 'y'){        // case: user wants to play again
                    break;                   // break out of while loop
                }else if(playAgain == 'n'){ // case: user does not want to play again
                    printf("Thank you for playing!\n");
                    printf("Exiting program.\n");
                    return 0; // Exit the Program
                }
                else{         // case: user enters invalid option
                    printf("You have entered an invalid option.\n");
                    printf("Exiting program.\n");
                    return 0; // Exit the Program
                }
            }
            else{                           // case: user has guesses left
                // tell user how many guesses they have left
                printf("You have %d guesses left.\n", MAX_NUMBER - countGuesses);
            }
        }
    }
    return 0;       // Exiting the Program
}