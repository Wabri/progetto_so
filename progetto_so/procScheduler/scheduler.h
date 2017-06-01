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
void printAllTasks(Task*, Task*, char);
void printTask(Task*);
int checkEmptyList(Task*);
int execTask(Task*);
Task* selectTask(Task*);
int getExeNumber();
int getPriority();
void getTaskName(Task*);
Task* newTaskElement(Task*, int);
int executeTask(Task*, char);
void deleteTask(Task**);
void modifyExecNumb(Task*);
void modifyPriority(Task*);
char switchPolicy(char);

char* sepa = "+----+-----------+-----------+-------------------+ \n\r";

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	char policy = 'p';
	const char* header =
			".......................................................................\n\r";
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	Task *tmpTask;
	Task **list = &firstTask;
	printf("%s", header);
	printf("               This is a process scheduler\n\r");
	printf("%s", header);
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!\n\r");
			return 0;
		case 1:
			if (checkEmptyList(firstTask) == 1) {
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
			deleteTask(list);
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
		if (!checkEmptyList(firstTask)) {
			printAllTasks(firstTask, lastTask, policy);
		}
	}
	return 0;
}

Task* selectTask(Task* t) {
	int id;
	printf("Seleziona il task...\nInserisci l'ID : ");
	scanf("%d", &id);
	while (t->ID != id){
		if(t->nextTask==NULL){
			printf("Throw some error..");
			return NULL;
		}
		t = t->nextTask;
	}
	return t;
}

void deleteTask(Task **list) {
	Task *currT, *prevT;
	int id;
	printf("Seleziona il task...\nInserisci l'ID : ");
	scanf("%d", &id);
	/*for first task, indicate there is no previous */
	prevT = NULL;
	for (currT = *list; currT != NULL; prevT = currT, currT = currT->nextTask) {
		if (currT->ID == id) {  /* Found it. */
      			if (prevT == NULL) {
        		/* Fix beginning pointer. */
        		*list = currT->nextTask;
      			} else {
        		/*
         		* Fix previous node's next to
         		* skip over the removed node.
         		*/
        		prevT->nextTask = currT->nextTask;
      			}
		free(currT);
		return;
		}
	}
}

int executeTask(Task* actualTask, char pol) {
	return 0;
}

int executeTaskID(Task* actualTask) {
	actualTask = selectTask(actualTask);
	actualTask->remainingExe = actualTask->remainingExe - 1;
	if (actualTask->remainingExe == 0) {
		deleteTask(&actualTask);
		return 0;
	}
	return actualTask->remainingExe;
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

void printAllTasks(Task *first, Task *last, char pol) {
	printf("\n\rScheduling Policy: ");
	if (pol == 'p') {
		printf("PRIORITY ");
	} else if (pol == 'e') {
		printf("REMAINING EXECUTIONS ");
	}
	printf("\nThe list of tasks is: \n\r");
	printf("%s", sepa);
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
	printf("%s", sepa);
	Task* tmp = first;
	while (tmp != last) {
		printTask(tmp);
		tmp = (*tmp).nextTask;
	}
}

void printTask(Task *thisTask) {
	printf("| %d  + %d         + %s        + %d                | \n\r",
			thisTask->ID, thisTask->priority, thisTask->nameTask,
			thisTask->remainingExe);
	printf("%s", sepa);
}

Task* newTaskElement(Task *actualTask, int idT) {
	actualTask->ID = idT;
	getTaskName(actualTask);
	actualTask->priority = getPriority();
	actualTask->remainingExe = getExeNumber();
	(*actualTask).nextTask = malloc(sizeof(Task));
	return (*actualTask).nextTask;
}

void modifyPriority(Task *t) {
	t = selectTask(t);
	t->priority = getPriority();
	return;
}

void modifyExecNumb(Task *t) {
	t = selectTask(t);
	t->remainingExe = getExeNumber();
	return;
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
