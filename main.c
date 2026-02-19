#include <stdio.h>
#include "InputAndDisplay.h"

void InputFunction(TaskInfo tasks[], int NumberOfTasks);

int main(){
    int NumberOfTasks;
    printf("How many Tasks would you like to add?\n");
    scanf("%d", &NumberOfTasks);
    TaskInfo tasks[NumberOfTasks];
    InputFunction(tasks, NumberOfTasks);
    return 0;

}