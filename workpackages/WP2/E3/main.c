// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 3
// Submission code: 888141

#include <stdio.h> // include standard io library
#include <stdlib.h> // include standard library
#include <string.h> // include string library

#include <unistd.h> // FOR POSIX SYSTEMS

// #ifdef WIN32
// #include <io.h>
// #define access _access
// #endif
// #define F_OK 0 // FOR WINDOWS BASED SYSTEMS

#define FILENAME "DATA.bin" // define the file name

// -----typedefs -------
typedef struct
{
    char firstname[20]; // first name
    char famname[20]; // family name
    char pers_number[13]; // yyyymmddnnnc
} PERSON; // alias PERSON

// Function declaration (to be extend)
PERSON input_record(void);             // Reads a person’s record.
void write_new_file(PERSON *inrecord); // Creates a file and
// writes the first record
void printfile(void);                 // Prints out all persons in the file
void search_by_firstname(char *name); // Prints out the person if
// in list
void append_file(PERSON *inrecord); // appends a new person to the file
long getSize(FILE *);               // get the size in bytes of a file
_Bool fileExists(char *fileName);   // check if file exists

// main function
int main(void)
{

    int option; // declare an option

    do
    {
        printf("1 Create a new and delete the old file.\n");
        printf("2 Add a new person to the file.\n");
        printf("3 Search for a person in the file.\n");
        printf("4 Print out all in the file.\n");
        printf("5 Exit the program.\n");
        scanf("%d", &option); // assign the option

        if (option == 1) // if the option is 1
        {
            PERSON* original = calloc(1, sizeof(PERSON)); // allocate memory for 1 person
            PERSON* dummy = original; // add a pointer to original
            strcpy(dummy->firstname, "John"); // copy the name
            strcpy(dummy->famname, "Michaels"); // copy the family name
            strcpy(dummy->pers_number, "200310121234"); // copy the personnummer
            write_new_file(original); // write the file
        }

        if (option > 1 && option < 5) // if the option is within 1 & 5
        {
            if (!fileExists(FILENAME)) // check if the file exists
            {
                printf("File does not exists, please create one!\n");
                continue; // if it does skip the iteration
            }
        }

        if (option == 2) // if the option is 2
        {
            PERSON* inRecord = calloc(1, sizeof(PERSON)); // allocate memory for 1 person
            printf("Enter first name: ");
            scanf("%s", inRecord->firstname); //assign the first name
            printf("Enter last name: ");
            scanf("%s", inRecord->famname); //assign the family name
            printf("Enter personnummer: ");
            scanf("%s", inRecord->pers_number); //assign the personnummer
            append_file(inRecord); //append to the file
        }

        if (option == 3) // if the option is 3
        {
            char keyword[20]; // declare a first name
            printf("Enter keyword: ");
            scanf("%s", keyword); // assign the first name
            search_by_firstname(keyword); // search using the first name
        }

        if (option == 4) // if the optionn is 4
        {
            printfile(); // print the whole file
        }

        if (option < 1 || option > 5) { // if the option is outside the range
            printf("Invalid Option\n"); // its an invalid option
        }

    } while (option != 5); // loop while the option is not 5 (Exit)

    return 0; // program succeeded
}

void append_file(PERSON *inrecord) // function to append a person to file
{

    FILE *filePtr = fopen(FILENAME, "ab"); // open the file stream (binary append mode)
    fwrite(inrecord, sizeof(PERSON), 1, filePtr); // write to the stream
    fclose(filePtr); // close the stream
}

void search_by_firstname(char *name) // function to look up a user by a keyword
{

    FILE *filePtr = fopen(FILENAME, "rb"); // open a file stream

    long size = getSize(filePtr); // get the size of the file in bytes
    int numRecords = size / sizeof(PERSON); // calculate the total number of records

    PERSON *records = malloc(size); // allocate memory for all records
    fread(records, sizeof(PERSON), numRecords, filePtr); // read all records into the memory
    fclose(filePtr);                                     // close the stream

    int found = 0; // initialise int found to 0

    for (int i = 0; i < numRecords; i++) // go through all records
    {

        PERSON current = *records++;                                 // get the value of the current pointer and increment
        _Bool firstNameMatch = strcmp(current.firstname, name) == 0; // the first name matches the search keyword
        _Bool lastNameMatch = strcmp(current.famname, name) == 0;    // the last name matches the search keyword

        if (firstNameMatch || lastNameMatch) // if first_name or family_name matches 
        {
            printf("%s %s", current.firstname, current.famname); // print the name
            found++; // increment the variable
        }
    }

    if (!found) // if the variable is 0
    {
        printf("\n");
        printf("No records found!"); // no record was found
    }

    printf("\n");
}

// define a function to print the whole file
void printfile(void)
{
    FILE *filePtr = fopen(FILENAME, "rb"); // open a file stream

    long sz = getSize(filePtr); // get the size of the file in bytes
    printf("Allocating %ld bytes of memory.\n", sz);

    PERSON *records = malloc(sz); // allocate memory of size in bytes
    PERSON *original = records; // initialise a PERSON pointer

    while (!feof(filePtr)) // while the file stream has not ended
    {
        fread(records++, sizeof(PERSON), 1, filePtr); // read the next record into memory
    }

    int numRecords = sz / sizeof(PERSON); // calculate total number of records

    for (int i = 0; i < numRecords; i++) // go through all records
    {
        PERSON *current = original++; // increment the pointer and assign the value
        printf("First Name: %s\n", current->firstname);
        printf("Last Name: %s\n", current->famname);
        printf("Personnummer: %s\n", current->pers_number);
        printf("============\n");
    }

    fclose(filePtr); // close the stream
}

void write_new_file(PERSON *inrecord) // function to write a new file
{
    FILE *filePtr = fopen(FILENAME, "wb"); // open a file stream in binary write mode
    fwrite(inrecord, sizeof(PERSON), 1, filePtr); // write the dummy data
    fclose(filePtr); // close the stream
}

long getSize(FILE *file) // function to get the size of the file in bytes
{
    fseek(file, 0L, SEEK_END); // go to end of file
    long sz = ftell(file);     // get the size of the file
    fseek(file, 0L, SEEK_SET); // go back to beginning of file
    return sz; // return the size in bytes
}

_Bool fileExists(char *fileName) // function to check if a file exists
{
    return access(fileName, F_OK) == 0; // return if the file exists
}