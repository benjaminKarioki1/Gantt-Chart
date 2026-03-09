#include "InputAndDisplay.h"


// This determines horizontal spacing for task names
#define task_col_width 20
// Each month gets 9 character spaces for alignment (to fit "September")
#define month_col_width 9

#define deps_col_width 15


void inputFunction(TaskInfo tasks[], int NumberOfTasks){
    
    for (int i = 0; i < NumberOfTasks; i++) {
       
        printf("Please enter the task name\n");
        
        scanf("%s", tasks[i].TaskName);
        
        printf("Start month (1-12):\n");
        {
            int month;
            scanf("%d", &month);
            tasks[i].StartMonth = (enum Month)month;
        }
        printf("End month (1-12):\n");
        {
            int month;
            scanf("%d", &month);
            tasks[i].EndMonth = (enum Month)month;
        }
        
        printf("Enter how many dependencies this task has\n");
       
        scanf("%d", &tasks[i].dependencies);
        // Loop to read each dependent task name based on the dependency count
        for (int j = 0; j < tasks[i].dependencies; j++) {
           
            printf("Enter dependent task\n");
            
            scanf("%s", tasks[i].DependentTasks[j]);
        }
    }

}


void addTask(TaskInfo tasks[], int *NumberOfTasks) {
    if (*NumberOfTasks >= Max_Tasks) {
        printf("Cannot add more tasks – maximum of %d reached\n", Max_Tasks);
        return;
    }

    int i = *NumberOfTasks;           /* index of the new entry */

    printf("Please enter the task name\n");
    scanf("%s", tasks[i].TaskName);

    printf("Start month (1-12):\n");
    {
        int month;
        scanf("%d", &month);
        tasks[i].StartMonth = (enum Month)month;
    }
    printf("End month (1-12):\n");
    {
        int month;
        scanf("%d", &month);
        tasks[i].EndMonth = (enum Month)month;
    }

    printf("Enter how many dependencies this task has\n");
    scanf("%d", &tasks[i].dependencies);
    for (int j = 0; j < tasks[i].dependencies; j++) {
        printf("Enter dependent task\n");
        scanf("%s", tasks[i].DependentTasks[j]);
    }

    (*NumberOfTasks)++;              /* bump caller’s count */
}

void clearChart() {
    // Preprocessor directive to check if compiling for Windows
#ifdef _WIN32
    // Windows system command to clear the screen (cls = clear screen)
    system("cls");
#else
    // Unix/Linux/macOS system command to clear the screen
    system("clear");
#endif
}

// Helper function to map Month enum to string name
// Defined as static since it's only used within this file
static const char *getMonthName(enum Month m) {
    switch (m) {
        case JANUARY: return "January";
        case FEBRUARY: return "February";
        case MARCH: return "March";
        case APRIL: return "April";
        case MAY: return "May";
        case JUNE: return "June";
        case JULY: return "July";
        case AUGUST: return "August";
        case SEPTEMBER: return "September";
        case OCTOBER: return "October";
        case NOVEMBER: return "November";
        case DECEMBER: return "December";
        default: return "";
    }
}

void DisplayTasks(TaskInfo tasks[], int NumberOfTasks) {
    

    // Calculate the total width of the chart in characters for consistent formatting
    // Formula: task_col_width + (12 months × (1 pipe + month_col_width)) + 1 pipe + deps_col_width
    // With month_col_width=9, deps_col_width=15: 20 + (12 × 10) + 1 + 15 = 20 + 120 + 16 = 156 characters
    int real_width = task_col_width
                   + 12 * (1 + month_col_width)
                   + 1 + deps_col_width;
    
    // Clear the screen before displaying the new chart
    clearChart();
    
    // ========== PRINT TOP BORDER ==========
    // Loop to print the top dashed line (one dash per character width)
    for (int i = 0; i < real_width; i++) {
        // Print a single dash character
        putchar('-');
    }
    // Print newline to move to next line after the dashed border
    putchar('\n');

    // ========== PRINT HEADER ROW ==========
    // Print the task name column header with proper width formatting
    // "%-*s" means: left-align string with width of task_col_width characters
    printf("%-*s", task_col_width, "Task Name");

    // Loop through all 12 months to print month headers using enum values
    for (enum Month m = JANUARY; m <= DECEMBER; m++) {
        // Print pipe separator followed by month name from enum mapping
        printf("|%-*s", month_col_width, getMonthName(m));
    }
    // Print final column header for dependencies with fixed width
    printf("|%-*s\n", deps_col_width, "Dependencies");
    
    // print separator line
    // Print dashes below the header row
    for (int i = 0; i < real_width; i++) {
        putchar('-');
    }
    putchar('\n');

    // print task rows
    // Loop through each task to display its row in the chart
    for (int i = 0; i < NumberOfTasks; i++) {

        // Print the task name in the first column with padding
        printf("%-*s", task_col_width, tasks[i].TaskName);

        // Loop through months 1-12 to show task timeline
        // iterate through months using enum values for clarity
        for (enum Month m = JANUARY; m <= DECEMBER; m++) {
            // Check if the current month falls within the task's duration
            // StartMonth and EndMonth are stored using enum Month types
            if (m >= tasks[i].StartMonth && m <= tasks[i].EndMonth) {
                // Print "XXX" to indicate task is active in this month
                printf("|%-*s", month_col_width, "XXX");
            } else {
                // Print empty space if task is not active in this month
                printf("|%-*s", month_col_width, "");
            }
        }

        // Print the dependencies column after all month columns
        printf("| ");
        // Check if this task has dependencies
        if (tasks[i].dependencies == 0)
            // Print "0" if task has no dependencies
            printf("0");
        else {
            // Print each dependent task name, separated by commas
            for (int d = 0; d < tasks[i].dependencies; d++) {
                // Add comma separator between multiple dependencies (except before first)
                if (d > 0) printf(",");
                // Print the dependent task name
                printf("%s", tasks[i].DependentTasks[d]);
            }
        }

        // Print newline to move to next row
        putchar('\n');
        
        // print row separator
        // Print dashes below each task row for visual separation
        for (int j = 0; j < real_width; j++) {
            putchar('-');
        }
        putchar('\n');
    }
}