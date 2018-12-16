#include<stdio.h>
#include<stdlib.h>

struct list_node 		
{
	int data;
	struct list_node* next;
};

struct node       		
	int value;
	char colour;		//red = not visited, blue = visited, yellow = in the data structure
	struct list_node* list;
	struct list_node* current;
	struct list_node* start;
	int parent;
	int d;
	int f;
};

void print_graph(int n, struct node* graph[])
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d : ",graph[i]->value);
		print_list(graph[i]->start);
	}
}

void insert(int u, int v, int n, struct node* graph[])  //edge from u to v
{
	int flag=0;
	for (int i = 0; i < n; ++i)
	{
		if (graph[i]->value==u)
		{
			graph[i]->list = (struct list_node*)malloc(sizeof(struct list_node));
			graph[i]->list->data=v;
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

stuct graph *adj(){
	int i,v,u;
	stuct graph *G=(struct graph *)malloc(sizeof(struct graph));
	if(!G){
		printf("error");
		return;
	}
	scanf("vertices is %d,edges is%d",&G->V,&G->E);
	G->adj=malloc(sizeof(G->V *G->V));
	for (u=0;u<G->V;u++){
		for (v=0;v<G->V;v++)
			G->adj[v][v]=0;}
	for (i=0;i<G->E;i++){
		scanf("readinf edge:%d,%d",&u,&v);
		G->adj[u][v]=1;
		G->adj[u][v]=1;
}
return G;
}
	
	
	int hascycle(struct graph *G,int u){
	visited[u]=1;
	for(int i=0;i<G->V;i++){
		if(G->adj[s][i]){
			if(predecessor[i]!=u && visited[i])
				return 1;
			else{
				predecessor[i]=u;
				return hascycle(G,i);}
		}
	}
	return 0;
}
	
	


		

int check(struct graph *G){
	for(int i=0;i<G->V;i++){
		visited[s]=0;
		predecessor[i]=0;
	}
	for(int i=0;i<G->V;i++){
		if(!visited[i] && hascycle(G,i))
			return 1;
	}
	return false;
}



int main()
{	int **adj;
	int n=6;					//no.of vertices
	struct node* graph[n];
	for (int i = 0; i < n; ++i)
	{
		graph[i]=(struct node*)malloc(sizeof(struct node));
		graph[i]->start=graph[i]->current=NULL;
		graph[i]->colour='r';
	}
	graph[0]->value=41;
	graph[1]->value=30;
	graph[2]->value=10;
	graph[3]->value=2;
	graph[4]->value=5;
	graph[5]->value=61;
	insert(41,30,n,graph);
	insert(2,30,n,graph);
	insert(30,10,n,graph);
	insert(10,41,n,graph);
	insert(5,10,n,graph);
	insert(5,61,n,graph);
	insert(61,2,n,graph);
	insert(30,5,n,graph);
	/*for (int i = 0; i < n; ++i)  //Check if all nodes are coloured red
	{
		printf("%d : %c\n",graph[i]->value, graph[i]->colour);
	}*/
	check(graph);
	/*for (int i = 0; i < n; ++i)  //Check if all nodes are coloured blue
	{
		printf("%d : %c\n",graph[i]->value, graph[i]->colour);
	}*/
	return 0;
};
