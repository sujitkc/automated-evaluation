#include <stdio.h>
#include <stdlib.h>

struct list_node 		//linked list
{
	int data;
	int weight;
	struct list_node* next;
};

struct node       		//element of array
{
	int value;
	char c;
	struct list_node* list;
	struct list_node* current;
	struct list_node* start;
	int priority;
  int bo;
	struct node* parent;
};

void print_list(struct list_node* start)
{
	struct list_node* temp=malloc(sizeof(struct list_node));
	temp=start;
	while(start!=NULL)
	{
		printf("%d ",start->data);
		start=start->next;
	}
	start=temp;
	printf("\n");
}

void print_graph(int n, struct node* graph[])
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d : ",graph[i]->value);
		print_list(graph[i]->start);
	}
}

void bottom_up_heapify(struct node *a[],int i)
{
	int p=(i-1)/2;
	struct node *t = (struct node *)malloc(sizeof(struct node));
	while(i>0)
	{
		if(a[p]->priority > a[i]->priority)
		{
			t=a[p];
			a[p]=a[i];
			a[i]=t;
		}
		else
			break;
		i=p;
		p=(i-1)/2;
	}
}

void top_down_heapify(struct node *a[], int n, int i)
{
	int l=2*i + 1;
	int r=2*i + 2,j;
	struct node *t = (struct node *)malloc(sizeof(struct node));
	if(l==n-1 && a[i]->priority > a[l]->priority)
	{
		t=a[l];
		a[l]=a[i];
		a[i]=t;
		return;
	}
	while(r<n)
	{
		if(a[l]->priority < a[r]->priority)
			j=l;
		else
			j=r;
		if(a[i]->priority < a[j]->priority)
			break;
		else
		{
			t=a[j];
			a[j]=a[i];
			a[i]=t;
		}
		i=j;
		l=2*i+1;
		r=2*i+1;
		if(l==n-1 && a[i]->priority > a[l]->priority)
		{
			t=a[l];
			a[l]=a[i];
			a[i]=t;
			break;
		}
	}
}

void build_heap(struct node *a[],int n)
{
	int i = n/2;
	while(i >= 0)
	{
		top_down_heapify(a,n,i);
		i--;
	}
}

void heap_insert(struct node* a[], int* n, struct node *num)
{
	num->c='y';
	a[*n] = num;
	bottom_up_heapify(a,*n);
	(*n)++;
}

struct node * delete_min(struct node *a[],int *n)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp=a[*n-1];
	a[*n-1]=a[0];
	a[0]=temp;
	temp=a[*n-1];
	temp->c='b';
	(*n)--;
	top_down_heapify(a,*n,0);
	return temp;
}

void add_edge(int u, int v, int wt, int n, struct node* graph[])  //edge from u to v
{
	int flag=0;
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value==u)
		{
			graph[i]->list = (struct list_node*)malloc(sizeof(struct list_node));
			graph[i]->list->data=v;
			graph[i]->list->weight=wt;
			if (graph[i]->current==NULL)
			{
				graph[i]->current=graph[i]->list;
				graph[i]->current->next=NULL;
				graph[i]->start=graph[i]->current;
			}
			else
			{
				graph[i]->list->next=graph[i]->current;
				graph[i]->current=graph[i]->list;
				graph[i]->start=graph[i]->list;
			}
			flag=1;
		}
	}
	if (flag==0)
	{
		printf("Node doesn't exist.\n");
	}
}

char get_colour(struct node *g[], int n, struct list_node *x)
{
	int t = x->data;
  char p;
	for (int i = 0; i < n; ++i)
	{
		if (g[i]->value==t)
		{
			p = g[i]->c;
		}

	}
  return p;
}

struct node * get_node(struct node *g[], int n, struct list_node *x)
{
	int t = x->data;
  struct node* temp;
	for (int i = 0; i < n; ++i)
	{
		if (g[i]->value==t)
		{
			temp = g[i];
		}

	}
  return temp;
}

void dijkstra(struct node *graph[], int n, int b)
{
	int m=0;
	struct node *a[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (struct node*)malloc(sizeof(struct node));
	}
	struct node *u = (struct node *)malloc(sizeof(struct node));
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value == b)
		{
			u=graph[i];
			heap_insert(a,&m,u);
			u->priority=0;
			u->parent=u;
		}
	}
	while(m!=0)
	{
		u=delete_min(a,&m);
		while(u->start!=NULL)
		{
			if(get_colour(graph,n,u->start)=='r')
			{
				temp=get_node(graph,n,u->start);
				temp->priority = u->priority + u->start->weight;
				temp->parent=u;

				heap_insert(a,&m,temp);
			}
			else if (get_colour(graph,n,u->start)=='y')
			{
				temp=get_node(graph,n,u->start);
				if (temp->priority > u->priority + u->start->weight)
				{
					temp->priority = u->priority + u->start->weight;
					temp->parent=u;

				}
			}
			u->start=u->start->next;
		}
	}
}

int shortest_path(struct node * graph[], int n, int a, int b)
{
	dijkstra(graph,n,a);
	struct node * v = (struct node*)malloc(sizeof(struct node));
	struct node * temp = (struct node*)malloc(sizeof(struct node));
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value==b)
		{
			v=graph[i];
			break;
		}
	}
	temp=v;

  return temp->priority;
}
int shortest_path1(struct node * graph[], int n, int a, int b)
{
	dijkstra(graph,n,a);
	struct node * v = (struct node*)malloc(sizeof(struct node));
	struct node * temp = (struct node*)malloc(sizeof(struct node));
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value==b && graph[i]->bo == 0)
		{
			v=graph[i];
			break;
		}
	}
	temp=v;
  return temp->priority;
}

int main()
{
	int test,n,m,s,t,i,j;
  printf("Enter the number of test cases:");
  scanf("%d",&test);
  for(j=0;j<test;j++){
    printf("%d",j);
    printf("Enter the number of nodes and edges:");
    scanf("%d %d",&n,&m);
	   struct node* graph[n];
	    for (int i = 0; i < n; i++)
	     {
		       graph[i]=(struct node*)malloc(sizeof(struct node));
		       graph[i]->start=graph[i]->current=NULL;
		       graph[i]->c='r';
           graph[i]->value=i+1;
	      }
      for(int i=0;i<m;i++){
        int x,y,d;
        printf(" Enter the src,dest,dist :" );
        scanf("%d %d %d",&x,&y,&d);
        add_edge(x,y,d,n,graph);
        add_edge(y,x,d,n,graph);
      }
    int shortar_t;
    shortar_t = shortest_path(graph,n,1,n);

    printf("k: %d\n:",shortar_t);
    printf(" Enter Src and Dest:");
    scanf("%d %d",&s,&t);
    for(i=0;i<n;i++){
      if(shortar_t==shortest_path(graph,n,1,i+1)+shortest_path(graph,n,i+1,n))
        graph[i]->bo =1;
    }
    int l = shortest_path1(graph,n,s,t);
    if (l == 0)
      printf("NO PATH EXISTS");
    else printf("%d\n",l);
  }
	return 0;
}
