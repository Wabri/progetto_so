/*
 * scheduler.h
 *
 *  Created on: 25 mag 2017
 *      Author: wabri
 */
#include <string.h>

typedef struct TaskElement {
	int ID;
	char nameTask[8];
	int priority; // number between 0 and 9
	int remainingExe; // max 99 execution per task
	struct Task *nextTask; // task successivo
} Task;

void newTaskElement(Task*, int, char[], int, int);
int createID(Task*);
char* getName(Task*);
int getPriority(Task*);
int getRemainingExecution(Task*);


int runScheduling() {
	printf("               This is a Scheduler Process\n\r");
	printf(".......................................................................\n\r");
	Task *firstTask = malloc(sizeof(Task));
	Task *actualTask;
	actualTask = firstTask;
	while (1) {
		break;
	}
	return 0;
}

void newTaskElement(Task *actualTask, int idT, char nameT[], int priorityT,	int execT) {
	actualTask->ID = idT;
	strcpy(actualTask->nameTask, nameT);
	actualTask->priority = priorityT;
	actualTask->remainingExe = execT;
	actualTask->nextTask = malloc(sizeof(Task));
}
