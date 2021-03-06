m#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "taskmanager.h"

int getChoice(void);
char switchPolicy(char pol);
Task* sortListByPriority(Task*);
Task* sortListByExecution(Task*);
Task* swapTask(Task*, Task*, Task*);

int main() {
	int idTraker = 1;
	int flag = 1;
	char policy = 'p';
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	printf(POINTSHEAD);
	printf("               This is a process scheduler\n\r");
	printf(POINTSHEAD);
	while (flag == 1) {
		Task *tmpTask;
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
					firstTask = sortListByPriority(firstTask);
				} else if (policy == 'e') {
					firstTask = sortListByExecution(firstTask);
				}
			}
			idTraker += 1;
			break;
		case 2:
			if (!isEmptyTaskList(firstTask)) {
			tmpTask = findPreviousTask(firstTask, lastTask);
				if (executeTask(tmpTask) == 0) {
					lastTask = tmpTask;
					lastTask->ID = lastTask->priority = 0;
					strcpy(lastTask->nameTask,"/0");
					lastTask -> nextTask = NULL;
				}
				printf("\n\r");
			}	
			break;
		case 3:
			if (!isEmptyTaskList(firstTask)) {
				tmpTask = selectTask(firstTask);
				if (executeTask(tmpTask) == 0) {
					firstTask = deleteTask(firstTask,tmpTask);
				}
			}
			break;
		case 4:
			if (!isEmptyTaskList(firstTask)) {
				firstTask = deleteTask(firstTask,selectTask(firstTask));
			}
			break;
		case 5:
			if (!isEmptyTaskList(firstTask)) {
				modifyPriority(firstTask);
				if (policy == 'p') {
					firstTask = sortListByPriority(firstTask);
				}
			}
			break;
		case 6:
			policy = switchPolicy(policy);
			if (policy == 'p') {
				firstTask = sortListByPriority(firstTask);
			} else if (policy == 'e') {
				firstTask = sortListByExecution(firstTask);
			}
			break;
		case 7:
			if (!isEmptyTaskList(firstTask)) {
				modifyExecNumb(firstTask);
				if (policy == 'e') {
					firstTask = sortListByExecution(firstTask);
				}
			}
			break;
		default:
			flag = 0;
			break;
		}
		if (!isEmptyTaskList(firstTask)) {
			printf("\n\rScheduling Policy: ");
			if (policy == 'p') {
				printf("PRIORITY \n\r");
			} else if (policy == 'e') {
				printf("REMAINING EXECUTIONS \n\r");
			}
			printListTasks(firstTask);
		} else {
			printf("\n\rList is empty! Please insert a task first...\n\r");
		}
	}
	return 0;
}

/*
*
* PURPOSE : Print menu and get the choice
* RETURN : int -> choice of the menu
*
*/
int getChoice() {
	printf("\n\rPlease select an option:\n\r");
	printf(" 0) Exit\n\r 1) Create a new task\n\r 2) Execute a task\n\r");
	printf(
			" 3) insert ID task and execute\n\r 4) Delete a task\n\r 5) Modify the PRIORITY of a task\n\r");
	printf(
			" 6) Switch policy (default : PRIORITY)\n\r 7) Modify the REMAINING EXECUTIONS of a task");
	int res = 0;
	printf("\n\r> ");
	scanf("%i", &res);
	return res;
}

/*
*
* PURPOSE : Switch the policy of the scheduler
* PARAMS : char pol -> actual policy of the scheduler
* RETURN : char -> new policy of the scheduler
*
*/
char switchPolicy(char pol) {
	printf("\n\rYou switched the policy of scheduling from ");
	if (pol == 'p') {
		printf("PRIORITY to REMAINING EXECUTIONS\n\r");
		return 'e';
	} else if (pol == 'e') {
		printf("REMAINING EXECUTIONS to PRIORITY \n\r");
		return 'p';
	}
	return 'p';
}

/*
*
* PURPOSE : Sort list by priority (highest priority, task most important)
* PARAMS : Task* headTask -> pointer of the first task of the list
* RETURN : Task* -> new pointer of first (head) task
*
*/
Task* sortListByPriority(Task *headTask) {
	Task *tempTask = headTask;
	Task *previousTempTask = tempTask;
	int flag = 0;
	while (!flag) {
		flag = 1;
		tempTask = headTask;
		previousTempTask = tempTask;
		while (tempTask->ID != 0) {
			if (tempTask->priority < tempTask->nextTask->priority) {
				if (tempTask == headTask) {
					headTask = swapTask(headTask, tempTask, tempTask->nextTask);
				} else {
					previousTempTask = swapTask(previousTempTask, tempTask,
							tempTask->nextTask);
				}
				flag = 0;
			}
			previousTempTask = tempTask;
			tempTask = tempTask->nextTask;
		}
	}
	return headTask;
}

/*
*
* PURPOSE : Sort list by priority (lowest remaining execution, task most important)
* PARAMS : Task* headTask -> pointer of the first task of the list
* RETURN : Task* -> new pointer of first (head) task
*
*/
Task* sortListByExecution(Task* headTask) {
	Task *tempTask = headTask;
	Task *previousTempTask = tempTask;
	int flag = 0;
	while (!flag) {
		flag = 1;
		tempTask = headTask;
		previousTempTask = tempTask;
		while (tempTask->ID != 0) {
			if ((tempTask->remainingExe > tempTask->nextTask->remainingExe)
					&& (tempTask->nextTask->remainingExe != 0)) {
				if (tempTask == headTask) {
					headTask = swapTask(headTask, headTask, headTask->nextTask);
				} else {
					previousTempTask = swapTask(previousTempTask, tempTask,
							tempTask->nextTask);
				}
				flag = 0;
			}
			previousTempTask = tempTask;
			tempTask = tempTask->nextTask;
		}
	}
	return headTask;
}

/*
*
* PURPOSE : Swap two task
* PARAMS : Task* previousTask -> pointer of the first task of the list
* PARAMS : Task* taskSwap1 -> pointer of first task to swap
* PARAMS : Task* taskSwap2 -> pointer of second task to swap
* RETURN : Task* -> pointer of the previous task
*
*/
Task* swapTask(Task *previousTask, Task *taskSwap1, Task *taskSwap2) {
	if (previousTask != taskSwap1) {
		previousTask->nextTask = taskSwap2;
		taskSwap1->nextTask = taskSwap2->nextTask;
		taskSwap2->nextTask = taskSwap1;
		return previousTask;
	}
	taskSwap1->nextTask = taskSwap2->nextTask;
	taskSwap2->nextTask = taskSwap1;
	return taskSwap2;
}
