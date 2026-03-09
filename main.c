
#include <stdio.h>
#include <string.h>
#include "InputAndDisplay.h"
#include "testExample.h"

void printAsciiArt() {
    printf("        .\n");
    printf("      ,i \\\n");
    printf("    ,' 8b \\\n");
    printf("  ,;o  `8b \\\n");
    printf(" ;  Y8. d8  \\\n");
    printf("-+._ 8: d8. i:\n");
    printf("    `:8 `8i `8\n");
    printf("      `._Y8  8:  ___\n");
    printf("         `'---Yjdp  \"8m._\n");
    printf("              ,\"' _,o9   `m._\n");
    printf("              | o8P\"   _.8d8P`-._\n");
    printf("              :8'   _oodP\"   ,dP'`-._\n");
    printf("               `: dd8P'   ,odP'  do8'`.\n");
    printf("                 `-'   ,o8P'  ,o8P' ,8P`.\n");
    printf("                   `._dP'   ddP'  ,8P' ,..\n");
    printf("                      \"`._ PP'  ,8P' _d8'L..__\n");
    printf("                          `\"-._88'  .PP,'7 ,8.`-.._\n");
    printf("                               ``'\"--\"'  | d8' :8i `i.\n");
    printf("                                         l d8  d8  dP/\n");
    printf("                                          \\`' J8' `P'\n");
    printf("                                           \\ ,8F  87\n");
    printf("                                           `.88  ,'\n");
    printf("                                            `.,-' mh\n\n");
}

void InputFunction(TaskInfo tasks[], int NumberOfTasks);

int findTaskByName(TaskInfo tasks[], int n, char* name) {
    // Loop through each task in the array
    for(int i = 0; i < n; i++) {
        // Use strcmp() to compare the current task name with the search name
        // strcmp returns 0 if strings are identical
        if (strcmp(tasks[i].TaskName, name) == 0) {
            // If match found, immediately return the index
            return i;
        }
    }
    // If loop completes without finding a match, return -1 to indicate not found
    return -1;
}


void editTask(TaskInfo tasks[], int NumberOfTasks) {
    // Declare character array to store the task name user wants to edit
    char name[65];
    // Prompt user to enter the exact name of the task they want to change
    printf("Please enter the task name you wish to change exactly\n");
    // Read the task name from user input
    scanf("%s", name);
    // Search for the task using findTaskByName() function
    int index = findTaskByName(tasks, NumberOfTasks, name);
    // Check if task was found (index will be -1 if not found)
    if (index == -1) {
        // Display error message if task not found
        printf("Task not found\n");
        // Exit function early and return to caller
        return;
    }

    printf("Please enter the new task name or write its old one\n");

    scanf("%s", tasks[index].TaskName);

    printf("Start month (1-12):\n");
    {
        int month;
        scanf("%d", &month);
        tasks[index].StartMonth = (enum Month)month;
    }

    printf("End month (1-12):\n");

    {
        int month;
        scanf("%d", &month);
        tasks[index].EndMonth = (enum Month)month;
    }

    printf("Enter how many dependencies this task has\n");

    scanf("%d", &tasks[index].dependencies);
    // Loop to read each dependency task name based on dependency count
    for(int i = 0; i < tasks[index].dependencies; i++) {

        printf("Enter dependent task\n");
        // Read and store each dependent task name in the array
        scanf("%s", tasks[index].DependentTasks[i]);
    }
}

void printDependenciesRecursive(TaskInfo tasks[], int n, int index, int visited[], int isFirst) {
    // Check if this task has already been visited/processed
    if (visited[index]) {
        // If already visited, return early to avoid infinite loops
        return;
    }
    // Mark the current task as visited to prevent processing it again
    visited[index] = 1;
    // Print the current task name, prepend arrow only if not the first call
    if (!isFirst) {
        printf(" -> ");
    }
    printf("%s", tasks[index].TaskName);
    for (int d = 0; d < tasks[index].dependencies; d++) {
        // Find the index of the dependent task by searching for its name
        int depIndex = findTaskByName(tasks, n, tasks[index].DependentTasks[d]);
        // Check if the dependent task was found in the array
        if (depIndex != -1) {
            // Recursively call this function for the dependent task
            // This allows traversal of the entire dependency chain
            printDependenciesRecursive(tasks, n, depIndex, visited, 0);
        } else {
            // Warn if dependency name does not exist in the task list
            printf(" [Warning: dependency '%s' not found]", tasks[index].DependentTasks[d]);
        }
    }
}


int hasCycle(TaskInfo tasks[], int n, int index, int visited[], int recStack[]) {
    // Check if the current task has not been visited yet
    if (!visited[index]) {
        // Mark the current task as visited
        visited[index] = 1;
        // Mark the current task as part of the current recursion path
        // This distinguishes between "completely processed" and "currently processing"
        recStack[index] = 1;
        // Loop through each dependency of the current task
        for (int d = 0; d < tasks[index].dependencies; d++) {
            // Find the array index of the dependent task by name
            int depIndex = findTaskByName(tasks, n, tasks[index].DependentTasks[d]);
            // Check if the dependent task exists in the array
            if (depIndex != -1) {
                // If dependent task has not been visited, recursively check it for cycles
                if (!visited[depIndex] && hasCycle(tasks, n, depIndex, visited, recStack)) {
                    // If a cycle is found in the recursive call, return 1 (true)
                    return 1;
                }
                // If the dependent task is in the current recursion stack,
                // it means we have found a cycle (going back to a task we're already processing)
                else if (recStack[depIndex]) {
                    // Return 1 to indicate cycle detected
                    return 1;
                }
            }
        }
    }
    // Remove the current task from the recursion stack since we're done processing it
    // This allows the same task to appear in different branches of the dependency tree
    recStack[index] = 0;
    // Return 0 to indicate no cycle was found
    return 0;

}


