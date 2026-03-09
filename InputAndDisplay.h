
#ifndef INPUT_AND_DISPLAY_H
#define INPUT_AND_DISPLAY_H


#include <stdio.h>

#include <stdlib.h> 

#define Max_Size 65

#define Max_Tasks 10

// Enumeration for months so the program uses symbolic names instead of raw integers
// Values start at 1 to match user input (1=January ... 12=December)
enum Month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};


typedef struct {
    // Store the task name as a fixed-size character array
    char TaskName[65];
    // Store names of tasks that this task depends on
    // Can handle up to 10 dependencies, each up to 64 characters (+ 1 for null terminator)
    char DependentTasks[10][65];
    // Starting month for the task (JANUARY..DECEMBER using enum Month)
    enum Month StartMonth;
    // Ending month for the task (must be >= StartMonth)
    enum Month EndMonth;
    // Number of dependencies this task has (0 means independent task)
    int dependencies;
} TaskInfo;

   // These are declared here so they can be used across multiple source files


void inputFunction(TaskInfo tasks[], int NumberOfTasks); 


void DisplayTasks(TaskInfo tasks[], int NumberOfTasks);


void clearChart();


#endif 