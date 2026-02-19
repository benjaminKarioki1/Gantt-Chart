#ifndef INPUT_AND_DISPLAY_H
#define INPUT_AND_DISPLAY_H

#include <stdio.h>
#define Max_Size 65
#define Max_Tasks 10

typedef struct {
    char TaskName[65];
    char DependentTask[65];
    int StartMonth;
    int EndMonth;
    int dependencies;
} TaskInfo;

void InputFunction(TaskInfo tasks[], int NumberOfTasks);
#endif /* INPUT_AND_DISPLAY_H */