//struct
struct node{
    char data[10];
    struct node *next;
}*head;


/*
*
* PURPOSE : Get the number of clients connected
*
* RETURN :  int -> number of clients in the list
*
*/
int clients_count(){
    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL){
        n=n->next;
        c++;
    }
    return c;
}

/*
*
* PURPOSE : Append a node to the end of the concat list
*
* PARAMS : char *pid -> pid to add in the list 
* RETURN : void
*
*/
void clients_append(char* pid){
    struct node *temp,*right;
    temp= (struct node *)malloc(sizeof(struct node));
    strcpy(temp->data, pid);

    right=(struct node *)head;
    while(right->next != NULL)
        right=right->next;

    right->next =temp;
    right=temp;
    right->next=NULL;
}

/*
*
* PURPOSE : Add the first node in the concat list
*
* PARAMS : char *pid -> pid to add in the list 
* RETURN : void
*
*/
void clients_add( char* num ){
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    strcpy(temp->data, num);
    // temp->data=num;
    if (head== NULL){
	    head=temp;
	    head->next=NULL;
    }
    else{
	    temp->next=head;
	    head=temp;
    }
}

/*
*
* PURPOSE : Add the (i+1)-node in the concat list
*
* PARAMS : char *pid -> pid to add in the list 
* RETURN : void
*
*/
void clients_addafter(char* num, int loc){
    int i;
    struct node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++){
        left=right;
        right=right->next;
    }
    temp=(struct node *)malloc(sizeof(struct node));
    // temp->data=num;
    strcpy(temp->data, num);

    left->next=temp;
    left=temp;
    left->next=right;
}

/*
*
* PURPOSE : Insert a pid in the concat list
*
* PARAMS : char *pid -> pid to add in the list 
* RETURN : void
*
*/
void clients_insert(char* pid){
    int c=0;
    struct node *temp;
    temp=head;
    if(temp==NULL){
		// printf("%s\n", "ok");
	    clients_add(pid);
    }
    else{
	    while(temp!=NULL){
	        if(temp->data<pid)
	        c++;
	        temp=temp->next;
	    }
	    if(c==0)
	        clients_add(pid);
	    else if(c<clients_count())
	        clients_addafter(pid,++c);
	    else
	        clients_append(pid);
    }
}

/*
*
* PURPOSE : Search a client in the concat list
*
* PARAMS : char *pid -> pid to add in the list 
* RETURN : void
*
*/
int clients_search(char* pid){
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL){
        if(strcmp(temp->data,pid)==0)
            return 1;
        
        prev=temp;
        temp= temp->next;
    }
    
    return 0;
}

/*
*
* PURPOSE : Remove a client in the concat list
*
* PARAMS : char *pid -> pid to remove 
* RETURN : int -> 1 if removed, 0 otherwise
*
*/
int clients_delete(char* num){
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL){
        if(strcmp(temp->data,num)==0){
            if(temp==head){
                head=temp->next;
                free(temp);
                return 1;
            }
            else{
                prev->next=temp->next;
                free(temp);
                return 1;
            }
        }
        else{
            prev=temp;
            temp= temp->next;
        }
    }
    return 0;
}

/*
*
* PURPOSE : Get the pid list of the clients connnected
*
* PARAMS : struct node *r
* RETURN : char* -> string of clients connected
*
*/
char*  clients_display(struct node *r){
    char* clients = NULL;
    char*  toAdd;

    clients = malloc(0);
    
    r=head;
    if(r==NULL)
        return "No Clients Connected";
    
    while(r!=NULL){
        toAdd = &(r->data)[0];
        sprintf(clients, "%s %s", clients, toAdd);
        r=r->next;
    }

    return clients;
}

/*
*
* PURPOSE : Kill all clients connected to the server sending them a SIGINT signal
*
* PARAMS : struct node *r
* RETURN : int -> number of clients killed
*
*/
int  clients_killer(struct node *r){
    int pid;
    int clientsKilled=0;

    r=head;
    if(r==NULL)
    	return 0;

    while(r!=NULL){
        pid = atoi(r->data);
        if(DEBUG)
            printf("    [DEBUG] pid to kill: %d\n",pid);

        kill(pid,SIGINT);
        clientsKilled += 1;
        r=r->next;
    }

    return clientsKilled;
}