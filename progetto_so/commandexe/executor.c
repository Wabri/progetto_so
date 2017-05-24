#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMN_LEN 100

int main(int argc, char *argv[])
{
    char cmd[MAX_CMN_LEN] = "", **p;
    int k = 0;
    FILE *f = fopen("out.k", "w");

    if (argc < 2) /*no command specified*/
    {
        fprintf(stderr, "Usage: ./program_name terminal_command ...");
        exit(EXIT_FAILURE);
    }
    else
    {
        strcat(cmd, argv[1]);
        for (p = &argv[2]; *p; p++)
        {
            strcat(cmd, " ");
            strcat(cmd, *p);
        }
        system(strcat(cmd," > out.k"));
        
	k = k + 1;
    }
    fclose(f);
    return 0;
}