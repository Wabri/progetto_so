// #include<stdio.h>
// #include<stdlib.h>
 
struct node
{
    char data[10];
    struct node *next;
}*head;

 
int clients_count()
{
    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
        n=n->next;
        c++;
    }
    return c;
}
 
void clients_append(char* num)
{
    struct node *temp,*right;
    temp= (struct node *)malloc(sizeof(struct node));
    strcpy(temp->data, num);
    // temp->data=num;
    right=(struct node *)head;
    while(right->next != NULL)
        right=right->next;

    right->next =temp;
    right=temp;
    right->next=NULL;
}
 
 
void clients_add( char* num )
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    strcpy(temp->data, num);
    // temp->data=num;
    if (head== NULL)
    {
	    head=temp;
	    head->next=NULL;
    }
    else
    {
	    temp->next=head;
	    head=temp;
    }
}

void clients_addafter(char* num, int loc)
{
    int i;
    struct node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
        left=right;
        right=right->next;
    }
    temp=(struct node *)malloc(sizeof(struct node));
    // temp->data=num;
    strcpy(temp->data, num);

    left->next=temp;
    left=temp;
    left->next=right;
    return;
}
  
void clients_insert(char* num)
{
    int c=0;
    struct node *temp;
    temp=head;
    if(temp==NULL){
		// printf("%s\n", "ok");
	    clients_add(num);
    }
    else
    {
	    while(temp!=NULL)
	    {
	        if(temp->data<num)
	        c++;
	        temp=temp->next;
	    }
	    if(c==0)
	        clients_add(num);
	    else if(c<clients_count())
	        clients_addafter(num,++c);
	    else
	        clients_append(num);
    }
}
 
 
 
int clients_search(char* num)
{
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
        if(strcmp(temp->data,num)==0)
            return 1;
        
        prev=temp;
        temp= temp->next;
    }
    
    return 0;
}
 
 
int clients_delete(char* num)
{
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
        if(strcmp(temp->data,num)==0)
        {
            if(temp==head)
            {
                head=temp->next;
                free(temp);
                return 1;
            }
            else
            {
                prev->next=temp->next;
                free(temp);
                return 1;
            }
        }
        else
        {
            prev=temp;
            temp= temp->next;
        }
    }
    return 0;
}
 
 
char*  clients_display(struct node *r)
{
    char* clients;
    char*  toAdd;

    r=head;
    if(r==NULL)
        return "No Clients Connected";
    // printf("%s\n", r);
    while(r!=NULL)
    {
        // printf("%s ",r->data);
        toAdd = &(r->data)[0];
        // printf("%s ",toAdd);
        toAdd = concat(toAdd, " ");
        clients = concat(clients, toAdd);
        // clients += sprintf(clients,toAdd);
        // sprintf(clients, "%s %s", "ok", toAdd);

        r=r->next;
    }
    printf("\n");
    // printf("%s ",clients);
    return clients;
}

//send SIGINT to all clients connected.
//RETURN the count of the clients found.
int  clients_killer(struct node *r)
{
    int pid;
    int clientsKilled=0;

    r=head;
    if(r==NULL)
    	return 0;

    while(r!=NULL)
    {
        pid = atoi(r->data);
        if(DEBUG)
            printf("[DEBUG] pid to kill: %d\n",pid);

        kill(pid,SIGINT);
        clientsKilled += 1;
        r=r->next;
    }

    return clientsKilled;
}
