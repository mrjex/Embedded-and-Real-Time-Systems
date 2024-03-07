// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 1
// Submission code: 888141

#include <stdio.h> // include standard input/output library
#include <stdlib.h> // include standard library
#include <stdbool.h> // include boolean library
#include <string.h> // include string library

// define enum for direction
enum DIRECTION
{
    N, //pos 0
    O, //pos 1
    S, //pos 2
    W //pos 3
};

// define struct for robot
typedef struct
{
    int xpos; // x position
    int ypos; // y position
    enum DIRECTION dir; // direction
} ROBOT; // define ROBOT as a type

typedef char byte; // define byte as a type

// function prototypes
typedef void (*RobotActionFunctionPointer)(ROBOT *); // Function pointer
void move(ROBOT *robot); // prototype for move function
void turn(ROBOT *robot); // prototype for turn function
RobotActionFunctionPointer getRobotAction(char command); // prototype for getRobotAction function
void performInstructions(char instructions[], ROBOT *robot, RobotActionFunctionPointer rFP); // prototype for performInstructions function

void checkValidity(int input); // prototype for checkValidity function
void clearBuffer(); // prototype for clearBuffer function

// main function
int main(void)
{
    int currentRound = 0; // counter for current round

    ROBOT *robot = malloc(sizeof(ROBOT)); // allocate memory for pointer to robot struct
    RobotActionFunctionPointer rFP; // Robot function pointer

    printf("Starting robot simulation game. Type -1 to exit.\n");

    // start game loop
    while (true)
    {
        printf("\n\n--------------------\n");
        printf("ROUND %d\n", ++currentRound); // increment and print current round

        int x; // x position
        int y; // y position
        printf("Start X: ");
        scanf("%d", &x); // get user input for x position

        checkValidity(x); // check if x position is valid or user wants to exit

        printf("Start Y: ");
        scanf("%d", &y); // get user input for y position

        checkValidity(y); // check if x position is valid or user wants to exit

        printf("%d, %d\n", x, y);

        robot->xpos = x; // assign x position to robot
        robot->ypos = y; // assign y position to robot
        robot->dir = 0; // starting direction is N

        char instructions[100]; // string array buffer for instructions
        printf("Enter instructions: ('m','t'): ");
        scanf("%99s", instructions); // take user instructions for moving or turning

        clearBuffer(); // clear buffer

        performInstructions(instructions, robot, rFP); // perform instructions
        printf("Final position: (%d, %d)\n", robot->xpos, robot->ypos); // print final position
    }

    return 0; // successfully exit program
}

// function to perform instructions
void performInstructions(char instructions[], ROBOT *robot, RobotActionFunctionPointer rFP)
{
    int numberOfInstructions = strlen(instructions); // get number of instructions from input string

    for (int i = 0; i < numberOfInstructions; i++) // iterate through each instruction
    {
        char currentInstruction = instructions[i]; // Input: "mmtmtmtmt" current = m   (current char in the input)

        rFP = getRobotAction(currentInstruction); // Decide on whether to use move() or turn(), or exit program
        rFP(robot);                               // Perform defined method
    }
}

// function to move robot
void move(ROBOT *robot)
{
    if (robot->dir == N)
    { // move NORTH
        robot->ypos = robot->ypos + 1; // increment y position
    }
    else if (robot->dir == O)
    { // move EAST
        robot->xpos = robot->xpos + 1; // increment x position
    }
    else if (robot->dir == S)
    { // move SOUTH
        robot->ypos = robot->ypos - 1;  // decrement y position
    }
    else
    { // move WEST
        robot->xpos = robot->xpos - 1; // decrement x position
    }
}

// function to turn robot
void turn(ROBOT *robot)
{
    robot->dir = (robot->dir + 1) % 4; // turn robot 90 degrees clockwise, modulo 4 to keep within 0-3 range
}

// Function that returns robot actions using function pointer
RobotActionFunctionPointer getRobotAction(char command)
{
    // switch statement to decide on which function to use
    switch (command)
    {
        case 'm': // if command is move
            return move; // return move function
        case 't': // if command is turn
            return turn; // return turn function
        default:  // if command is invalid
            printf("Invalid command. Exiting Program.\n");
            exit(1); // exit program with error
    }
}

void checkValidity(int input){
    // check if starting x position is out of range
        if(input==-1){ // check if user wants to exit
            printf("Exiting program.\n");
            printf("Thank you for playing!\n");
            exit(1); // exit program
        }
        else if(input < 0 || input > 99) // check if input is out of range
        {
            printf("invalid\n");
            exit(1); // exit program
        }
}

// function to clear buffer
void clearBuffer()
{
    int c; // initialize c as int
    while ((c = getchar()) != '\n' && c != EOF); // iterate through buffer until new line or EOF (end of file)
}