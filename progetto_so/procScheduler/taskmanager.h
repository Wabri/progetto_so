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
Task* newTaskElement(Task*,int);
void printTask(Task*);
void printListTask(Task*, Task*, char);
void deleteTask(Task**);

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
	int p = 0;
	do {
		printf("\n\rInserisci la priorita' richiesta : ");
		scanf("%i", &p);
		if (((p < 0) || (p > 10))) {
			printf("\n\rErrore, la priorita' blablabla \n\r");
		}
	} while ((p < 0) || (p > 10));
	return p;
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
	}
	return actualTask;
}

void modifyPriority(Task *t) {
	t = selectTask(t);
	t->priority = setPriority();
	return;
}

void modifyExecNumb(Task *t) {
	t = selectTask(t);
	t->remainingExe = setExeNumber();
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

void printListTasks(Task *first, Task *last, char pol) {
	printf("\n\rScheduling Policy: ");
	if (pol == 'p') {
		printf("PRIORITY ");
	} else if (pol == 'e') {
		printf("REMAINING EXECUTIONS ");
	}
	printf("\nThe list of tasks is: \n\r");
	printf("+----+-----------+-----------+-------------------+\n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI |\n\r");
	printf("+----+-----------+-----------+-------------------+\n\r");
	Task* tmp = first;
	while (tmp != last) {
		printTask(tmp);
		tmp = (*tmp).nextTask;
	}
}

void deleteTask(Task **list) {
	Task *currT, *prevT;
	int id;
	printf("Seleziona il task...\nInserisci l'ID : ");
	scanf("%d", &id);
	/*for first task, indicate there is no previous */
	prevT = NULL;
	for (currT = *list; currT != NULL; prevT = currT, currT = currT->nextTask) {
		if (currT->ID == id) { /* Found it. */
			if (prevT == NULL) {
				/* Fix beginning pointer. */
				*list = currT->nextTask;
			} else {
				/*
				 * Fix previous node's next to
				 * skip over the removed node.
				 */
				prevT->nextTask = currT->nextTask;
			}
			free(currT);
			return;
		}
	}
}
