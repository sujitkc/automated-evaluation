#include<stdio.h>
#include<stdlib.h>
struct node_et
{
	int v;
	int w;
	struct node_et *next;
};
struct vertex
{
	int v;
	int colour;
	int p;
	int r;
	int l;
	int longest;
	struct vertex *next;
};
struct h
{
	int v;
	int l;
};
struct vertex *stack=NULL;
void print_graph(struct node_et *vertices[], int n, int e)
{
	int i;
	struct node_et *sptr;
	for(i=0;i<n;i++)
	{
		sptr=vertices[i];
		while(sptr!=NULL&&sptr->next!=NULL)
		{
			printf("%d %d\n",sptr->v,sptr->w);
		}
		printf("%d %d\n",sptr->v,sptr->w);
	}
}
void make_graph(struct node_et *vertices[], int n, int e)
{
	int a,i;
	struct node_et *sptr;
	printf("Enter edge in form 'a b w' where w is weight of edge from a to b\n");
	for(i=0;i<e;i++)
	{
		struct node_et *t=malloc(sizeof(struct node_et));
		t->next=NULL;
		scanf("%d %d %d", &a, &(t->v), &(t->w));
		sptr=vertices[a];
		while(sptr!=NULL&&sptr->next!=NULL)
		{
			sptr=sptr->next;
		}
		if(sptr==NULL)
			vertices[a]=t;
		else
			sptr->next=t;
	}
}
void push(struct vertex * a)
{
	a->colour=1;
	struct vertex * sptr;
	if(stack==NULL)
	{
		stack=a;
	}
	else
	{
		a->next=stack;
		stack=a;
	}
}
struct vertex * pop()
{
	struct vertex *a=stack;
	if(stack->next==NULL)
		stack=NULL;
	else
		stack=stack->next;
	return a;
}
void dfs(struct node_et *vertices[],struct vertex *visited[], int n, int e)
{
	printf("Enter source\n");
	int k,i;
	/*scanf("%d",&k);*/
	for(k=0;k<n;k++)
	{
		push(visited[k]);
		visited[k]->r=visited[k]->r+1;
		visited[k]->p=k;
		while(stack!=NULL)
		{
				struct vertex *u=pop();
				if(visited[u->v]->colour==1)
				{
				visited[u->v]->colour=2;
				struct node_et *sptr=vertices[u->v];
				while(sptr!=NULL)
				{
					if(visited[sptr->v]->colour==0)
					{
						push(visited[sptr->v]);
						visited[sptr->v]->r=visited[sptr->v]->r+1;
						visited[sptr->v]->p=u->v;
					}
					else if(visited[sptr->v]->colour==1)
						visited[sptr->v]->p=u->v;
					sptr=sptr->next;
				}
				}
		}
		for(i=0;i<n;i++)
		{
			visited[i]->colour=0;
			visited[i]->p=0;
		}
	}
}
/*void display(int **num, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d	\t",num[i][1]);
	}
	printf("\n");
}*/
void topdown_heapify(struct h* arr[], int i,int n)
{
		int l=2*i+1, r=2*i+2, j;
		if(r<n)
		{
		if(arr[l]->l>arr[r]->l)
				j=r;
		else
				j=l;
		if(arr[j]->l>=arr[i]->l)
				j=i;
		if(j!=i)
			{
				struct h * t =arr[i];
				arr[i]=arr[j];
				arr[j]=t;
				topdown_heapify(arr,j,n);
			}
		}
		if(l==n-1&&arr[i]->l>arr[l]->l)
		{
			struct h *t =arr[i];
			arr[i]=arr[l];
			arr[l]=t;
		}	
}
void bottomup_heapify(struct h *arr[], int i)
{
	int p= (i-1)/2;
	if(p>=0)
	{
		if((arr[i]->l)<arr[p]->l)
		{
			struct h *t=arr[i];
			arr[i]=arr[p];
			arr[p]=t;
			bottomup_heapify(arr,p);
		}
	}
}
int del_min(struct h *a[],int * n)
{
	int m= a[0]->v;
	a[0]=a[(*n)-1];
	*n=*n-1;
	a= (struct h *)realloc(a,sizeof(struct h)*(*n));
	topdown_heapify(a,0,*n);
	return m;
	
}
/*void insert(struct vertex **a, int *n, struct vertex *t)
{
	*n=*n+1;
	a= (struct h *)realloc(a,sizeof(struct h)*(*n));
	a[*n-1]=t;
	bottomup_heapify(a,*n-1);
}*/
void decrease_key(struct h *arr[], int i, int k)
{
	arr[i]->l=k;
	bottomup_heapify(arr,i);
}
void increase_key(struct h *arr[], int i, int k, int n)
{
	arr[i]->l=k;
	topdown_heapify(arr,i,n);
}
void dijkstra(struct h *heap[], struct node_et *vertices[],struct vertex *visited[], int e, int n)
{
	int k,i=0;
	struct vertex *a;
	while(stack!=NULL)
	{
		for(i=0;i<n;i++)
		{
			visited[i]->colour=0;
			visited[i]->p=0;
		}
		a=pop();
		visited[a->v]->colour=1;
		visited[a->v]->p=a->v;
		visited[a->v]->l=0;
		while(n>0)
		{
				int u=del_min(heap,&n);
				visited[u]->colour=2;
				struct node_et *sptr=vertices[u];
				while(sptr!=NULL)
				{
					if(visited[sptr->v]->colour==0)
					{
						visited[sptr->v]->l=visited[u]->l+ sptr->w;
						visited[sptr->v]->colour=1;
						visited[sptr->v]->p=u;
						for(i=0;i<n;i++)
						{
							if(heap[i]->v==sptr->v)
								break;
						}
						decrease_key(heap,i,visited[sptr->v]->l);
					}
					else if(visited[sptr->v]->colour==1)
					{
						if((visited[sptr->v]->l)>visited[u]->l+ sptr->w)
						{
							visited[sptr->v]->l=visited[u]->l+ sptr->w;
							visited[sptr->v]->p=u;
							for(i=0;i<n;i++)
							{
								if(heap[i]->v==sptr->v)
									break;
							}
							decrease_key(heap, i, visited[sptr->v]->l);
						}
					}
					sptr=sptr->next;
				}
			
		}
		int m=0;
		for(i=0;i<n;i++)
		{
			if((visited[i]->l)>m)
				m=visited[i]->l;
			visited[i]->colour=0;
			visited[i]->p=0;
		}
		visited[a->v]->longest=m;
	}
}
int main()
{
	int n,e,i;
	struct node_et *sptr;
	printf("Enter no. of vertices in the graph\n");
	scanf("%d",&n);
	struct node_et * vertices[n];
	struct vertex * visited[n];
	for(i=0;i<n;i++)
	{
		vertices[i]=NULL;
	}
	for(i=0;i<n;i++)
	{
		struct vertex *t=malloc(sizeof(struct vertex));
		t->v=i;
		t->colour=0;
		t->p=0;
		t->next=NULL;
		t->r=0;
		t->l=0;
		t->longest=0;
		visited[i]=t;
	}
	printf("Enter no. of edges in graph");
	scanf("%d",&e);
	make_graph(vertices, n, e);
	//print_graph(vertices, n, e);
	dfs(vertices,visited,n,e);
	for(i=0;i<n;i++)
	{
		printf("\n%d	%d	%d",visited[i]->v, visited[i]->p, visited[i]->r);
	}
	for(i=0;i<n;i++)
	{
		if(visited[i]->r==n)
		{
			push(visited[i]);
		}
	}
	if(stack==NULL)
	{
		printf("-1");
		return 0;
	}
	struct vertex *ptr=stack;
	while(ptr!=NULL)
	{
		printf("\n%d	",ptr->v);
		ptr=ptr->next;
	}
	struct h * heap[n];
    	for (i=0; i<n; i++)
    	{
		 heap[i]->v=i;
		 heap[i]->l=10000;
	}
	dijkstra(heap, vertices,visited,e,n);
	for(i=0;i<n;i++)
	{
		if(visited[i]->longest!=0)
			break;
			
	}
	int m=i;
	for(i=i+1;i<n;i++)
	{
		if(visited[i]->longest<visited[m]->longest)
			m=i;
			
	}
	printf("\n%d	%d",visited[m]->v,visited[m]->longest);
	return 0;
}
