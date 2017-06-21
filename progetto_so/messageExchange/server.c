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


int main()
{
	int fd;
	int fd_client;
	
	char cmd[100];
	char pid[10];
	char pipeName[20];
	char clientsList[150];
	
	char* p_pid;
	char* p_pipeName;
	char* p_clientsList;

	//init clients list
    char* num;
    struct node *n;
    head=NULL;

	mknod (CMD_PIPE_NAME, S_IFIFO|0666, 0); /* Create named pipe */
	fd = open (CMD_PIPE_NAME, O_RDONLY); /* Open it for reading */
	

	while (readLine (fd, cmd)){
		/* Receiving messages */
        if(DEBUG)
			printf ("[DEBUG] Received: %s\n", cmd);

		strtok_r(cmd, " ", &p_pid);
		strcpy(pid, p_pid); /* BANG!!! */

		switch (cmd[0]){
			case '1':
				clients_insert(pid);
				break;
			case '2':
				p_clientsList = clients_display(n);
				if(&p_clientsList[0] == NULL)
					sprintf(p_clientsList, "%s\n", "No Clients Connected");
		        
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
				int i_pid = atoi(pid);
				
				if(DEBUG)
					printf("[DEBUG] SIGUSR1 TO PID %d\n", i_pid);

				kill(i_pid, SIGUSR1);
				break;		
			case '4':
				clients_delete(pid);
				break;
		}

	} 

	

	close (fd); /* Close pipe */
	unlink(CMD_PIPE_NAME); /* Remove used pipe */
}
