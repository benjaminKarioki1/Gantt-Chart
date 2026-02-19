#include "InputAndDisplay.h"

void InputFunction(TaskInfo tasks[], int NumberOfTasks){
    int NumberOfTasks;
    printf("How many Tasks would you like to add?\n");
    scanf("%d", &NumberOfTasks);
    for (int i = 0; i < NumberOfTasks; i++) {
        printf("Enter the Task Name: ");
        scanf("%s", tasks[i].TaskName);
        printf("Enter the Start Month (1-12): ");
        scanf("%d", &tasks[i].StartMonth);
        printf("Enter the End Month (1-12): ");
        scanf("%d", &tasks[i].EndMonth);
        printf("Enter the Number of Dependencies: ");
        scanf("%d", &tasks[i].dependencies);
        if (tasks[i].dependencies > 0) {
            printf("Enter the Dependent Task: ");
            scanf("%s", tasks[i].DependentTask);
        }   
    }
}
