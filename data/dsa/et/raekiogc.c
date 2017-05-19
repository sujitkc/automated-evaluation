#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};
void addedge(struct node* a[],int u,int v){
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=v;
	temp->next=a[u];
	a[u]=temp;
	/*struct node* temp1=(struct node*)malloc(sizeof(struct node));
	temp1->data=u;
	temp1->next=a[v];
	a[v]=temp1;*/
}
void DFS_visit(struct node* a[],int i,char color[])
{
	color[i]='g';
	struct node* q;
	q=a[i];
	printf("%d\n",q->data);
	/*while(q!=NULL)
	{
		if(color[q->data]=='g')
		{
			printf("there is a cycle");
		}
		
		else if(color[q->data]=='w')
		{
			DFS_visit(a,q->data,color);
		}
		q=q->next;
	}*/
}
void DFS(struct node *a[],int n)
{
	char color[n];
	for (int i = 1; i <n+1; i++)
	{
		color[i]='w';
	}
	struct node *p;
	for (int i = 1; i < n+1; i++)
	{
		p=a[i];
		if(p!=NULL && color[p->data]=='w')
		{

			DFS_visit(a,i,color);
		}

	}	
}
int main()
{
	int t,n,m,x,y;
	scanf("%d",&t);
	int j=0;
	while(j<t)
	{
		scanf("%d %d",&n,&m);
		struct node* a[n];
		for (int i = 1; i < n+1; ++i)
		{
		a[i]=NULL;
		}
		for(int k=0;k<m;k++)
		{
			scanf("%d %d",&x,&m);
			addedge(a,x,y);	
		}
		DFS(a,n);
	j++;
    }
	/*addedge(a,1,2);
	addedge(a,2,3);
	addedge(a,1,3);*/
	/*addedge(a,2,0);
	addedge(a,2,3);
	addedge(a,3,3);*/
	/*struct node*p;
	for(int i=0;i<4;i++)
	{
		p=a[i];
		while(p!=NULL)
		{
			printf("%d\t",p->data);
			p=p->next;
		}
		printf("\n");
	}*/
	

	return 0;
}