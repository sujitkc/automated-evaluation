#include <stdio.h>
#include <stdlib.h>

struct list_node
{
	int data;
	struct list_node* next;
};

void addedge(int u,int v, struct list_node* arr[])
{
	struct list_node* temp=(struct list_node*)malloc(sizeof(struct list_node));
	temp->data=v;
	temp->next=arr[u];
	arr[u]=temp;
}

void dfs(struct list_node* graph[], int s,int visited[])
{
	visited[s]=1;
	//printf("%d\n",s );

	struct list_node* neighbours;
	neighbours=graph[s];
	while(neighbours!=NULL)
	{
		if (visited[neighbours->data]==0)
		{
			dfs(graph,neighbours->data,visited);
		}
		neighbours=neighbours->next;
	}
}

void MODdfs(struct list_node* graph[], int x,int visited[])
{
	visited[x] = 1;

	struct list_node* neighbours;
	neighbours = graph[x];
	int sum = weight[x];
	while(neighbours != NULL)
	{
		if(visited[neighbours->data] == 0){
			sum = sum + MODdfs(graph, neighbours, visited)
		}
		neighbours = neighbours->next;
		wt(u) = sum;
		return sum;
	}
}

int main()
{
	int a;
	int arr1[a-1];
	scanf("%d", &a);
	int visited[a];

	for (int i = 0; i <a; ++i){
		visited[i]=0;
	}

	struct list_node* graph[a];
	for(int j = 0; j<(a-1); ++j){
		scanf("%d %d", &arr1[j], &arr[j+1])
		addedge(j,j+1,graph);
	}
	struct list_node *currentptr;
	for(int i=0;i<a;++i)
	{
		currentptr=graph[i];
		while(currentptr!=NULL)
		{
			printf("%d\t",currentptr->data );
			currentptr=currentptr->next;
		}
		printf("\n");
	}

	MODdfs(graph,,visited);
}
