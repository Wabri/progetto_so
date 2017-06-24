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

#include "functions.inc.h"
#include "functions.client.h"

int main(){
    if(DEBUG)
        printf("[DEBUG] pid: %d\n", getpid());

    signal(SIGINT, sigHandler_1);
    signal(SIGUSR1 ,sigHandler_2); 
    signal(SIGUSR2 ,sigHandler_3);

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