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
	int priority;
	int remainingExe;
	struct TaskElement *nextTask;
} Task;

int getChoice();
void printAllTasks(Task*, Task*);
void printTask(Task*);
int createID(Task*);
void getTaskName(Task*);
int getPriority();
int getExeNumber();
int checkEmptyList(Task*);
Task* newTaskElement(Task*, int);

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	Task *tmpTask;
	printf(".......................................................................\n\r");
	printf("               This is a process scheduler\n\r");
	printf(".......................................................................\n\r");
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!\n\r");
			return 0;
		case 1:
			if (checkEmptyList(firstTask) == 1)
				break;
			printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
			printf("This task has the value of:\n\r");
			printTask(firstTask);
			break;
		case 2:
			if (checkEmptyList(firstTask)){
				break;
			}
			printAllTasks(firstTask, lastTask);
			break;
		case 3:
			if (firstTask->ID == 0) {
				lastTask = newTaskElement(firstTask, idTraker);
				printTask(firstTask);
			} else {
				tmpTask = lastTask;
				lastTask = newTaskElement(lastTask, idTraker);
				printTask(tmpTask);
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

int checkEmptyList(Task *actualTask) {
	if (!(actualTask->ID)) {
		printf("\n\rList is empty! Please insert a task first...\n\r");
		return 1;
	}
	return 0;
}

int getExeNumber() {
	int exnum = 0;
	printf("\n\rInserisci il numero di esecuzioni rimanenti : ");
	scanf("%i", &exnum);
	if ((exnum < 0) || (exnum > 99)) {
		printf("\n\rErrore, il numex blabla \n\r");
		exnum = getExeNumber();
	}
	return exnum;
}

int getPriority() {
	int p = 0;
	printf("\n\rInserisci la priorita' richiesta : ");
	scanf("%i", &p);
	if ((p < 0) || (p > 10)) {
		printf("\n\rErrore, la priorita' blablabla \n\r");
		p = getPriority();
	}
	return p;
}

void getTaskName(Task *actualTask) {
	char name[8];
	printf("\n\rAssegna un nome a questo task (max 8 caratteri) : ");
	scanf("%s", name);
	strcpy(actualTask->nameTask, name);
	return;
}

int getChoice() {
	printf("You can choose to:\n\r");
	printf(
			" 0) Exit\n\r 1) Print a task\n\r 2) Print all tasks\n\r 3) Create a new task\n\r");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
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

Task* newTaskElement(Task *actualTask, int idT) {
	actualTask->ID = idT;
	getTaskName(actualTask);
//	strcpy(actualTask->nameTask, tmp);
	actualTask->priority = getPriority();
	actualTask->remainingExe = getExeNumber();
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}
