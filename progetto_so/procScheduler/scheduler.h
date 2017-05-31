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

int getChoice();
void printAllTasks(Task*, Task*);
void printTask(Task*);
Task* newTaskElement(Task*, int, char[], int, int);

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	Task *tmpTask;
	printf("               This is a Scheduler Process\n\r");
	printf(
			".......................................................................\n\r");
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!!!\n\r");
			return 0;
		case 1:
			printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
			printf("This Task have the value of:\n\r");
			printTask(firstTask);
			break;
		case 2:
			printAllTasks(firstTask, lastTask);
			break;
		case 3:
			if (firstTask->ID == 0) {
				lastTask = newTaskElement(firstTask, idTraker, "test", 4, 5);
				printTask(firstTask);
				printTask(lastTask);
			} else {
				tmpTask = lastTask;
				lastTask = newTaskElement(lastTask, idTraker, "test", 4, 5);
				printTask(firstTask);
				printTask(tmpTask);
				printTask(lastTask);
			}
			idTraker += 1;
			break;
		case 4:

			break;
		case 5:

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
			" 0) Exit\n\r 1) Print Task\n\r 2) Print all tasks\n\r 3) Create new Task\n\r 4) Execution of Task\n\r 5) Delete task\n\r 6) Modify task priority\n\r 7) Switch scheduling policy");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
	printf("you choice %i \n\r", res);
	return res;
}

void printAllTasks(Task *first, Task *last) {
	printf("The list of task is: \n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
	Task* tmp = first;
	while (tmp != last) {
		printTask(tmp);
		tmp = (*tmp).nextTask;
	}
}

void printTask(Task *thisTask) {
	printf("+----+-----------+-----------+-------------------+ \n\r");
	printf("| %d  + %d         + %s        + %d                | \n\r",
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
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}
