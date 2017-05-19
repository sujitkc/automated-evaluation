#include<stdio.h>
#include<stdlib.h>

struct node
{
	int colour,priority,id;
	struct node * pi;
};

struct edge
{
	int weight,endnode;
};

struct listnode
{
	struct edge * edge;
	struct listnode * next;
};

void AddEdge(int start,int w, int end,struct listnode * arr[])
{
	struct edge * newnode = (struct edge *)malloc(sizeof(struct edge));
	newnode->weight = w;
	newnode->endnode = end;
	if(arr[start] == NULL)
	{
		arr[start] = (struct listnode*)malloc(sizeof(struct listnode));
		arr[start]->edge = newnode;
		arr[start]->next = NULL;
		return;
	}
	struct listnode * curr = arr[start];
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = (struct listnode*)malloc(sizeof(struct listnode));
	curr->next->edge = newnode;
	curr->next->next = NULL;
}

void Graph(struct listnode * arr[],int num)
{
	for(int i = 0; i<num; i++)
	{
		struct listnode * curr = arr[i];
		printf("%d->",i);
		while(curr != NULL)
		{
			printf("endnode = %d, weight = %d    ",curr->edge->endnode,curr->edge->weight);
			curr=curr->next;
		}
		printf("\n");
	}
}

void TopDownHeapifyMin(struct node * heap[], int i,int n)
{
	while(2*i + 2<n)
	{
		int min = heap[2*i + 1]->priority > heap[2*i + 2]->priority?2*i+2:2*i+1;
		if(heap[min] < heap[i])
		{
			struct node * temp = heap[min];
			heap[min] = heap[i];
			heap[i] = temp;
			i = min;
		}
		else
		{
			break;
		}
	}
	if(2*i + 1<n && heap[i]->priority> heap[2*i + 1]->priority)
	{
		struct node * temp = heap[2*i + 1];
		heap[2*i + 1] = heap[i];
		heap[i] = temp;
	}
}

void BottomUpHeapifyMin(struct node * heap[], int i)
{
	while(i>0)
	{
		if(heap[i]->priority < heap[(i-1)/2]->priority)
		{
			struct node * temp = heap[i];
			heap[i] = heap[(i-1)/2];
			heap[(i-1)/2] = temp;
			i = (i-1)/2;
		}
		else
		{
			break;
		}
	}
}

void InsertMin(struct node * heap[],struct node * n,int *soheap)
{
	heap[*soheap] = n;
	BottomUpHeapifyMin(heap,*soheap);
	*soheap+=1;
}

void DeleteMin(struct node * heap[], int *soheap)
{
	if(*soheap == 0)
	{
		return;
	}
	else if(*soheap == 1)
	{
		*soheap-=1;
		return;
	}
	heap[0] = heap[(*soheap)-1];
	*soheap-=1;
	TopDownHeapifyMin(heap,0,*soheap);
}

void Dijkstra(struct listnode * arr[], int num, int index,int * max,int * node)
{
	struct node * nodes[num];
	struct node * heap[10000];
	int tempmax = -1;
	int tempnode = index;
	int size = 0;
	for(int i = 1; i<num; i++)
	{
		nodes[i] = (struct node*)malloc(sizeof(struct node));
		nodes[i]->colour = -1;
		nodes[i]->id = i;
	}
	InsertMin(heap,nodes[index],&size);
	nodes[index]->colour = 0;
	nodes[index]->priority = 0;
	nodes[index]->pi = nodes[index];
	while(size != 0)
	{
		struct node *temp = heap[0];
		if(heap[0]->colour == 1)
		{
			DeleteMin(heap,&size);
			continue;
		}
		DeleteMin(heap,&size);
		temp->colour = 1;
		//printf("endnode = %d weight = %d\n\n",temp->id,temp->priority);
		if(temp->priority > tempmax)
		{
			tempmax = temp->priority;
		}
		//printf("\n\ntempmax = %d tempnode = %d\n\n",tempmax,tempnode);
		struct listnode * curr = arr[temp->id];
		while(curr != NULL)
		{
			//printf("node to be added %d colour %d\n\n",nodes[curr->edge->endnode]->id,nodes[curr->edge->endnode]->colour);
			if(nodes[curr->edge->endnode]->colour == -1)
			{
				nodes[curr->edge->endnode]->pi = temp;
				nodes[curr->edge->endnode]->colour = 0;
				nodes[curr->edge->endnode]->priority = temp->priority + curr->edge->weight;
				InsertMin(heap,nodes[curr->edge->endnode],&size);
			}
			else if(nodes[curr->edge->endnode]->colour == 0)
			{
				if(nodes[curr->edge->endnode]->priority > temp->priority + curr->edge->weight)
				{
					nodes[curr->edge->endnode]->priority = temp->priority + curr->edge->weight;
					InsertMin(heap,nodes[curr->edge->endnode],&size);		
				}
			}
			curr = curr->next;
		}
	}
	for(int i = 1; i<num; i++)
	{
		if(nodes[i]->colour == -1)
		{
			return;
		}
	}
	if(tempmax < *max || *max == -1)
	{
		//printf("changing\n\n\n");
		*max = tempmax;
		*node = tempnode;
	} 
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int x = 0; x<t; x++)
	{
		int num,m;
		scanf("%d %d",&num,&m);
		num++;
		struct listnode * arr[num];
		for(int i = 0; i<num; i++)
		{
			arr[i] = NULL;
		}
		int max = -1,node = -1;
		int s,e,d;
		for(int i = 0; i<m; i++)
		{
			scanf("%d %d %d",&s,&e,&d);
			AddEdge(e,d,s,arr);
		}
		//Graph(arr,num);
		for(int i = 1; i<num; i++)
		{
			Dijkstra(arr,num,i,&max,&node);
			//printf("\n\n\n");
		}
		printf("%d %d\n\n\n",node,max);
	}
}