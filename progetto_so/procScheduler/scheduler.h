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
	char* nameTask;
	int priority;
	int remainingExe;
	struct TaskElement *nextTask;
} Task;

Task* newTaskElement(Task*, int);
int getChoice();
void printAllTasks(Task*, Task*);
void printTask(Task*);
int createID(Task*);
void getTaskName(Task*);
int getPriority();
int getExeNumber();
int checkEmptyList(Task*);
char* sepa = "+----+-----------+-----------+-------------------+ \n\r";

int runScheduling() {
	int idTraker = 1;
	int flag = 1;
	char* header = 
			".......................................................................\n\r";
	Task *firstTask = malloc(sizeof(Task));
	Task *lastTask = NULL; // the last Task is always empty
	Task *tmpTask;
	printf("%s",header);
	printf("               This is a process scheduler\n\r");
	printf("%s",header);
	while (flag == 1) {
		switch (getChoice()) {
		case 0:
			printf("Bye!\n\r");
			return 0;
		case 1:
			if(checkEmptyList(firstTask)==1) break;
			printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
			printTask(firstTask);
			break;
		case 2:
			if(checkEmptyList(firstTask)==1) break;
			printAllTasks(firstTask, lastTask);
			break;
		case 3:
			if (firstTask->ID == 0) {
				lastTask = newTaskElement(firstTask, idTraker);
				printAllTasks(firstTask, lastTask);
			} else {
				tmpTask = lastTask;
				lastTask = newTaskElement(lastTask, idTraker);
				printAllTasks(firstTask, lastTask);
	
			}
			idTraker += 1;
			break;
		default:
			flag = 0;
			break;
		}
	}
	return 0;
}

int checkEmptyList(Task *t){
	if(t->ID == 0) {
		printf("\tList is empty! Please insert a task first...\n\r");
		return 1;
	}
	return 0;
}	

int getExeNumber(){
	int exnum = 0;
	printf("Inserisci il numero di esecuzioni rimanenti : ");
	scanf("%i",&exnum);
	while((exnum<0) || (exnum>99)){
		printf("\tERRORE! Il numero di esecuzioni rimanenti deve essere 0<N<100 \n");
		exnum = getExeNumber();
	}	
	return exnum;
}

int getPriority(){
	int p = 0;
	printf("Inserisci la priorita' richiesta : ");
	scanf("%i",&p);
	while((p<0) || (p>10)){
		printf("\tERRORE! La priorita' deve essere un numero 0<N<9\n");
		p = getPriority();
	}
	return p;
}

void getTaskName(Task *actualTask){
	char name[8];
	printf("Assegna un nome a questo task (max 8 caratteri) : ");
	scanf("%s",name);
	actualTask->nameTask = name;
	return;	
}

int getChoice() {
	printf("\nYou can choose to:\n\r");
	printf(
			" 0) Exit\n\r 1) Print a task\n\r 2) Print all tasks\n\r 3) Create a new task\n\r");
	int res = 0;
	printf("> ");
	scanf("%i", &res);
	return res;
}

void printAllTasks(Task *first, Task *last) {
	printf("\nThe list of tasks is: \n\r");
	printf(sepa);
	printf("| ID + PRIORITA\' + NOME TASK + ESECUZ. RIMANENTI | \n");
	Task* tmp = first;
	while (tmp != last) {
		printTask(tmp);
		tmp = (*tmp).nextTask;
	}
}

void printTask(Task *thisTask) {
	printf(sepa);
	printf("| %d  + %d         + %s        + %d                | \n\r",
			thisTask->ID, thisTask->priority, thisTask->nameTask,
			thisTask->remainingExe);
	printf(sepa);
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
