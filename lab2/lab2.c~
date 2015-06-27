//Justin McCaffrey mccaffrey.31
#include <stdio.h>
#include <stdlib.h>

//the struct for a node in the linked list
struct node {
  int data;
  struct node * next;
};

//creates and returns a pointer to a node containing the input integer
struct node * createNode(int data){
    struct node * newNode=(struct node *)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

//inserts a node into the list so that they remain in numerical order and returns a pointer to the head node
struct node * insertNode(struct node * head,struct node * newNode){
    struct node * temp=head; 
    if(head==NULL){
	head=newNode;
    }
    else if((head->data)>(newNode->data)){
	newNode->next=head;
	head=newNode;
    }
    else{
    	while(temp->next!=NULL && (temp->next->data)<(newNode->data)){  
		temp=temp->next;
    	}
	if(temp->next!=NULL){
   		newNode->next=temp->next;
   		temp->next=newNode;
	}
	else{
		temp->next=newNode;
	}
    }
    return head;
}

//Deletes all nodes in the list
void freeList(struct node * head){
    if(head->next!=NULL){
        freeList(head->next);
    }
    free(head);
}

//deletes nodes with data==value and returns a pointer to the head node
struct node * deleteNode(int value, struct node * head){
    struct node * temp = head;
    struct node * prevTemp = NULL;
    while(temp!=NULL){
        if(temp->data==value){
            if(prevTemp==NULL){
                head=temp->next;
                free(temp);
		temp=head;
            }
            else{
                prevTemp->next=temp->next;
                free(temp);
                temp=prevTemp->next;
            }
        }
        else{
        prevTemp=temp;
        temp=temp->next;
        }
    }
    return head;
}


//prints the values of all nodes in the list
void printList(struct node * head){
    struct node * temp = head;
    while(temp!=NULL){
        printf("%d,",temp->data);
        temp=temp->next;
    }
    printf("%s","END\n");
}

//This program takes inputs to create, change, and print a linked list.
int main()
{ 
    int x=0,value;
    struct node * head=NULL;
    do{
    printf("%s","Enter:\n0 to quit\n1 to add new node\n2 to delete all nodes containing a certain value\n3 to print the list :");
    if(scanf("%d",&x)){
    switch (x){
    case 1 ://add new node
        printf("%s","Enter a value:");
        scanf("%d",&value);
        struct node * newNode=createNode(value);
        head=insertNode(head,newNode);
        break;
    case 2 ://remove all nodes with value
        printf("%s","Enter a value:");
        scanf("%d",&value);
        head=deleteNode(value,head);
        break;
    case 3 ://print list
        printList(head);
        break;
    default ://exit
        x=0;
    }}
    }while(x>0);
    printf("%s","exiting..");
    if(head!=NULL){
        freeList(head);
    }
    return 0;
}




