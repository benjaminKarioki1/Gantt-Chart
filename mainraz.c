#include <stdio.h>
#include "InputAndDisplay.h"

void InputFunction(TaskInfo tasks[], int NumberOfTasks); // input function

void DisplayTasks(TaskInfo tasks[], int NumberOfTasks); // display function

int main() {
    int NumberOfTasks;

    printf("How many Tasks would you like to add?\n");
    scanf("%d", &NumberOfTasks);

    TaskInfo tasks[NumberOfTasks];

    InputFunction(tasks, NumberOfTasks); // call input

    DisplayTasks(tasks, NumberOfTasks); // call display

    return 0;
}
