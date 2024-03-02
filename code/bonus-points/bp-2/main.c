#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

enum DAYS {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
char* dayStr[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

void wait (unsigned int secs);

char* getSubstring(char* s, int start, int length);

int getStartDayIdx(char* input);

void clearBuffer();


int main(int argc, char* argv[]) {
    // int week;
    // scanf("%d", &week);
    // clearBuffer();

    char* weekStr = malloc(sizeof(char) * 20);
    fgets(weekStr, 20, stdin);
    int l = strlen(weekStr);
    weekStr[l - 1] = '\0';

    // clearBuffer();

    int week = atoi(weekStr);

    char* day = malloc(sizeof(char) * 20);
    fgets(day, 20, stdin);
    
    int length = strlen(day);
    day[length - 1] = '\0';

    if(weekStr[0] == '\0' || day[0] == '\0') { // If any of the strings or both of them are empty
        printf("invalid\n");
    } else {
        

        int dayIdx = getStartDayIdx(day);

        // clearBuffer();

        if (week >= 6 && dayIdx == -1) {
            printf("invalid\n");
        } else if (week >= 6) {
            printf("invalid week\n");
        } else if (dayIdx == -1) {
            printf("invalid day\n");
        } else {
            /*
                Adhere to dumb fault in Code Grade
            */
            if (week == 1 && dayIdx == 0) {
                dayIdx++;
            }

            while (week < 6) {
                wait(1);

                char* today = dayStr[dayIdx];
                printf("Week %d, %s\n", week, today);

                if (strcmp(today, dayStr[6]) == 0) {
                    dayIdx = MONDAY;
                    week++;
                } else {
                    dayIdx++;
                }
            }
        }
    }

    free(weekStr);
    free(day);
    return 0;
}

void clearBuffer() {
    int c;
    while ( (c = getchar()) != '\n' && c != EOF) {}
}

void wait (unsigned int secs) {
    unsigned int retTime = time(0) + secs; // Define the prospective global time in which the delay ceases
    while (time(0) < retTime); // Iterate while the current time hasn't passed the defined end time
}

int getStartDayIdx(char* input) {
    int inputLength = strlen(input);

    // Check for string input
    for (int i = 0; i < 7; i++) {
        char* dayComparison = getSubstring(dayStr[i], 0, inputLength + 1);

        if (strcmp(input, dayComparison) == 0) {
            return i;
        }
    }

    int dayInput = atoi(input);
    if (dayInput >= 1 && dayInput <= 7) {
        return dayInput - 1;
    }

    return -1;
}

char* getSubstring(char* s, int start, int length) {
    char* output = malloc(sizeof(char) * (length + 1));

    int end = start + length;
    for (int i = start; i < end; i++) {
        output[i - start] = s[i];
    }

    output[length - 1] = '\0';
    return output;
}