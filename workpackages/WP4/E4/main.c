// (C) Nasit Vurgun, Joel Mattsson, Mohamad Khalil, group: 19 (2024)
// Work package 2
// Exercise 1
// Submission code: 755350

#include <stdio.h> // Include standard input output library

// Test-case arrays:
int test[] = {1,2,34,5,67,3,23,12,13,10}; // Array 1 of numerical values
int test2[] = {1,2,3,4,5,69,68,67,33,34}; // Array 2 of numerical values
int test3[] = {8,23,1,3,6,9,68,7,1,4}; // Array 3 of numerical values

// - - - FUNCTION PROTOTYPES - - -

// Swapping and searching prototypes
void swap(int a[], int i, int j);
void selectionSort(int a[], int n);
void bubbleSort(int a[], int n);
int linearSearch(int a[], int target, int n);

// Printing and testing prototypes
void runSearchingTestCases();
void runSortingTestCases();
void printArray(int a[], int n);

// Main: Logic
int main(int argc, char** argv)
{
    runSearchingTestCases(); // Run all associated test cases to 'linearSearch()'
    runSortingTestCases(); // Run all associated test cases to 'bubbleSort()' and 'selectionSort()'

    printf("\nExiting program...\n");
    return 0;
}

// Print an integer array of length 'n'
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) { // Iterate through all elements
        printf("%d ", a[i]);
    }
}

/*
    Run all test cases on the linear search method by executing it with different
    values passed as parameters and comparing them to the expected logical output.
*/
void runSearchingTestCases() {
    printf("TEST CASES - SEARCHING:\n");
    printf("%d\n", linearSearch(test, 2, 10)); // Expected output: 1
    printf("%d\n", linearSearch(test, 3, 10)); // Expected output: 5
    printf("%d\n", linearSearch(test, 10, 10)); // Expected output: 9
    printf("%d\n", linearSearch(test, 69, 10)); // Expected output: -1

    printf("%d\n", linearSearch(test2, 34, 10)); // Expected output: 9
    printf("%d\n", linearSearch(test2, 1, 10)); // Expected output: 0
    printf("%d\n", linearSearch(test3, 7, 10)); // Expected output: 7
    
    printf("\n\n");
}

/*
    Run all tests pertaining to sorting predefined integer arrays
*/
void runSortingTestCases() {
    printf("TEST CASES - SORTING:\n");

    bubbleSort(test, 10); // Sort array 'test' using bubblesort algorithm
    printf("test[] = ");
    printArray(test, 10); // Expected output: Sorted in ascending order

    printf("\n");

    selectionSort(test2, 10); // Sort array 'test2' using selectionsort algorithm
    printf("test2[] = ");
    printArray(test2, 10); // Expected output: Sorted in ascending order

    printf("\n");

    bubbleSort(test3, 10); // Sort array 'test3' using bubblesort algorithm
    printf("test3[] = ");
    printArray(test3, 10); // Expected output: Sorted in ascending order

    printf("\n");
}


/*
    Sort by finding the minimal element in the array and swapping it such that
    the leftmost (i:th) element is sorted.
*/
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) { // Go through all elements except the last one
        
        // Find the smallest integer in the current outerloop (in the right-sub-array that is unsorted)
        int jMin = i;
        for (int j = jMin; j < n; j++) { // Start iteration from jMin
            if (a[j] < a[jMin]) { // If current index element is the smallest one
                jMin = j; // Store index
            }
        }
        
        swap(a, i, jMin); // Swap current index with the minimal one found in the right-subarray of unsorted elements
    }
}


/*
    Sort by iterating such that continious swaps takes the shape of bubbles, where
    the maximal element always is sorted at the end of the array after the i:th
    iteration.
*/
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n; i++) { // Go through all elements
        for (int j = 0; i < n - j - 1; j++) { // Neglect the right-sub-array that is sorted, don't perform redundant iterations
            if (a[j] > a[j + 1]) { // If the two adjacent elements aren't ascending
                swap(a, j + 1, j); // Swap the two elements like a bubble
            }
        }
    }
}

// Swaps two elements in an array 'a' with its two indices 'i' and 'j'
void swap(int a[], int i, int j) {
    int temp = a[i]; // Temporary variable for swapping
    a[i] = a[j]; // Swap index i to j
    a[j] = temp; // Swap index j to i
}

// int* a
// a + n --> Points to address, therefore we have to dereference it
int linearSearch(int a[], int target, int n) {
    for (int i = 0; i < n; i++) { // Linearly go through all elements
        if (*(a + i) == target) { // Check if current value equates to the desired one we are searching for
            return i; // Return index if found
        }
    }
    return -1; // No element found, return -1
}