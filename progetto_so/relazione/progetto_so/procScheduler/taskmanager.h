#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

typedef struct TaskElement {
	int ID;
	char nameTask[9]; // the ninth element of the name must be 
	int priority;
	int remainingExe;
	struct TaskElement *nextTask;
} Task;

int setExeNumber(void);
int setPriority(void);
void setTaskName(Task*);
int isEmptyTaskList(Task*);
Task* selectTask(Task*);
void modifyPriority(Task*);
void modifyExecNumb(Task*);
Task* newTaskElement(Task*, int);
void printTask(Task*);
void printListTasks(Task*);
Task* deleteTask(Task*, Task*);
int executeTask(Task*);

/*
*
* PURPOSE : Setter remainingExe member of struct TaskElement, this function is use by newTaskElement
* RETURN : int -> number of remaining execution
*
*/
int setExeNumber() {
	int exeNum = 0;
	do {
		printf("\n\rInsert the number of remaning executions : ");
		scanf("%i", &exeNum);
		if ((exeNum < 0) || (exeNum > 99)) {
			printf("\n\rError! It must be a number between 1 and 99. \n\r");
		}
	} while ((exeNum <= 0) || (exeNum > 99));
	return exeNum;
}

/*
*
* PURPOSE : Setter priority member of struct TaskElement, this function is use by newTaskElement
* RETURN : int -> number of priority 
*
*/
int setPriority() {
	int priority = 0;
	do {
		printf("\n\rInsert the priority (ascending order): ");
		scanf("%i", &priority);
		if (((priority < 0) || (priority > 9))) {
			printf("\n\rError! It must be a number between 1 and 9\n\r");
		}
	} while ((priority < 0) || (priority > 9));
	return priority;
}

/*
*
* PURPOSE : Setter name member of struct TaskElement, this function is use by newTaskElement
* PARAMS : Task* actualTask -> pointer of the task that want to set name
* RETURN : void
*
*/
void setTaskName(Task *actualTask) {
	char name[256];
	do {
		printf("\n\rName this task (max 8 chars) : ");
		scanf("%s", name);
		if (strlen(name)>0 && strlen(name)<=8) {
			strcpy(actualTask->nameTask, name);
			for (int i = strlen(name); i<=9 ;i++) {
				actualTask->nameTask[i] = '\0'; // this for cycle set all character of the name task with the null character
			}
			return;
		} else {
			printf("\n\rThe name of the task must be less than 8");
		}
	} while (strlen(name)>8);
	printf("Something went wrong\n\rThe name of the task it will be setted -default-");
	strcpy(actualTask->nameTask,"default\0");
	return;
}

/*
*
* PURPOSE : Check if the list is empty
* PARAMS : Task* firstTask -> pointer of the first (head) task of the list
* RETURN : int -> return 0 if the list is empty, return 1 if the list is not empty
*
*/
int isEmptyTaskList(Task *firstTask) {
	return !(firstTask->ID);
}

/*
*
* PURPOSE : It ask the ID of the Task and finds the Task with that ID
* PARAMS : Task* firstTask -> pointer of the first (head) task of the list
* RETURN : Task* -> return the pointer of the task found
*
*/
Task* selectTask(Task* firstTask) {
	int id;
	printf("Select the task...\nInsert the ID : ");
	scanf("%d", &id);
	while (firstTask->ID != id) {
		firstTask = firstTask->nextTask;
		if (firstTask == NULL) {
			printf("\n\rError! No tasks with this ID!\n\r");
			return firstTask;
		}
	}
	return firstTask;
}

/*
*
* PURPOSE : Modify the priority of the task
* PARAMS : Task* thisTask -> pointer of the task to change
* RETURN : void
*
*/
void modifyPriority(Task *thisTask) {
	thisTask = selectTask(thisTask);
	if (thisTask == NULL) {
		return;
	}
	thisTask->priority = setPriority();
	return;
}

/*
*
* PURPOSE : Modify the execution number of the task
* PARAMS : Task* thisTask -> pointer of the task to change
* RETURN : void
*
*/
void modifyExecNumb(Task *thisTask) {
	thisTask = selectTask(thisTask);
	if (thisTask == NULL) {
		return;
	}
	thisTask->remainingExe = setExeNumber();
	return;
}

/*
*
* PURPOSE : Allocate a new item in the list
* PARAMS : Task* actualTask -> pointer of the last task of the list
* PARAMS : int idT -> the id of the new task
* RETURN : Task* -> pointer of the new last task of the list
*
*/
Task* newTaskElement(Task *actualTask, int idT) {
	actualTask->ID = idT;
	setTaskName(actualTask);
	actualTask->priority = setPriority();
	actualTask->remainingExe = setExeNumber();
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}

/*
*
* PURPOSE : Print a single Task
* PARAMS : Task* thisTask -> pointer of the task to print
* RETURN : void
*
*/
void printTask(Task *thisTask) {
	printf("| %d  + %d         + %s        + %d                | \n\r",
			thisTask->ID, thisTask->priority, thisTask->nameTask,
			thisTask->remainingExe);
	printf(SEPARATOR);
}

/*
*
* PURPOSE : Print the list of the task
* PARAMS : Task* first -> printing start from this task
* RETURN : void
*
*/
void printListTasks(Task *first) {
	printf(SEPARATOR);
	printf("| ID + PRIORITY + TASK NAME + REMAINING EXEC |\n\r");
	printf(SEPARATOR);
	Task* tmp = first;
	while (tmp->ID != 0) {
		printTask(tmp);
		tmp = (*tmp).nextTask;
	}
}

/*
*
* PURPOSE : Delete a Task
* PARAMS : Task* first -> pointer of the first task of the list
* PARAMS : Task* thisTask -> pointer of the task to delete
* RETURN : Task* -> return the pointer of the first task of the list
*
*/
Task* deleteTask(Task *first, Task *thisTask) {
	if (thisTask != NULL) {
		Task *tmpTask = first;
		if (thisTask == first) {
			tmpTask = thisTask->nextTask;
			thisTask->ID = thisTask->priority = thisTask->remainingExe = 0;
			strcpy(thisTask->nameTask, "\0");
			thisTask->nextTask = NULL;
			return tmpTask;
		} else {
			while (tmpTask->nextTask == NULL) {
				if (tmpTask->nextTask == thisTask) {
					tmpTask->nextTask = thisTask->nextTask;
					thisTask->ID = thisTask->priority = thisTask->remainingExe =
							0;
					strcpy(thisTask->nameTask, "\0");
					thisTask->nextTask = NULL;
					return first;
				}
				tmpTask = tmpTask->nextTask;
			}
		}
	}
	printf("There is no task to delete!\n\r");
	return first;
}

/*
*
* PURPOSE : Execute a Task
* PARAMS : Task* thisTask -> pointer of the task to execute
* RETURN : Task* -> return the number of the remaining execution
*
*/
int executeTask(Task *thisTask) {
	if (thisTask != NULL) {
		thisTask->remainingExe -= 1;
		return thisTask->remainingExe;
	} else if (thisTask->remainingExe == 0) {
		printf("This task has no more executions to be done\n\r");
		return 0;
	}
	printf("There is no task to execute!\n\r");
	return 0;
}
