/*
*
* PURPOSE : Show menu options
*
* RETURN : void
*
*/
void menu(){
    int menuChoice;

    printf("Menu 1\n");
    printf("~~~~~~~~~~\n");
    printf("1. Connect to server.\n");
    printf("2. Get clients connected to server.\n");
    printf("3. Write to client/s.\n");
    printf("4. Disconnect from server.\n");
    printf("5. Exit.\n");
    scanf("%d", &menuChoice);
    printf("\n");
    switch ( menuChoice ){
        case 1:
            connect();
            break;
        case 2:
            getClientsID();
            break;
        case 3:
            sendMessage();
            break;
        case 4:
            disconnect();
            break;
        case 5:
            disconnect();
            clientExit();
            break;
        default:
            printf("Please.. is not a joke. \n");
    }

    printf("\n");
    menu();
}

/*
*
* PURPOSE : Connect to server
*
* RETURN : void
*
*/
void connect(){    
    if(connected == 1){
        printf("%s\n", "Already connected");
        return;
    }
    
    printf("%s\n", "Connected");

    char str[7];

    sprintf(str, "1 %d", getpid()); // puts string into buffer
    
    write(fd, str, sizeof(str));
    
    connected = 1;

    return;
}

/*
*
* PURPOSE : Request the list of the clients connected to the server
*
* RETURN : void
*
*/
void getClientsID(){
    char str[7];
    char *s_pid;

    sprintf(s_pid, "%d", getpid());
    sprintf(str, "2 %s", s_pid); // puts string into buffer

    write(fd, str, sizeof(str));

    return;
}

/*
*
* PURPOSE : Clear old chars on a stream
*
* RETURN : void
*
*/
void clear_stream(FILE *in){
    int ch;
    
    clearerr(in);
    
    do
        ch = getc(in);
    while (ch != '\n' && ch != EOF);
    
    clearerr(in);
}

/*
*
* PURPOSE : Get the lenght of an int
*
* PARAMS : int -> int to measure
* RETURN : int -> lenght of the int passed
*
*/
int get_int_len(int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

/*
*
* PURPOSE : Send message to client(s) menu
*
* RETURN : void
*
*/
void sendMessage(){
    char msg[MAX_MSG_LEN];
    int confirm;
    int i = 1;

    //read the string message from STDIN
    clear_stream(stdin);
    printf("\nEnter the message: ");
    scanf("%[^\n]s", msg);

    //output the message to the STDOUT
    printf("Message entered : %s\n", msg);

    //message confirm
    printf("\nPress 1 to confirm, others to delete the message.. ");
    if(scanf("%d", &confirm)==1 && confirm==1){
        //confirmed
        if(DEBUG)
            printf("%s\n", "Start sending..");

        int k = 1;
        int pid;
        
        while (1) {
            printf("\nEnter the %dth pid destination (letters to return to Menù): ", k);
            
            if(scanf("%d", &pid)==1){    
                if(DEBUG)
                    printf("[DEBUG] pid entered: %d\n", pid);
                
                //send to pid
                int size = 5 + get_int_len(getpid()) + get_int_len(pid) + strlen(msg);
                char str[size];
                
                if(DEBUG)
                    printf("[DEBUG] str size: %d\n", size);

                sprintf(str, "3 %d %d %s", getpid(), pid, msg); // puts string into buffer
                
                if(DEBUG)
                    printf("[DEBUG] string to send: '%s'\n", str);
                
                write(fd, str, sizeof(str));


                k = k + 1;
            }else{
                clear_stream(stdin);
                break;
            }
        }

        if(DEBUG)
            printf("%s\n", "[DEBUG] End sending");
    
    }else{
        clear_stream(stdin);
        printf("%s\n", "Message aborted");
    }
        
    
    return;
}

/*
*
* PURPOSE : Disconnect from the server
*
* RETURN : void
*
*/
void disconnect(){
    if(connected == 0){
        printf("\n%s\n", "Already disconnected");
        return;
    }
    
    printf("\n%s\n", "Client disconnected");

    char str[7];

    sprintf(str, "4 %d", getpid()); // puts string into buffer
    
    write(fd, str, sizeof(str));
    
    connected = 0;

    return;
}

/*
*
* PURPOSE : Function to exit from client execution
*
* RETURN : void
*
*/
void clientExit(){
    close(fd);
    printf("%s\n", "Bye");
    exit(0);
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
            printf("    [DEBUG] SIGINT catched\n");

        printf("{/SIGNAL}\n");
        disconnect();
        clientExit();
    }
    return;
}

/*
*
* PURPOSE : Manage SIGUSR1 signal. When a SIGUSR1 is catched the client read from its named pipe
*
* PARAMS : int -> signal number
* RETURN : void
*
*/
void sigHandler_2(int signumber){

    if(signumber == SIGUSR1) {
        printf("\n{SIGNAL}\n");
        if(DEBUG)
            printf("    [DEBUG] SIGUSR1 catched\n");

        //READ RESPONSE FROM PROCESS PIPE
        char s_pid[10];
        int fd_client;
        char pipeName[20];
        char response[100];
        char *p_pipeName;

        sprintf(s_pid, "%d", getpid());


        p_pipeName = concat(PIPES_PATH, s_pid);

        // sprintf(p_pipeName,"%s %s",PIPES_PATH, s_pid);

        strcpy(pipeName, p_pipeName); /* BANG!!! */
        fd_client = open(pipeName, O_RDONLY); /* Open it for writing */
        
        if(DEBUG)
            printf("    [DEBUG] Reading from: %s ...\n", pipeName);
        
        readLine(fd_client, response);
        printf("    Received: %s\n", response);

        close(fd_client);

        char c[50];
        sprintf(c, "rm -f  %s",pipeName);
        FILE *fp = popen(c, "r");

        // closing files
        pclose(fp);
        printf("{/SIGNAL}\n");

    }   
}

/*
*
* PURPOSE : Manage SIGUSR2 signal. When a SIGUSR2 is catched the client had tried to send a message to a non existing client 
*
* PARAMS : int -> signal number
* RETURN : void
*
*/
void sigHandler_3(int signumber){

    if(signumber == SIGUSR2) {
        printf("\n{SIGNAL}\n");

        if(DEBUG)
            printf("    [DEBUG] SIGUSR2 catched.\n");

        printf("    Pid not found.\n");

        printf("{/SIGNAL}\n");
    }
}