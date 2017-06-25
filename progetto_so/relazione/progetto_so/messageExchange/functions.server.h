/*
*
* PURPOSE : Create the data folder to store named pipes
*
* RETURN : void
*
*/
int initDataFolder() {
	FILE *fp;

	fp = popen("mkdir -p data/", "r");
	if (fp == NULL) {
		printf("[Error] - Error initialing process folder\n");
		exit(1);
	}

  	pclose(fp);

	return 0;
}

/*
*
* PURPOSE : Manage SIGINT signal (CTRL+C)
*
* PARAMS : int -> signal number
* RETURN : void
*
*/
void sigHandler_1(int signumber) {
    if(signumber == SIGINT){
        printf("\n{SIGNAL}\n");
        if(DEBUG)
            printf("	[DEBUG] SIGINT catched\n");

        int killed;
        remove(CMD_PIPE_NAME);
        // here we have to insert a while to send SIGINT to all clients to disconnect to this server
    	killed = clients_killer(n);
    	if(DEBUG)
    		printf("	[DEBUG] killed %d clients\n", killed);
        printf("{/SIGNAL}\n");
    	exit(0);
    }
    return;
}

/*
*
* PURPOSE : Send text to a pid client. Create a named pipe with the destination pid value, write the text and send.
*
* PARAMS : char* -> destination pid
* PARAMS : char* -> string to send
* RETURN : void
*
*/
void sendTextToClient(char* pid, char* p_textToSend){
	char pipeName[20];
	char* p_pipeName;
	int fd_client;
	char c_textToSend[strlen(p_textToSend)+1];

	strcpy( c_textToSend, p_textToSend );

	p_pipeName = (char*)malloc(strlen(PIPES_PATH)+strlen(pid)+1);
	p_pipeName = concat(PIPES_PATH, pid);
	strcpy(pipeName, p_pipeName); /* BANG!!! */
	mknod(pipeName, S_IFIFO|0666, 0); /* Create named pipe */
	if(DEBUG)
		printf("[DEBUG] Writing '%s' (size: %lu) to '%s'\n", c_textToSend, sizeof(c_textToSend), pipeName);
	fd_client = open(pipeName, O_RDWR); /* Open it for writing */
	
	int res = write(fd_client, c_textToSend, sizeof(c_textToSend));
	if(DEBUG)
		printf("[DEBUG] Written %d elements\n", res);
	// close(fd_client); /* Close pipe */

}