/*
 * scheduler.h
 *
 *  Created on: 25 mag 2017
 *      Author: wabri
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "taskmanager.h"

int runScheduling(void);
int getChoice(void);
char switchPolicy(char pol);
Task* sortListByPriority(Task*, Task*);
Task* sortListByExecution(Task*, Task*);
Task* swapTask(Task*, Task*, Task*);
void swapTasks(Task**, Task**, Task**b);
Task* getPreviousTask(Task*, Task*);

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
			if (firstTask->ID == 0) {
				lastTask = newTaskElement(firstTask, idTraker);
			} else {
				lastTask = newTaskElement(lastTask, idTraker);
				printListTasks(firstTask, lastTask);
				if (policy == 'p') {
//					firstTask = sortListByPriority(firstTask, lastTask);
				} else if (policy == 'e') {
//					firstTask = sortListByExecution(firstTask, lastTask);
				}
			}
			idTraker += 1;
			break;
		case 2:
			if (executeTask(firstTask) == 0) {
				firstTask = deleteTask(firstTask, firstTask, lastTask);
			}
			break;
		case 3:
			tmpTask = selectTask(firstTask);
			if (executeTask(tmpTask) == 0) {
				firstTask = deleteTask(firstTask, tmpTask, lastTask);
			}
			break;
		case 4:
			firstTask = deleteTask(firstTask, selectTask(firstTask), lastTask);
			break;
		case 5:
			modifyPriority(firstTask);
			if (policy == 'p') {
//				firstTask = sortListByPriority(firstTask, lastTask);
			}
			break;
		case 6:
			policy = switchPolicy(policy);
			if (policy == 'p') {
//				firstTask = sortListByPriority(firstTask, lastTask);

			} else if (policy == 'e') {
//				firstTask = sortListByExecution(firstTask, lastTask);
			}
			break;
		case 7:
			modifyExecNumb(firstTask);
			if (policy == 'e') {
//				firstTask = sortListByExecution(firstTask, lastTask);
			}
			break;
		default:
			flag = 0;
			break;
		}
		if (!isEmptyTaskList(firstTask)) {
			printf("\n\rScheduling Policy: ");
			if (policy == 'p') {
				printf("PRIORITY ");
			} else if (policy == 'e') {
				printf("REMAINING EXECUTIONS ");
			}
			printListTasks(firstTask, lastTask);
		}
	}
	return 0;
}

int getChoice() {
	printf("\n\rYou can choose to:\n\r");
	printf(" 0) Exit\n\r 1) Create a new task\n\r 2) Execute head Task\n\r");
	printf(
			" 3) Execute id Task\n\r 4) Delete Task\n\r 5) Modify PRIORITY of Task\n\r");
	printf(
			" 6) Switch policy (default : PRIORITY)\n\r 7) Modify REMAINING EXECUTIONS of Task");
	int res = 0;
	printf("\n\r> ");
	scanf("%i", &res);
	return res;
}

char switchPolicy(char pol) {
	printf("\n\rYou switched the policy of scheduling from ");
	if (pol == 'p') {
		printf("PRIORITY ");
		printf("to ");
		printf("REMAINING EXECUTIONS\n\r");
		return 'e';
	} else if (pol == 'e') {
		printf("REMAINING EXECUTIONS ");
		printf("to ");
		printf("PRIORITY \n\r");
		return 'p';
	}
	return 'p';
}

Task* sortListByPriority(Task *headTask, Task *lastTask) {

}

Task* sortListByExecution(Task* headTask, Task *lastTask) {

}

Task* swapTask(Task *headTask, Task *task1, Task *task2) {
	if (headTask == task1) {
		headTask = task2;
	} else {
		Task *tempTask = headTask;
		while (tempTask->nextTask == task1) {
			tempTask = tempTask->nextTask;
		}
		tempTask->nextTask = task2;
	}
	task1->nextTask = task2->nextTask;
	task2->nextTask = task1;
	return headTask;
}
