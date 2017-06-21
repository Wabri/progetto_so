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

int connected = 0;
char * myfifo = CMD_PIPE_NAME;
int fd;


void menu();
void connect();
void getClientsID();
void sendMessage();
void disconnect();
void clientExit();
void ex_program(int sig);
// void signal(SIGINT, ex_program);

void menu()
{
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
            clientExit();
            break;
        default:
            printf("Please.. is not a joke. \n");
    }

    printf("\n");
    menu();
}

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

void getClientsID(){
    // int fd_client;

    char str[7];
    // char pipeName[15];
    // char response[100];

    char *s_pid;
    // char *p_pipeName;

    sprintf(s_pid, "%d", getpid());

    sprintf(str, "2 %s", s_pid); // puts string into buffer

    write(fd, str, sizeof(str));




    return;
}

void sendMessage(){
    return;
}

void disconnect(){
    if(connected == 0){
        printf("%s\n", "Already disconnected");
        return;
    }
    
    printf("%s\n", "Client disconnected");

    char str[7];

    sprintf(str, "4 %d", getpid()); // puts string into buffer
    
    write(fd, str, sizeof(str));
    
    connected = 0;

    return;
}

void clientExit(){
    close(fd);
    printf("%s\n", "Bye");
    exit(0);
}

void ex_program(int sig) {
    if(sig == 2){
        disconnect();
        clientExit();
    }
    
    return;
}

//Handler - Exiting process, OR reading from pipe
void sigHandler(int signumber){

    if(signumber == SIGUSR1) {
        if(DEBUG)
            printf("[DEBUG] SIGUSR1 catched.\n");

        //READ RESPONSE FROM PROCESS PIPE

        char s_pid[10];
        int fd_client;
        char pipeName[20];
        char response[100];
        char *p_pipeName;

        sprintf(s_pid, "%d", getpid());
        // printf("%s\n", s_pid);
        p_pipeName = concat(PIPES_PATH, s_pid);
        strcpy(pipeName, p_pipeName); /* BANG!!! */
        fd_client = open(pipeName, O_RDWR); /* Open it for writing */
        // printf("pipeName: %s\n", pipeName);
        readLine(fd_client, response);
        printf("Client list: %s\n", response);

        close(fd_client);

    }
    
    menu();
}

int main()
{
    signal(SIGINT, ex_program);
    signal(SIGUSR1 ,sigHandler); 

    fd = open(myfifo, O_WRONLY);

    if(fd==-1){
        printf("%s\n", "ERR: server is not running");
        return 0;
    }

    printf("Hello. Welcome to the client.\n");
    printf("Press RETURN key to continue...\n");
    getchar();
    menu();

    return 0;
}
