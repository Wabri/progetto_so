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

int getChoice();
char switchPolicy(char);

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	char policy = 'p';
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
			if (isEmptyTaskList(firstTask) == 1) {
				break;
			}
			printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n\r");
			printf("This task has the value of:\n\r");
			printTask(firstTask);
			break;
		case 2:
			break;
		case 3:
			if (firstTask->ID == 0) {
				lastTask = newTaskElement(firstTask, idTraker);
			} else {
				lastTask = newTaskElement(lastTask, idTraker);
			}
			idTraker += 1;
			break;
		case 4:
			executeTask(firstTask, policy);
			break;
		case 5:
			deleteTask(firstTask);
			break;
		case 6:
			policy = switchPolicy(policy);
			break;
		case 7:
			modifyPriority(firstTask);
			break;
		case 8:
			modifyExecNumb(firstTask);
			break;
		default:
			flag = 0;
			break;
		}
		if (!isEmptyTaskList(firstTask)) {
			printListTasks(firstTask, lastTask, policy);
		}
	}
	return 0;
}

int getChoice() {
	printf("\n\rYou can choose to:\n\r");
	printf(" 0) Exit\n\r 1) Print a task\n\r 2) Print all tasks\n\r");
	printf(" 3) Create a new task\n\r 4) Execute Task\n\r");
	printf(" 5) Delete Task\n\r 6) Switch policy (default : PRIORITY)\n\r");
	printf(" 7) Modify priority\n\r 8) Modify number of remaining execution");
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
