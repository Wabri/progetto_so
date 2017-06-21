// //function to manage clientList

// struct LIST {
// 	char * pid;
// 	struct LIST *next;
// 	// struct LIST *previous;
// };
// typedef struct LIST List ;

// //INIT NEW NODE
// void clientListNewNode(List * node){
// 	node = (List*)malloc(sizeof(List));
// 	node->next = NULL;
// 	// node->previous = NULL;
// 	node->pid = "x";
// 	return;
// }

// //ADD
// void clientListAddNode(List *tail, char* pid){
// 	if(tail->pid == "x"){
// 		//it's the first element
// 		printf("%s\n", "FIRST!");
// 		tail->pid = pid;
// 		return;
// 	}

// 	List * newNode;

// 	newNode = malloc(sizeof(List));
// 	newNode->pid = pid;
// 	newNode->next = NULL;
// 	// newNode->previous = tail;
// 	// printf("newnode %p\n", newNode);
// 	tail->next = newNode;
// 	tail = newNode;
// 	// printf("New tail addr : %p\n", tail);
// 	// printf("New pid tail : %s\n", tail->pid);
// 	return;
// }

// void printList(List* head){
// 	List * node = head;

// 	printf("List: %s, ", node->pid);
// 	while(node->next!=NULL){
// 		printf("%s, ", node->pid);
// 		node = node->next;
// 	}
// }

#include<stdio.h>
#include<stdlib.h>
 
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
    	return NULL;

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
 
 
// int  main()
// {
//     int i,num;
//     struct node *n;
//     head=NULL;
//     while(1)
//     {
//     printf("\nList Operations\n");
//     printf("===============\n");
//     printf("1.Insert\n");
//     printf("2.Display\n");
//     printf("3.Size\n");
//     printf("4.Delete\n");
//     printf("5.Exit\n");
//     printf("Enter your choice : ");
//     if(scanf("%d",&i)<=0){
//         printf("Enter only an Integer\n");
//         exit(0);
//     } else {
//         switch(i)
//         {
//         case 1:      printf("Enter the number to insert : ");
//                  scanf("%d",&num);
//                  insert(num);
//                  break;
//         case 2:     if(head==NULL)
//                 {
//                 printf("List is Empty\n");
//                 }
//                 else
//                 {
//                 printf("Element(s) in the list are : ");
//                 }
//                 display(n);
//                 break;
//         case 3:     printf("Size of the list is %d\n",count());
//                 break;
//         case 4:     if(head==NULL)
//                 printf("List is Empty\n");
//                 else{
//                 printf("Enter the number to delete : ");
//                 scanf("%d",&num);
//                 if(delete(num))
//                     printf("%d deleted successfully\n",num);
//                 else
//                     printf("%d not found in the list\n",num);
//                 }
//                 break;
//         case 5:     return 0;
//         default:    printf("Invalid option\n");
//         }
//     }
//     }
//     return 0;
// }
