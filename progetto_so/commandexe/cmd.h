#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMN_LEN 100

char* parse(char cmd[]){

char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",cmd);
  pch = strtok (cmd," ");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ");
  }
  return 0;
}


int cmd()
{
    int k = 1;
    char cmd[MAX_CMN_LEN] = "";
    char* dhn;
    
    while(1)
    {
    	printf("Inserisci il %d comando: ", k);
	scanf("%s",&cmd);
        dhn = parse(cmd);
        printf("ecco il dhn : %s",dhn);
	if(cmd=="\n")
	{
	    printf("Error!");
	}
	
	// system(cmd);

	k = k+1;   

    }
    
    return(0);
    
}    


