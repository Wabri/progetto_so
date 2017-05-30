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

int runScheduling() {
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask;
	lastTask = firstTask;
	newTaskElement(lastTask,10,"test",5,40);
	printf("name of first Task: %s \n\r", lastTask->nameTask);
}

void newTaskElement(Task *actualTask, int idT, char nameT[], int priorityT, int execT) {
	actualTask->ID = idT;
	strcpy(actualTask->nameTask,nameT);
	actualTask->priority = priorityT;
	actualTask->remainingExe = execT;
	actualTask->nextTask = malloc(sizeof(Task));
}