void testDependencies(TaskInfo tasks[], int NumberOfTasks) {
    // Declare a character array to store the task name user wants to test
    char name[65];
    // Prompt user to enter the task name they want to check
    printf("Enter the task name to check dependencies\n");
    // Read the task name from user input
    scanf("%s", name);
    // Search for the task in the array using findTaskByName()
    int index = findTaskByName(tasks, NumberOfTasks, name);
    // Check if the task was found
    if (index == -1) {
        // If not found, display error message
        printf("Task not found\n");
        // Exit function early without performing the test
        return;
    }

    // Initialize the visited array to track which tasks have been processed
    // memset() fills all bytes with 0, meaning all tasks are initially unvisited
    int visited[Max_Tasks] = {0};
    // Initialize the recursion stack array to track tasks in the current path
    // This array helps detect cycles in the dependency graph
    int recStack[Max_Tasks] = {0};
    // Call hasCycle() to check if there are any circular dependencies
    // starting from the selected task
    int cycleFound = hasCycle(tasks, NumberOfTasks, index, visited, recStack);
    // Check if a cycle was detected
    if (cycleFound) {
        // Display warning message if circular dependency found
        printf("!!! Circular Dependency Found !!!\n");
    } else {
        // Display success message if no circular dependencies found
        printf("No circular dependencies found for this task.\n");
    }

    // Initialize a fresh visited array for the recursive dependency printing
    // This is separate from the cycle detection visited array
    int vis[Max_Tasks] = {0};
    // Call recursive function to print the entire dependency chain
    // This shows the path: Task -> Dep1 -> Dep2 -> ... -> Dep_n
    printDependenciesRecursive(tasks, NumberOfTasks, index, vis, 1);
    // Print a newline to end the dependency chain output
    printf("\n");
}


int main() {

    // Declare an array to hold up to Max_Tasks (10) TaskInfo structures
    TaskInfo tasks[Max_Tasks];
    // Variable to store the number of tasks user wants to create or will use
    int NumberOfTasks;
    // Character array to store user's choice (yes/no) as a string
    char choice[10];
    // Display welcome message to the user
    printf("Welcome to the Gantt Generator\n");
    // Ask user whether they want predefined example or create custom Gantt chart
    printf("Would you like to use the test example or create your own Gantt from scratch? (yes or no)\n");
    // Read user's response (yes/no)
    scanf("%s", choice);
    // Check if user chose to use the predefined example
    // strcmp returns 0 if strings are equal; check both "yes" and "Yes" variations
    if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0) {
        // Call function to load predefined example tasks
        // This initializes the tasks array with 5 sample tasks
        NumberOfTasks = testExample(tasks);
    } else {
        // User chose to create their own custom Gantt chart
        // Prompt user to enter the number of tasks they want to create
        printf("How many tasks would you like to add? (1-10)\n");
        // Read the number of tasks from user input
        scanf("%d", &NumberOfTasks);
        // Validate that the input is within acceptable range (1 to 10)
        if (NumberOfTasks < 1 || NumberOfTasks > 10) {
            // If invalid, display error message
            printf("Invalid number, setting to 1\n");
            // Default to 1 task if input is out of range
            NumberOfTasks = 1;
        }
        // Call inputFunction from InputAndDisplay.c to get task details from user
        // This function prompts user for task name, start/end months, and dependencies
        inputFunction(tasks, NumberOfTasks);
    }

    // Display the complete Gantt chart with all tasks and their timeline
    DisplayTasks(tasks, NumberOfTasks);
    // Enter the main program loop for interactive menu
    while (1) {
        // Display menu options to user
        printf("If you wish to edit the Gantt please type 'edit' / If you wish to run a test, type 'test' or to exit, type 'quit' and then press enter to execute your option.\n");
        // Declare character array to store user's menu selection
        char option[10];
        // Read the user's option from input
        scanf("%s", option);
        // Check if user selected "edit" option
        if (strcmp(option, "edit") == 0) {
            // Call editTask function to allow user to modify a task
            editTask(tasks, NumberOfTasks);
            // After editing, redisplay the updated Gantt chart
            DisplayTasks(tasks, NumberOfTasks);
        }
        // Check if user selected "test" option
        else if (strcmp(option, "test") == 0) {
            // Call testDependencies function to check for circular dependencies
            testDependencies(tasks, NumberOfTasks);
        }
        // Check if user selected "quit" option
        else if (strcmp(option, "quit") == 0) {

            break;
        }
        // Handle invalid option selection
        else {

            printf("Invalid option\n");
        }
    }
printf("Thank you for using out chart!");
void printAsciiArt();

    return 0;
}