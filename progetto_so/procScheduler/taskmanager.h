/*
 * taskmanager.h
 *
 *  Created on: 31 mag 2017
 *      Authors: wabri, pagano
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

typedef struct TaskElement {
	int ID;
	char nameTask[8];
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

void setTaskName(Task *actualTask) {
	char name[8];
	printf("\n\rName this task (max 8 chars) : ");
	scanf("%8s", name);
	strcpy(actualTask->nameTask, name);
	return;
}

int isEmptyTaskList(Task *actualTask) {
	if (!(actualTask->ID)) {
		printf("\n\rList is empty! Please insert a task first...\n\r");
		return 1;
	}
	return 0;
}

Task* selectTask(Task* actualTask) {
	int id;
	printf("Select the task...\nInsert the ID : ");
	scanf("%d", &id);
	while (actualTask->ID != id) {
		actualTask = actualTask->nextTask;
		if (actualTask == NULL) {
			printf("\n\rError! No tasks with this ID!\n\r");
			return actualTask;
		}
	}
	return actualTask;
}

void modifyPriority(Task *thisTask) {
	thisTask = selectTask(thisTask);
	if (thisTask == NULL) {
		return;
	}
	thisTask->priority = setPriority();
	return;
}

void modifyExecNumb(Task *thisTask) {
	thisTask = selectTask(thisTask);
	if (thisTask == NULL) {
		return;
	}
	thisTask->remainingExe = setExeNumber();
	return;
}

Task* newTaskElement(Task *actualTask, int idT) {
	actualTask->ID = idT;
	setTaskName(actualTask);
	actualTask->priority = setPriority();
	actualTask->remainingExe = setExeNumber();
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}

void printTask(Task *thisTask) {
	printf("| %d  + %d         + %s        + %d                | \n\r",
			thisTask->ID, thisTask->priority, thisTask->nameTask,
			thisTask->remainingExe);
	printf(SEPARATOR);
}

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
