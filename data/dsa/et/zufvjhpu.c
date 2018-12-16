#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node
{
	int data;
	struct node *next;
	int colour;
	struct node *p;
};
struct stack
{
	struct node *node;
	struct stack * next;
}*top=NULL;
void add_edge(struct node *arr[],struct node *s,struct node *e);
struct node* pop();
void push(struct node *n);
struct node* dfs(struct node *arr[],int n);
void main()
{
	int t;
	scanf("%d",&t);
	int n,m;
	for(i=0;i<n;i++){
	sacnf("%d %d",&n,&m);
	}
	struct node *a,*b,*c,*d,*e,*f,*cur;
	int i;
	a = (struct node*)malloc(sizeof(struct node));
	b = (struct node*)malloc(sizeof(struct node));
	c = (struct node*)malloc(sizeof(struct node));
	d = (struct node*)malloc(sizeof(struct node));
	e = (struct node*)malloc(sizeof(struct node));
	f = (struct node*)malloc(sizeof(struct node));
	a->data=1;
	b->data=2;
	c->data=3;
	d->data=4;
	e->data=5;
	f->data=6;
	a->colour=0;
	b->colour=0;
	c->colour=0;
	d->colour=0;
	e->colour=0;
	f->colour=0;
	struct node *arr[6];
	arr[0]=a;
	arr[1]=b;
	arr[2]=c;
	arr[3]=d;
	arr[4]=e;
	arr[5]=f;
	add_edge(arr,a,b);
	add_edge(arr,a,d);
	add_edge(arr,b,c);
	add_edge(arr,b,d);
	add_edge(arr,d,e);
	add_edge(arr,e,c);
	add_edge(arr,e,b);
	add_edge(arr,f,c);
	add_edge(arr,f,e);
	for(i=0;i<6;i++)
	{
		cur=arr[i];
		while(cur!=NULL)
		{
			printf("%d\t",cur->data);
			cur = cur->next;
		}
		printf("\n");
	}
	dfs(arr,6);
}
void add_edge(struct node *arr[],struct node *s,struct node *e)
{
	struct node *new;
	new=(struct node*)malloc(sizeof(struct node));
	*new=*e;
	struct node *cur = arr[(s->data)-1];
	while(cur->next!=NULL)
		cur = cur->next;
	cur->next = new;
	new->next = NULL;
}
struct node* dfs(struct node *arr[],int n)
{
	struct node *u,*v;
	int i=0;
	while(i<n)
	{
		push(arr[i]);
		arr[i]->colour = 1;
		arr[i]->p=arr[i];
		while(top!=NULL)
		{
			u=pop();
			if(u->colour == 1)
			{
				i++;
				v=u->next;
				u->colour=2;
				while(v!=NULL)
				{
                     if(arr[(v->data)-1]->colour != 2)
					{
						push(arr[(v->data)-1]);
						arr[(v->data)-1]->colour=1;
						arr[(v->data)-1]->p=u;
					}
					v = v->next;
					 else if(arr[(v->data)-1]->colour == 2)
					{
						struct node* t=v;
					 	while(t!=u)
						{
							printf("%d\t",t->data);
						}
						exit(0);
					}
				}
			}
		}
	}
	printf("DAG");
}
void push(struct node *n)
{
	struct stack *newnode;
	newnode = (struct stack*)malloc(sizeof(struct stack));
	newnode->node=n;
	if (top==NULL)
		newnode->next =NULL;
	else
		newnode->next=top;
	top=newnode;
}
struct node* pop()
{
	struct stack *temp=top;
	if(top!=NULL)
	{
		top=temp->next;
		return temp->node;
	}
}
