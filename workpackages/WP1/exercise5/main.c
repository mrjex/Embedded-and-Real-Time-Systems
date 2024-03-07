// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 1
// Exercise 5
// Submission code: 271323

#include <stdio.h> // Stdio library: Standard input output library
#include <stdlib.h> // Stdlib library: Mainly for dynamic memory allocation of pointers to heap
#include <string.h> // strcar and strncat
#include <time.h> // Time library: Used to access time-related data. In this file, it is utilized as a way of generating a unique random seed
#include <unistd.h> // Unistd library: Access the process id of the launch of the program (optimzed randomization of seed)
#include <stdbool.h> // Stdbool library: Make use of bool datatype

#define MAX 100             // Defines the maximum number of the values in the table
#define MAXNUMBER 20        // Defines the maximum value of random numbers
#define OUTPUTSPACING 4     // Defines the space displayed between the number and it's frequency 'x's

// ------ Function declarations ----------

// This function generates a set of random numbers and fills the table *tab with these numbers
void create_random(int *tab);

// This function takes the *tab of random numbers and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);

// This function takes the frequency count table and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

// Append a specified amount of characters of the same type to an already existing string
void appendCharactersN(char *s, char c, int n);

// ------ Function definitions ----------

// Create an array of random numbers within specified range
void create_random(int *tab)
{
    /*
        Use current time and process id to set the seed of the randomization.
        Incorporating the process id helps distiguish between each execution
        of the program. In turn, the randomzied numbers aren't constrained by
        the time between each execution (only using 'time()' from 'time.h' library
        generates a new seed each second).
    */
    srand(time(NULL) * getpid());

    for (int i = 0; i < MAX; i++) // Iterate through all fields and assign a random number
    {
        tab[i] = rand() % (MAXNUMBER + 1); // Assign randomized number to current field
    }
}

/*
    Takes two pointers and manipulates one of them (freq) by mapping
    the contents of 'tab' to the equivalent index with an associated
    counter for each value.
*/
void count_frequency(int *tab, int *freq)
{
    /*
        Initialize all frequency fields to 0 at the start of the algorithm, since they must
        be incremented only when their corresponding numerical value is identified.
    */
    for (int i = 0; i < MAX; i++) // Iterate through all existing numbers
    {
        freq[i] = 0; // Assign value 0 to the current element
    }

    /*
        Link the frequency values in accordance with the randomized values in 'tables'.
        This is done by incrementing at the examined number's index in the frequency
        array.
    */
    for (int i = 0; i < MAX; i++) // Iterate through all existing numbers
    {
        int nr = tab[i]; // Link the numerical value to its frequency by index
        freq[nr]++;      // Since the specified random range starts at 0, we can use it as the index
    }
}

/*
    Print the result of the mapping of each value.
*/
void draw_histogram(int *freq)
{
    char spacing[50] = ""; // The maximum amount of spacing allowed is 49 characters (50 - terminator '\0')
    appendCharactersN(spacing, ' ', OUTPUTSPACING); // Append 'OUTSPACING' many whitespaces to a string (in the console, this is the space between the number and its frequency 'x's)

    for (int i = 0; i < MAX; i++) // Iterate through all numbers
    {
        if (freq[i] > 0) // Don't display the numbers that don't have any frequency
        {
            char s[MAX] = ""; // Accommodate space for edge case where all random numbers a specific number
            appendCharactersN(s, 'x', freq[i]); // Append 'freq[i]' many 'x's to the string 's'
            printf("%4d:%s%s\n", i, spacing, s); // Print the current number separated by predefined spacing and the string of 'x's of frequency
        }
    }
}

// Append 'n' characters with value 'c' to an already existing string
void appendCharactersN(char *s, char c, int n)
{
    for (int i = 0; i < n; i++) // Iterate over the specified quantity of characters to append
    {
        strncat(s, &c, 1); // Concatinate character 'c' to the string
    }
}

// ------ Main --------------------------

int main(void)
{
    int table[MAX + 1]; // Create an int array to store all possible numbers
    int frequency[MAX + 1]; // Declare an array that represents the frequency of each number in the form of an array

    create_random(table); // Assign randomized value to each contained element in 'table' array
    count_frequency(table, frequency); // Map values from 'table' to 'frequency'
    draw_histogram(frequency); // Print the frequencies of each number to the console

    /** Printing table elements to verify correctness, as TA Asked
    for(int i=0; i<MAX; i++){   // iterate through all the elements in the table
        printf("%d ", table[i]); // print the current element
    }
    printf("\n");  // new line
    */

    return 0;  // successfully exit the program
}