// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 2
// Submission code: 888141

#include <stdio.h> // include the standard io library
#include <stdlib.h> // include the standard library
#include <time.h> // include the time library
// #### Constants #####
#define MAX 5 // define max number

// ##### typedefs ####
typedef struct q // define a struct q to represent a node
{
    int number; // int number holds data
    struct q *next; // next pointer to next node
    struct q *prev; // prev pointer to prev node
} REGTYPE; // define type alias 'REGTYPE'

// ##### Function declarations #####
REGTYPE *random_list(void); // declare function random list that generates a random list
REGTYPE *add_first(REGTYPE *temp, int data); // declare function add_first that adds a node at the head

// ###### Main program #######
int main(int argc, char *argv[])
{
    int nr = 0; // initialise int variable nr represents position
    REGTYPE *act_post, *head = NULL; // act_pos is the actual position in the list, head is the first node in the list

    srand(time(0)); // Random seed
    head = random_list(); // generate random list and assign to head
    head = add_first(head, 20); // Add first head node with value 30

    act_post = head; // set act_pos to head initially
    while (act_post != NULL) // while act_pos is not null
    {
        printf("\n Post nr %d : %d", nr++, act_post->number);
        act_post = act_post->next; // set act pos to next node
    }

    // --- Free the allocated memory ---
    while ((act_post = head) != NULL) // while current node is not null
    {
        head = act_post->next; // set the head to the next node
        // printf("\nFreeing %p", act_post);
        free(act_post); // free the memory for current node
    }

    return 0; // program succeeded
}
// ==== End of main ======================================

REGTYPE *random_list(void) // function to generate random list
{
    int nr, i = 0; // nr and i correspond to the position in the list
    REGTYPE *top; // top is a pointer to start
    REGTYPE *start = malloc(sizeof(REGTYPE)); // Allocate memory for head node
    top = start; // point top to start
    REGTYPE *curr = start; // initialise current as the head

    while (i < 100) // run 100 times
    {

        curr->number = rand() % MAX; // generate random number
        if (i == 99) // if this is the last iteration
        {
            curr->next = NULL; //set the next to null
            break; // break out
        }

        curr->next = malloc(sizeof(REGTYPE)); // allocate memory for next node
        curr->next->prev = curr; // set the previous pointer to the current node
        curr = curr->next; // go up the nodes
        i++; // increment i

    }

    return (top); // return the head
}

//==========================================================
REGTYPE *add_first(REGTYPE *temp, int data) // declare a function to add a node at head
{
    REGTYPE *head = malloc(sizeof(REGTYPE)); // allocate memory for head
    head->number = data; // assign the data

    head->next = temp; // set the next ptr to the linked list
    return head; // return the head
}