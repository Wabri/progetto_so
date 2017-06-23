#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
 
#include "config.h"
#include "functions.h"
#include "listManage.h"

// init folder data to store pipes
int initDataFolder() {
	FILE *fp;

	fp = popen("mkdir -p data/", "r");
	if (fp == NULL) {
		printf("[Error] - Error initialing process folder\n");
		exit(1);
	}
	return 1;
}

//CTRL+C managing
void sigHandler_1(int signumber) {
    if(signumber == SIGINT){
        remove(CMD_PIPE_NAME);

    	exit(0);
    }
    
    return;
}

int main()
{
	initDataFolder();
	sleep(1); //in order to be sure of folder creation

	signal(SIGINT, sigHandler_1);

	int fd;
	int fd_client;
	
	char cmd[100];
	// char msg[MAX_MSG_LEN];
	char pid[10];
	char pipeName[20];
	char clientsList[150];
	
	char* p_pid;
	char* p_msg;
	char* p_pipeName;
	char* p_clientsList;

	//init clients list
    char* num;
    struct node *n;
    head=NULL;

	int res = mknod(CMD_PIPE_NAME, S_IFIFO|0666, 0); /* Create named pipe */
	if(res!=0){
		printf("%s\n", "[ERR] Problem creating pipe");
		return 1;
	}

	fd = open(CMD_PIPE_NAME, O_RDONLY); /* Open it for reading */
	if(fd==-1){
		printf("%s\n", "[ERR] Problem reading pipe");
		return 1;
	}

	if(DEBUG)
		printf("%s\n", "[DEBUG] Ready to read pipe ..");

	while (readLine (fd, cmd)){
		/* Receiving messages */
        if(DEBUG)
			printf ("[DEBUG] Received: %s\n", cmd);

		strtok_r(cmd, " ", &p_pid);
		strcpy(pid, p_pid); /* BANG!!! */
		int i_pid = atoi(pid);
		if(DEBUG)
			printf("[DEBUG] cmd->%c\n", cmd[0]);
		switch (cmd[0]){
			case '1':
				clients_insert(pid);
				break;
			case '2':
				p_clientsList = clients_display(n);
				// printf("%s\n", p_clientsList);

				// if(p_clientsList == NULL){
				// 	// printf("%s\n", "no clients");
				// 	sprintf(p_clientsList, "%s\n", "No Clients Connected");
				// 	// strcpy(p_clientsList, "No Clients Connected\0");
				// }
		        
		        if(DEBUG)
					printf("[DEBUG] %s\n", p_clientsList);

				p_pipeName = (char*)malloc(strlen(PIPES_PATH)+strlen(pid)+1);

				p_pipeName = concat(PIPES_PATH, p_pid);

				strcpy(pipeName, p_pipeName); /* BANG!!! */

				mknod(pipeName, S_IFIFO|0666, 0); /* Create named pipe */
				
				strcpy(clientsList, p_clientsList); /* BANG!!! */
				
				fd_client = open(pipeName, O_RDWR); /* Open it for writing */
				// printf("fd: %d\n", fd_client);
				write(fd_client, clientsList, sizeof(clientsList));

				// close(fd_client); /* Close pipe */
				
				if(DEBUG)
					printf("[DEBUG] SIGUSR1 TO PID %d\n", i_pid);

				kill(i_pid, SIGUSR1);
				break;		
			case '3':
				if(DEBUG){
					printf("[DEBUG] SENDING MESSAGE '%s' TO PID %d\n","", i_pid);
				}
				printf("cmd: %s\n", cmd);
				strtok_r(&p_pid[0], " ", &p_msg);
				printf("msg: %s\n", p_msg);

				// kill(i_pid, SIGUSR2);
				break;
			case '4':
			case '5':
				clients_delete(pid);
				break;

		}
	} 

	if(DEBUG)
		printf("%s\n", "End..");

	close (fd); /* Close pipe */
	unlink(CMD_PIPE_NAME); /* Remove used pipe */
}
