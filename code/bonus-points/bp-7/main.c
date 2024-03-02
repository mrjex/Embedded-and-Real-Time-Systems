#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXBUFFER 100
#define NUMSTRINGS 5


typedef struct q {
    int element;
    struct q* next;
} Node;


void appendNode(Node* linkedList, int newElement, int* nP);
int findPreviousElement(Node* linkedList, int targetElement);
void clearBuffer();


int main(int argc, char* argv[])
{
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144
    
    int targetElement;
    scanf("%d", &targetElement);
    clearBuffer();
    
    int n = 0;
    int* nP = &n;
    
    Node* head = malloc(sizeof(Node));
    head->next = NULL;
    head->element = 0;
    (*nP)++;
    
    
    
    appendNode(head, 1, nP);
    appendNode(head, 1, nP);
    appendNode(head, 2, nP);
    appendNode(head, 3, nP);
    appendNode(head, 5, nP);
    appendNode(head, 8, nP);
    appendNode(head, 13, nP);
    appendNode(head, 21, nP);
    appendNode(head, 34, nP);
    appendNode(head, 55, nP);
    appendNode(head, 89, nP);
    appendNode(head, 144, nP);

    /*
    printf("LINKED LIST:\n");
    Node* iterationPos = head;
    while (iterationPos != NULL) {
        printf("%d\n", iterationPos->element);
        iterationPos = iterationPos->next;
    }
    */
    
    printf("%d\n", findPreviousElement(head, targetElement)); // Output
    return 0;
}

void appendNode(Node* linkedList, int newElement, int* nP) {
    Node* newNode = malloc(sizeof(Node));
    newNode->element = newElement;
    
    /*
    IMPLEMENTATION 2: Practice
    int startAddress = linkedList;
    int i = 0;
    while (i++ < *nP) {
        linkedList = linkedList.next;
    }
    
    linkedList.next = newNode;
    (*nP)++;
    */
    

    Node* currentPos = linkedList; // Points to the same address as the head of the linked list
    
    while (currentPos->next != NULL) {
        currentPos = currentPos->next;
    }
    
    currentPos->next = newNode;
}


int findPreviousElement(Node* linkedList, int targetElement) {
    Node* currentPos = linkedList;
    int previousElement = linkedList->element;
    
    while (currentPos->next != NULL) {
        
        if (currentPos->element == targetElement) {
            return previousElement;
        }
        
        previousElement = currentPos->element;
        currentPos = currentPos->next;
    }
    
    return previousElement;
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


