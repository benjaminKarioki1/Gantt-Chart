
#include "testExample.h"
#include <string.h>  

int testExample(TaskInfo tasks[]) {
    
    strcpy(tasks[0].TaskName, "Task_1");
    tasks[0].StartMonth = 1;  
    tasks[0].EndMonth = 3;    
    tasks[0].dependencies = 0; 

    
    strcpy(tasks[1].TaskName, "Task_2");
    tasks[1].StartMonth = 2;  
    tasks[1].EndMonth = 5;    
    tasks[1].dependencies = 1;  
    strcpy(tasks[1].DependentTasks[0], "Task_1");

    
    strcpy(tasks[2].TaskName, "Task_3");
    tasks[2].StartMonth = 4;  
    tasks[2].EndMonth = 7;    
    tasks[2].dependencies = 1;  
    strcpy(tasks[2].DependentTasks[0], "Task_2");

    
    strcpy(tasks[3].TaskName, "Task_4");
    tasks[3].StartMonth = 6;  
    tasks[3].EndMonth = 9;    
    tasks[3].dependencies = 1;  
    strcpy(tasks[3].DependentTasks[0], "Task_3");

    
    strcpy(tasks[4].TaskName, "Task_5");
    tasks[4].StartMonth = 8;  
    tasks[4].EndMonth = 12;   
    tasks[4].dependencies = 1;  
    strcpy(tasks[4].DependentTasks[0], "Task_4");

    
    return 5;
}