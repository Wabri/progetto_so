/*
 * scheduler.h
 *
 *  Created on: 25 mag 2017
 *      Author: wabri
 */
#include <string.h>
#include <stdio.h>

typedef struct TaskElement {
	int ID;
	char nameTask[8];
	int priority; // number between 0 and 9
	int remainingExe; // max 99 execution per task
	struct Task *nextTask; // task successivo
} Task;

void newTaskElement(Task*, int, char[], int, int);
int getChoice();
void printTask(Task*);
int createID(Task*);
char* getName(Task*);
int getPriority(Task*);
int getRemainingExecution(Task*);

int runScheduling() {
	int flag = 1;
	Task *firstTask = malloc(sizeof(Task));
	Task *actualTask;
	actualTask = firstTask;
	printf("               This is a Scheduler Process\n\r");
	printf(
			".......................................................................\n\r");
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!!!\n\r");
			return 0;
		case 1:
			printTask(firstTask);
			break;
		case 2:
			newTaskElement(actualTask, 10, "test", 4, 5);
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
	printf(" 0) Exit\n\r 1) Print Tasks\n\r 2) Create new Task\n\r");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
	printf("you choice %i \n\r", res);
	return res;
}

void printTask(Task *first) {
	printf("The list of task is: \n\r");
	for (Task *i = (Task*)first; i == NULL; i =(Task*) i->nextTask) {
		printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
		printf("| %d + %d         + %s        + %d                | ", i->ID,
				i->priority, i->nameTask, i->priority);
		printf("+----+-----------+-----------+-------------------+ \n");
	}
}

void newTaskElement(Task *actualTask, int idT, char nameT[], int priorityT,
		int execT) {
	actualTask = malloc(sizeof(Task));
	actualTask->ID = idT;
	strcpy(actualTask->nameTask, nameT);
	actualTask->priority = priorityT;
	actualTask->remainingExe = execT;
	actualTask->nextTask = NULL;
}
