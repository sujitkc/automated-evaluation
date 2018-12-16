#include <stdio.h>
#include <stdlib.h>
struct graph
{
	char label;
	char color;
	int distance;
	int count;
	int discover;
	int finish;
	//struct graph *data;
	//struct graph *next;
	//struct node *parent;
};
int max=6;
int vertexcount=-1;
int count=-1;
struct graph *lstvertices[6];
//struct graph *stack=NULL;
int adjmatrix[6][6];
int timer=0;
#include <stdio.h>
void topdownheapify(int *heap,int i,int n)
{
	int l,r,j,t;
	l=2*i+1;
	r=2*i+2;
	while(r<=n)
	{
		if(*(heap+l)<*(heap+r))
		{
			j=l;
		}
		else
		{
			j=r;
		}
		if(*(heap+j)<*(heap+i))
		{
			//printf("appy");
			t=*(heap+i);
			*(heap+i)=*(heap+j);
			*(heap+j)=t;
			//
			//printf("%d",*(heap+i));

			i=j;
			l=2*i+1;
			r=2*i+1;
		}
		else
		{
			break;
		}
		//printf("%d",*(heap+i))
	}
}
void buildheap(int *h,int n)
{
	int i;
	i=n/2;
	while(i>=0)
	{
		topdownheapify(h,i,n);
		i--;
	}
	printf("build heap using topdownheapify");
	for(i=0;i<n;i++)
	{
		printf("%d ",*(h+i));
	}
}
//struct graph *stackk=NULL;



void insert(struct graph *node)
{
	struct graph *temp;
	temp=stackk;
	//temp=malloc(sizeof(struct graph));

	temp->data=node;
	temp->next=stackk;
	stackk=temp;
	if(stackk==NULL)/*list is empty, create first node*/
	{
		temp=malloc(sizeof(struct graph));
		temp->data=node;
		temp->next=NULL;
		stackk=temp;
	}
	else
	{}
		while(temp->next!=NULL)/*add a new node at last
		{
			temp=temp->next;                                  /* temp function always start from the beginning*/	
		}
		temp->next=malloc(sizeof(struct graph));
		temp->next->data=node;
		temp->next->next=NULL;
	}
}
printpath(struct node *temp)"
{
	if(temp==lstvertices[0])
	{
		printf("%d",lstvertices[0]);
	}
	else 
	{
		printpath(temp->parent);
		printf("%d",temp->label);
	}
	
}
struct graph *delete()
{
	struct graph *temp,*r;
	r=stackk->data;
	temp=stackk;
	stackk=temp->next;
	free(temp);
	return r;
}

void addedge(int start,int end,int weight)
{
	adjmatrix[start][end]=weight;
	adjmatrix[end][start]=weight;
}
void addvertex(char node)
{
	struct graph *vertex=malloc(sizeof(struct graph));
	vertex->label=node;
	vertex->color='W';
	//vertex->distance=-1;
	//vertex->parent=NULL;
	vertex->count=++count;
	printf("count=%d\n",vertex->count);
	vertexcount=vertexcount+1;
	lstvertices[vertexcount]=vertex;
}
void dfs(struct graph *temp,int n)
{
	int i;
	temp->color='G';
	timer=timer+1;
	temp->discover=timer;
	if(temp==n)
	{

		return;
	}


	//lstvertices[0]->distance=0;
	//insert(lstvertices[0]);
	//while(stackk!=NULL)
	//{
		//struct graph *u=delete();
		printf("%c ",temp->label);
		int p=temp->count;
		//printf("p=%d\n",p);
		for(i=0;i<=vertexcount;i++)
		{
			if(adjmatrix[p][i]>0 && lstvertices[i]->color=='W')
			{
				lstvertices[i]->color='G';
				//lstvertices[i]->distance=lstvertices[p]->distance+1;
				//lstvertices[i]->parent=lstvertices[p];
				//insert(lstvertices[i]);
				dfs(lstvertices[i]);
			}
		}
		temp->color='B';
		timer=timer+1;
		temp->finish=timer;

	//}
}
void djk( )
{
	lstvertices[0]->parent=lstvertices[0];
	lstvertices[0]->distance=0;
	lstvertices[0]->color='Y';
	while(heap)
	{
		u=deletemin()
		u->color='B';
		int p=u->count;
		//printf("p=%d\n",p);
		for(i=0;i<=vertexcount;i++)
		{
			if(adjmatrix[p][i]>0 && lstvertices[i]->color=='R')
			{
				lstvertices[i]->distance=u->distance + adjmatrix[i][u];
				lstvertices[i]='Y';
				add(lstvertices[i]);
			}
			else if(lstvertices[i]->color=='Y'adjmatrix[p][i]>0 && ) 
			{
				if(lstvertices[i]->distance>(lstvertices[p]+adjmatrix[p][u]))
				{
					lstvertices[i]->distance=lstvertices[p]->distance +adjmatrix[p][u];
					lstvertices[i]->parent=lstvertices[p]->label;
				}
				if(lstvertices[i]->distance==(lstvertices[p]+adjmatrix[p][u]))
				{
					lstvertices[i]->distance=lstvertices[p]->distance +adjmatrix[p][u];
					lstvertices[i]->parent->next=lstvertices[p]->label;
				}
				

			}


	}
}
int main()
{
	int i,j;
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			adjmatrix[i][j]=0;
		}
	}
	addvertex('0'); //0
	addvertex('1');  //1
	addvertex('2');  //2
	addvertex('3');  //3
	addvertex('4');
	addvertex('5');  //3
	addvertex('6');
	//4

	addedge(0,1,2);
	addedge(0,2,4);
	addedge(2,3,6);
	addedge(1,3,5);
	addedge(2,4,6);
	djk();
	printpath();

	return 0;
}
