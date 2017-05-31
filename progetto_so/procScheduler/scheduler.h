/*
 * scheduler.h
 *
 *  Created on: 25 mag 2017
 *      Author: wabri
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TaskElement {
	int ID;
	char nameTask[8];
	int priority; // number between 0 and 9
	int remainingExe; // max 99 execution per task
	struct TaskElement *nextTask;
} Task;

Task* newTaskElement(Task*, int, char[], int, int);
int getChoice();
void printAllTasks(Task*);
void printTask(Task*);
int createID(Task*);
char* getName(Task*);
int getPriority(Task*);
int getRemainingexecution(Task*);

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask; // the last Task is always empty
	lastTask = firstTask;
	printf("               This is a Scheduler Process\n\r");
	printf(
			".......................................................................\n\r");
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!!!\n\r");
			return 0;
		case 1:
			printAllTasks(firstTask);
			break;
		case 2:
			printTask(firstTask->nextTask);
			break;
		case 3:
			lastTask = newTaskElement(lastTask, idTraker, "test", 4, 5);
			idTraker += 1;
			break;
		default:
			flag = 0;
			break;
		}
	}
	return 0;
}

int getChoice() {
	printf("You can chose to:\n\r");
	printf(
			" 0) Exit\n\r 1) Print Task\n\r 2) Print all tasks\n\r 3) Create new Task\n\r");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
	printf("you choice %i \n\r", res);
	return res;
}

void printAllTasks(Task *first) {
	printf("The list of task is: \n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
	if (first->ID != 0) {
		for (Task *i = first; i == NULL; i = i->nextTask) {
			printf("+----+-----------+-----------+-------------------+ \n\r");
			printf("| %d + %d         + %s        + %d                | \n\r",
					i->ID, i->priority, i->nameTask, i->remainingExe);
			printf("+----+-----------+-----------+-------------------+ \n\r");
		}
	}
}

void printTask(Task *thisTask) {
	printf("This Task have the value of:\n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n\r");
	printf("| %d  + %d         + %s          + %d                 | \n\r",
			thisTask->ID, thisTask->priority, thisTask->nameTask,
			thisTask->remainingExe);
	printf("+----+-----------+-----------+-------------------+ \n\r");
}

Task* newTaskElement(Task *actualTask, int idT, char nameT[], int priorityT,
		int execT) {
	actualTask->ID = idT;
	strcpy(actualTask->nameTask, nameT);
	actualTask->priority = priorityT;
	actualTask->remainingExe = execT;
	actualTask->nextTask = malloc(sizeof(Task));
	return actualTask->nextTask;
}
