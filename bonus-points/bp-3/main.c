#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUTDELIMITER " "

typedef struct {
    int n;
    int a[40];
} IntArray;

IntArray splitStringIntoIntegers(char* s, char* delimiter);
bool isDigit(char* input);
void clearBuffer();

int main(int argc, char* argv[]) {
    char dimensionsInput[30];

    printf("Input the size: ");
    fgets(dimensionsInput, 30, stdin);

    dimensionsInput[9] = '\0'; //

    IntArray matrixDimensions = splitStringIntoIntegers(dimensionsInput, INPUTDELIMITER);
    int matrixN = matrixDimensions.a[0] * matrixDimensions.a[1];




    char matrix1Input[30];
    printf("Input elements of matrix: ");

    // clearBuffer();

    fgets(matrix1Input, 30, stdin);

    matrix1Input[29] = '\0'; //

    IntArray matrix1 = splitStringIntoIntegers(matrix1Input, INPUTDELIMITER);

    if (matrix1.n != matrixN || matrix1.n == 1) {
        printf("invalid\n");
        return 0;
    }

    char matrix2Input[30];
    printf("Input elements of matrix: ");

    // clearBuffer();
    fgets(matrix2Input, 30, stdin);

    matrix2Input[29] = '\0'; //

    IntArray matrix2 = splitStringIntoIntegers(matrix2Input, INPUTDELIMITER);

    if (matrix2.n != matrixN || matrix2.n == 1) {
        printf("invalid\n");
        return 0;
    }

    // clearBuffer();


    printf("The sum is:\n");

    int i = -1; // Index of the entire matrix
    int currentColumnIdx; // Index of the current column
    int currentSum;
    while (++i < matrixN) {

        currentSum = matrix1.a[i] + matrix2.a[i];
        currentColumnIdx = i % matrixDimensions.a[1];
        
        printf("%d", currentSum);

       // If the index is currently positioned at the last column, print a newline to represent the new row
       if (currentColumnIdx == matrixDimensions.a[1] - 1) {

            /*
            if (matrixN == 4 && matrix2.a[3] == -300) {
                printf(" ");
            }
            */
            printf("\n");
        } else { // If the current element isn't the last element in the current row, then print a space to seperate it from the next value
            printf(" ");
        }
    }

    return 0;
}

/*
    Takes a string 's' with values seperated with string 'delimiter'
    and converts all values into integers contained in an array.
*/
IntArray splitStringIntoIntegers(char* s, char* delimiter) {
    char* splitPointer;
    splitPointer = strtok(s, delimiter); // Set the pointer to the first character of the string

    int a[40];
    int i = 0;

    IntArray intArray;

    /*
        TODO: Research --> Best way to split a string
    */

    while (splitPointer != NULL) {
        if (!isDigit(splitPointer)) {
            printf("invalid\n");
            exit(0);
        }

        intArray.a[i++] = atoi(splitPointer);
        splitPointer = strtok(NULL, delimiter); // Increment pointer to the first character of the next number

        /*
            IMPORTANT NOTE FOR EXAMS: The last element of of the string when calling strtok() ends with '\n', which MUST be changed to '\0' manually!
        */
    }

    intArray.n = i;

    return intArray;
}


/*
bool isDigit(char* s) {
    int l = strlen(s);
    int i = 0;

    int previousAddress = (int)s;

    if (s[l - 1] == '\n') {
        s[l - 1] = '\0';
        l--;
    }

    bool isNumber;

    while (i++ < l) {
        isNumber = (s[0] >= '0' && s[0] <= '9'); // DOES NOT COVER EDGE CASE FOR NEGATIVE NUMBERS

        if (isNumber == false) {
            return false;
        }

        s++;
    }

    s = (char*)previousAddress;
    return true;
}
*/


/*
    Takes a string as input performs two steps to return a bool on whether its a valid number or not:
        1) Check for other types of characters outside the range of 0-9
        2) Check for starting zeros
*/
bool isDigit(char* input) {

    /*
        IMPORTANT NOTES: The 2 if-statements below catch the edge cases of strtok()
    */

    int l = strlen(input);
    if (input[l -1] == '\n') { //Account for last string when using strtok(), which ends with '\n'
        input[l - 1] = '\0';
        l--;
    }

    if (l > 0) { // Account for the last potential substring if user inputs whitespaces after values (length is 0 with spaces)
        char* refP; // Declare a pointer that can be referenced to access the value by address
        int decimalNr = strtol(input, &refP, 10); // Convert the string to an integer in base 10

        if (refP == input || (*refP != '\0')) { // Check if the inputted argument is a valid number
            return false;
        }
    }

    return true;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}