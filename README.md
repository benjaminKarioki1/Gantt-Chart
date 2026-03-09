**Gantt Chart Generator**
**Students:** Benjamin Karioki, Abdulrazaq Alobaid
**Git Repository:** https://csgitlab.ucd.ie/BenjaminKarioki/gantt-chart


**How the Gantt Chart is Displayed**
The Gantt chart is printed in the terminal as an ASCII table. Each row represents a task and the columns represent the twelve months of the year.
To generate the chart, the program loops through each task and then loops through the months from January to December. If the current month is between the task’s start and end month, "XXX" is printed to indicate the task is active during that month. Otherwise the space is left blank.
We used formatted printf() statements with fixed column widths so that the task names, month columns, and dependency column remain aligned. The screen is cleared before each display so the updated chart appears cleanly.  

**Mapping Tasks to a Struct**
Each task is stored using a TaskInfo struct. The struct contains the task name, start month, end month, number of dependencies, and the names of dependent tasks.
Tasks are stored in an array of structs, allowing the program to manage up to ten tasks. We also used an enum to represent months instead of raw integers. This makes the code easier to read and ensures the months correspond to values from 1–12 entered by the user.

**Editing and Changing Tasks**
We implemented an edit feature that allows the user to modify an existing task by typing edit.
The program asks for the exact task name and searches the task array using a helper function that compares names using strcmp(). Once the task is found, the user is prompted to enter the updated task name, start month, end month, and dependencies. These values overwrite the existing values stored in the struct, and the Gantt chart is displayed again with the updated information.


**Searching for Circular Dependencies**
To detect circular dependencies, we implemented a recursive search similar to a depth-first search.
The program keeps track of visited tasks and also tracks the current recursion path. When checking dependencies, the function recursively follows each dependent task. If the algorithm encounters a task already in the current recursion stack, it indicates a circular dependency.

If this occurs, the program prints a warning message. Otherwise it confirms that the task dependencies are valid.
(Refer to line 73 of main.c for the full function)


**Our choice of Ascii Art**
We chose this piece of candy because of our shared interest in confectionaries. Hope you enjoy sweets just as much as we do :)


