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
void sortTaskList(Task*, Task*, char);
Task* sortListByPriority(Task*, Task*);
Task* sortListByExecution(Task*, Task*);
void swapTask(Task*, Task*, Task*);
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
				if (policy == 'p') {
					firstTask = sortListByPriority(firstTask, lastTask);
				} else if (policy == 'e') {
					firstTask = sortListByExecution(firstTask, lastTask);
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
			firstTask = sortListByPriority(firstTask, lastTask);
			break;
		case 6:
			policy = switchPolicy(policy);
			if (policy == 'p') {
				firstTask = sortListByPriority(firstTask, lastTask);
			} else if (policy == 'e') {
				firstTask = sortListByExecution(firstTask, lastTask);
			}
			break;
		case 7:
			modifyExecNumb(firstTask);
			firstTask = sortListByExecution(firstTask, lastTask);
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

void sortTaskList(Task* first, Task* last, char pol) {
	if (pol == 'p') {
		sortListByPriority(first, last);
	} else if (pol == 'e') {
		sortListByExecution(first, last);
	}
}

Task* sortListByPriority(Task *first, Task *last) {
	Task *tmp;
	Task *newFirst = first;
	Task *previous;
	int flag = 0;
	while (!flag) {
		tmp = first;
		previous = first;
		flag = 1;
		while (tmp->nextTask->ID != 0) {
			if (tmp->nextTask->priority > tmp->priority) {
				if (tmp == first) {
					newFirst = tmp->nextTask;
				}
				swapTask(previous, tmp, tmp->nextTask);
				flag = 0;
			}
			if (tmp->nextTask->ID != 0) {
				tmp = tmp->nextTask;
				previous = tmp;

			}
		}
	}
	return newFirst;
}

Task* sortListByExecution(Task* first, Task *last) {
	Task *tmp;
	Task *newFirst = first;
	Task *previous;
	int flag = 0;
	while (!flag) {
		tmp = previous = first;
		flag = 1;
		while (tmp->nextTask->ID != 0) {
			if (tmp->nextTask->remainingExe < tmp->remainingExe) {
				if (tmp == first) {
					newFirst = tmp->nextTask;
				}
				swapTask(previous, tmp, tmp->nextTask);
				flag = 0;
			}
			if (tmp->nextTask->ID != 0) {
				previous = tmp;
				tmp = tmp->nextTask;
			}
		}
	}
	return newFirst;
}

void swapTask(Task *previous, Task *toMove, Task *following) {
	if (previous == toMove) {
		previous->nextTask = following;
	}
	toMove->nextTask = following->nextTask;
	following->nextTask = toMove;
}

void sortListPriority(Task **list, Task *firstTask) {
	Task *currT, *prevT;
	prevT = NULL;
	for (currT = *list; currT != NULL; prevT = currT, currT = currT->nextTask) {
		if ((currT->nextTask->priority) > (currT->priority)) {
			swapTasks(&firstTask, &currT, &(currT->nextTask)); // LOOPS FOREVER
		}
	}
	return;
}

void swapTasks(Task **head, Task **a, Task **b) {
	// first check if a agrgument is null
	if ((*head) == NULL ||               // Empty list
			(*a) == NULL || (*b) == NULL) {     // one node is null
		// Nothing to swap, just return
		printf("\n Nothing to swap, just return \n");
		return;
	}
	// find previos nodes
	Task* prevA = getPreviousTask(*head, *a);
	Task* prevB = getPreviousTask(*head, *b);

	//Now swap previous node's next
	if (prevA) {
		prevA->nextTask = (*b); // a's previous become b's previous, and
	}
	if (prevB) {
		prevB->nextTask = (*a); // b's previous become a's previous
	}

	//Now swap next fiels of candidate nodes
	Task* temp = (*a)->nextTask;
	(*a)->nextTask = (*b)->nextTask;
	(*b)->nextTask = temp;
	//change head: if any node was a head
	if ((*head) == (*a)) {
		*head = *b;
	} else {
		if ((*head) == (*b)) {
			*head = *a;
		}
	}
	return;
}

Task* getPreviousTask(Task* head, Task* a) {
	if (head == a) {
		// a is the first task
		return NULL;
	}
	Task* temp = head; 		// temp is current task
	Task* prevA = NULL;

	while (temp && temp != a) { 	//search while not reach to end or the task
		prevA = temp;          // find previous task
		temp = temp->nextTask;
	}
	if (temp != a) {			// node[a] not present in list
		fprintf(stderr, "\n error: node not found!\n");
		exit(EXIT_FAILURE); 	// bad technique to exit()
	}
	return prevA;
}
