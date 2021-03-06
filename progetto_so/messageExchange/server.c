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

struct node *n;

int initDataFolder(void);
void sigHandler_1(int);
void sendTextToClient(char*,char*);
 
#include "functions.inc.h"
#include "listmanage.h"
#include "functions.server.h"

int main(){
	initDataFolder();

	signal(SIGINT, sigHandler_1);

	int i_fd;
	int i_pid_m;
	int i_pid_d;

	char cmd[100];
	char pid[10];
	
	char* p_pid_m;
	char* p_pid_d;
	char* p_msg;
	char* p_clientsList;
	char* p_token;

	//init clients list
    head=NULL;

	int res = mknod(CMD_PIPE_NAME, S_IFIFO|0666, 0); /* Create named pipe */
	if(res!=0){
		printf("%s\n", "[ERR] Problem creating pipe");
		return 1;
	}

	i_fd = open(CMD_PIPE_NAME, O_RDONLY); /* Open it for reading */
	if(i_fd==-1){
		printf("%s\n", "[ERR] Problem reading pipe");
		return 1;
	}

	if(DEBUG)
		printf("[DEBUG] Reading from pipe %s ..\n\n", CMD_PIPE_NAME);

	while (readLine(i_fd, cmd)){
		/* Receiving messages */
        if(DEBUG)
			printf("[DEBUG] Received: %s\n", cmd);

		char* cmd_detected = strtok(cmd, " ");
		// printf("%s\n", cmd_detected);
		char* p_pid_m = strtok(NULL, " ");
		// printf("%s\n", p_pid_m);


		strcpy(pid, p_pid_m); /* BANG!!! */
		i_pid_m = atoi(pid);
		
		if(DEBUG)
			printf("[DEBUG] cmd->%s | pid_m->%s\n", cmd_detected, p_pid_m);

		switch (cmd_detected[0]){
			case '1':
				clients_insert(pid);
				break;
			case '2':
				p_clientsList = clients_display(n);
				
				sendTextToClient(pid, p_clientsList);

				if(DEBUG)
					printf("[DEBUG] SIGUSR1 TO PID %d\n", i_pid_m);

				//notify client through SIGNAL SIGUSR1
				kill(i_pid_m, SIGUSR1);
				break;		
			case '3':

				p_pid_d = strtok(NULL, " ");
				p_msg = strtok(NULL, " ");

				while(p_token = strtok(NULL, " "))
					sprintf(p_msg, "%s %s", p_msg, p_token);


				if(DEBUG){
					printf("[DEBUG] pid_d->%s\n", p_pid_d);
					printf("[DEBUG] msg received: %s\n", p_msg);
				}


				if(clients_search(p_pid_d)==1){
					//if the client is connected, send the message
					i_pid_d = atoi(p_pid_d);			

					sendTextToClient(p_pid_d, p_msg);
					//notify client through SIGNAL SIGUSR1
					kill(i_pid_d, SIGUSR1);
				}else{
					//otherwise notify the client who request to send this message
					if(DEBUG)
						printf("[DEBUG] Client %s is not connected\n", p_pid_d);

					//send SIGUSR2 to client
					kill(i_pid_m, SIGUSR2);

				}

				break;
			case '4':
			case '5':
				clients_delete(pid);
				break;
		}

		printf("\n\r");
	} 

	if(DEBUG)
		printf("%s\n", "End..");

	close (i_fd); /* Close pipe */
    remove(CMD_PIPE_NAME);
}