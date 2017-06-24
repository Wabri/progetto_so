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
#include <math.h>

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
void ex_program(int);
void sigHandler_1(int);
void sigHandler_2(int);
void sigHandler_3(int);
// void sigHandler_4(int);
// void signal(SIGINT, ex_program);

int main()
{
    if(DEBUG)
        printf("[DEBUG] pid: %d\n", getpid());

    signal(SIGINT, sigHandler_1);
    signal(SIGUSR1 ,sigHandler_2); 
    signal(SIGUSR2 ,sigHandler_3);
    // signal(SIGUSR3, sigHandler_4) ;

    fd = open(myfifo, O_WRONLY);

    if(fd==-1){
        printf("%s\n", "[ERR]: server is not running");
        return 0;
    }

    printf("Hello. Welcome to the client.\n");
    printf("Press RETURN key to continue...\n");
    getchar();
    menu();

    
    return 0;
}

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
            disconnect();
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
    char str[7];
    char *s_pid;

    sprintf(s_pid, "%d", getpid());
    sprintf(str, "2 %s", s_pid); // puts string into buffer

    write(fd, str, sizeof(str));

    return;
}

void clear_stream(FILE *in)
{
    int ch;
    
    clearerr(in);
    
    do
        ch = getc(in);
    while (ch != '\n' && ch != EOF);
    
    clearerr(in);
}

int get_int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

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
            printf("\nEnter the %dth pid destination (letters to exit): ", k);
            
            if(scanf("%d", &pid)==1){    
                if(DEBUG)
                    printf("[DEBUG] pid entered : %d\n", pid);
                
                //send to pid
                int size = 5 + get_int_len(getpid()) + get_int_len(pid) + strlen(msg);
                char str[size];
                
                if(DEBUG)
                    printf("[DEBUG] str size %d\n", size);

                sprintf(str, "3 %d %d %s", getpid(), pid, msg); // puts string into buffer
                
                if(DEBUG)
                    printf("[DEBUG] string to send: %s\n", str);
                
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

//CTRL+C managing
void sigHandler_1(int signumber) {
    if(signumber == SIGINT){
        if(DEBUG)
            printf("[DEBUG] SIGINT catched.\n");

        disconnect();
        clientExit();
    }
    return;
}

//SIGUSR1 when the server has sent something to this client
void sigHandler_2(int signumber){


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
        
        if(DEBUG)
            printf("[DEBUG] Reading from: %s ...\n", pipeName);
        
        readLine(fd_client, response);
        printf("Received: %s\n", response);

        close(fd_client);
        // remove(pipeName);

        char c[50];
        sprintf(c, "rm -f  %s",pipeName);
        FILE *fp = popen(c, "r");

        // if (fp == NULL) {
        //     fprintf(f, "[Error] - Error executing the command\n");
        // }

        // read the output a line at a time - output it.
        // while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        //     fprintf(f, "%s", path);
        // }

        // closing files
        pclose(fp);

    }
    
}

//SIGUSR2 alert when a message is sent to a client who is not connected to the server
void sigHandler_3(int signumber){

    if(signumber == SIGUSR2) {
        if(DEBUG)
            printf("[DEBUG] SIGUSR2 catched.\n");

        printf("Pid not found.\n");
        // menu();
    }
    
    // menu();
}

// void sigHandler_4(int signumber) {
//     if (signumber == SIGUSR3) {
//         if (DEBUG) {
//             printf ("[DEBUG] SIGUSR3 carched.\n\r");
//         }
//         disconnect();
//     }
// }