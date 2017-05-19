#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct adjnode
{
	int data;
	struct adjnode *next;
};

void append(struct node **head,int key)
{
	struct node *temp=(struct node*)malloc(sizeof(struct node)),*current;
	temp->data=key;
	temp->next=NULL;
	if(*head==NULL)
	{
		*head=temp;
	}
	else{
	temp->next=*head;
	*head=temp;
	}
}
int pop(struct node **head)
{
	int key;
	struct node *current,*prev;
	current=*head;
	key=current->data;
	*head=current->next;
	free(current);

	    return key;
}
void addnode(struct adjnode *arr[],int parent,int key)
{
	struct adjnode *temp=(struct adjnode*)malloc(sizeof(struct adjnode));
	temp->data=key;
	temp->next=NULL;
if(arr[parent]==NULL)
{
	arr[parent]=temp;
}
else
{
	temp->next=arr[parent];
	arr[parent]=temp;
}
}
void print_queue(struct adjnode *head)
{
	int temp=0;
	struct adjnode *current;
	current=head;
while(current!=NULL)

	{   
	
		printf("%d\t",current->data);

		current=current->next;
	}	
}
void print_graph(struct adjnode *arr[])
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		int sum[]={0};
		
		printf("%d->",i );
		
		print_queue(arr[i]);
	
		printf("\n");
	}
	
}
void DFS(struct adjnode *arr[],struct node *head,int vist_arr[])
{
int key,source_node=0,x;
struct adjnode *current,*temp;
struct node *currentptr;
append(&head,source_node);
vist_arr[source_node]=1;
while(head!=NULL)
{
key=pop(&head);
printf("%d\t",key);
current=arr[key];
while(current!=NULL)
{
	if(vist_arr[current->data]==0)
	{
	
	append(&head,current->data);
	
	vist_arr[current->data]=1;
	
   }
   
   current=current->next;
  
}
}
}
int main()
{
	int i,vist_arr[5];
	//struct node *head=NULL;
	struct adjnode *arr[5];
	for (i = 0; i < 5; ++i)
	{
		arr[i]=NULL;
		vist_arr[i]=0;
		/* code */
	}
	addnode(arr,0,1);
	addnode(arr,0,2);
	addnode(arr,1,3);
	addnode(arr,1,4);
	addnode(arr,2,1);
	addnode(arr,2,3);
	addnode(arr,2,2);
	addnode(arr,3,2);
	addnode(arr,3,4);
	addnode(arr,4,0);
	print_graph(arr);
	struct node *head=NULL,*current;

	DFS(arr,head,vist_arr);
}
