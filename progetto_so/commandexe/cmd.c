#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

#define MAX_CMD_LEN 100

int main() {
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
		execCommandAndLog(cmd, k);
		k = k + 1;
	}

	return (0);
}