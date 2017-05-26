#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 100

// init folder ../commandexe/data/[pid] to store the logs
int initDataFolder(){
	char cmd[30];
	FILE *fp;

	sprintf(cmd,"%s%i","mkdir -p ../commandexe/data/",getpid());

	fp = popen(cmd, "r");

	if (fp == NULL){
		printf("[Error] - Error initialing process folder\n");
		exit(1);
	}
	
	return 0;
}

// function that execute the c command and log the output in ../commandexe/data/[pid]/out.[index]
int execCommandAndLog( char* c, int index)
{
	FILE *fp;
	char path[1035];
	char filename[7];

	sprintf(filename,"../commandexe/data/%i/%s.%i",getpid(),"out",index);
	FILE *f = fopen(filename, "w");
	if (f == NULL){
		printf("[Error] - Error opening file!\n");
		exit(1);
	}

	// command open to read
	sprintf(c,"%s %s",c,"2>&1");
	fp = popen(c, "r");

	if (fp == NULL) {
		fprintf(f, "[Error] - Error executing the command\n");
	}

	// read the output a line at a time - output it.
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		fprintf(f,"%s", path);
	}

	// closing files
	pclose(fp);
	fclose(f);

	return 0;
}

int cmd_yuri() {
	int k = 1;
	

	initDataFolder();

	while (1) {
		char cmd[MAX_CMD_LEN] = "";
		printf("\nEnter the %d-cmd: ", k);

		//read chars until \n
		scanf("%[^\n]", cmd);
		getchar();

		printf("Cmd entered : %s\n", cmd);

		if (strlen(cmd) == 0) {
			printf("Bye!\n");
			exit(1);
		}

		execCommandAndLog(cmd,k);

		k = k + 1;

	}

	return (0);
}