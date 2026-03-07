#include "InputAndDisplay.h"
#include <stdio.h>

void InputFunction(TaskInfo tasks[], int NumberOfTasks) {

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
        } else {

            tasks[i].DependentTask[0] = '\0';
        }
    }
}

void DisplayTasks(TaskInfo tasks[], int NumberOfTasks) {
    const char *monthNames[12] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    printf("\n=========================== GANTT CHART ===========================\n");
    printf("%-20s", "Task Name");
    for (int m = 0; m < 12; m++) {
        printf("%-5s", monthNames[m]);
    }
    printf("  Deps\n");
    // THIS IS A SEPERATOR LINE
    printf("------------------------------------------------------------------");
    printf("-----------------\n");

    // each row has a task
    for (int i = 0; i < NumberOfTasks; i++) {
        // Task name column
        printf("%-20s", tasks[i].TaskName);

        // 12 columns for the months in the year
        for (int m = 1; m <= 12; m++) {
            if (m >= tasks[i].StartMonth && m <= tasks[i].EndMonth) {
                printf("%-5s", "XXX");
            } else {
                printf("%-5s", "");     //for the blank parts
            }
        }

        // dependencies
        printf("  ");
        if (tasks[i].dependencies == 0) {
            printf("None");
        } else {
            printf("%s", tasks[i].DependentTask);
        }

        printf("\n");
    }

    printf("==================================================================\n\n");
}
