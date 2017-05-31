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
int checkEmptyList(Task*);
int getExeNumber();
int getPriority();
void getTaskName(Task*);
Task* newTaskElement(Task*, int);
void executionTask(Task*, char);
void deleteTask(Task*);
char switchPolicy(char);

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	char policy = 'p';
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	Task *tmpTask;
	printf(
			".......................................................................\n\r");
	printf("               This is a process scheduler\n\r");
	printf(
			".......................................................................\n\r");
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!\n\r");
			return 0;
		case 1:
			if (checkEmptyList(firstTask) == 1)
				break;
			printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n\r");
			printf("This task has the value of:\n\r");
			printTask(firstTask);
			break;
		case 2:
			if (checkEmptyList(firstTask)) {
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
//			executionTask(firstTask, policy);
			break;
		case 5:
			deleteTask(tmpTask);
			break;
		case 6:
			printf("\n\rYou change the policy of scheduling from ");
			if (policy == 'p') {
				printf("priority ");
			} else if (policy == 'e') {
				printf("remaining execution ");
			}
			policy = switchPolicy(policy);
			printf("to ");
			if (policy == 'p') {
				printf("priority \n\r");
			} else if (policy == 'e') {
				printf("remaining execution \n\r");
			}
			break;
		default:
			flag = 0;
			break;
		}
	}
	return 0;
}

int getChoice() {
	printf("\n\rYou can choose to:\n\r");
	printf(" 0) Exit\n\r 1) Print a task\n\r 2) Print all tasks\n\r");
	printf(" 3) Create a new task\n\r 4) Execute Task\n\r");
	printf(" 5) Delete Task\n\r 6) Switch policy\n\r");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
	return res;
}

void printAllTasks(Task *first, Task *last) {
	printf("The list of task is: \n\r");
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n\r");
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

Task* newTaskElement(Task *actualTask, int idT) {
	actualTask->ID = idT;
	getTaskName(actualTask);
	actualTask->priority = getPriority();
	actualTask->remainingExe = getExeNumber();
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}

void deleteTask(Task *actualTask) {
	while (1) {

	}
}

char switchPolicy(char pol) {
	if (pol == 'p') {
		return 'e';
	} else if (pol == 'e') {
		return 'p';
	}
	return 'p';
}
