/*
 * taskmanager.h
 *
 *  Created on: 31 mag 2017
 *      Author: wabri
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
		printf("\n\rInserisci il numero di esecuzioni rimanenti : ");
		scanf("%i", &exeNum);
		if ((exeNum < 0) || (exeNum > 99)) {
			printf("\n\rErrore, il numex blabla \n\r");
		}
	} while ((exeNum < 0) || (exeNum > 99));
	return exeNum;
}

int setPriority() {
	int priority = 0;
	do {
		printf("\n\rInsert priority value: ");
		scanf("%i", &priority);
		if (((priority < 0) || (priority > 10))) {
			printf("\n\rPriority must have value between 0 and 10\n\r");
		}
	} while ((priority < 0) || (priority > 10));
	return priority;
}

void setTaskName(Task *actualTask) {
	char name[8];
	printf("\n\rAssegna un nome a questo task (max 8 caratteri) : ");
	scanf("%s", name);
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
	printf("Seleziona il task...\nInserisci l'ID : ");
	scanf("%d", &id);
	while (actualTask->ID != id) {
		actualTask = actualTask->nextTask;
		if (actualTask == NULL) {
			printf("\n\rThere is no Task with this ID\n\r");
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
	printf("+----+-----------+-----------+-------------------+\n\r");
}

void printListTasks(Task *first) {
	printf("\n\rThe list of tasks is: \n\r");
	printf("+----+-----------+-----------+-------------------+\n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI |\n\r");
	printf("+----+-----------+-----------+-------------------+\n\r");
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
	printf("There is no Task to delete!!");
	return first;
}

int executeTask(Task *thisTask) {
	if (thisTask != NULL) {
		thisTask->remainingExe -= 1;
		return thisTask->remainingExe;
	} else if (thisTask->remainingExe == 0) {
		printf("This task don\'t have no more execution to done");
		return 0;
	}
	printf("There is no Task to execute!!");
	return 0;
}
