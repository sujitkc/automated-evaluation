#include<stdio.h>
#include<stdlib.h>
struct graph{
	int V;
	int E;
	int *adj;
};

struct listnode{
	int vertexnum;
	struct listnode *next;
};

struct graph *adjlist(){
	int x,y,i;
	struct listnode *temp;
	struct graph *G=(struct graph *)malloc(sizeof(struct graph));
	if(!G){
		printf("Error");
		
	}
	scanf("%d %d",&G->V,&G->E);
	G->adj=malloc(G->V*sizeof(struct graph));
	for(i=0;i<G->V;i++){
		G->adj[i]=(struct listode *)malloc(sizeof(struct listnode));
		G->adj[i]->vertexnum=i;
		G->adj[i]->next=G->adj[i];
	}
	for(i=0;i<E;i++){
		scanf("%d %d",&x,&y);
		temp=(struct listnode *)malloc(struct listnode);
		temp->vertexnum=y;
		temp->next=G->adj[x];
		G->adj[x]->next=temp;
		temp = (struct listnode *)malloc(struct listnode);
		temp->vertexnum=y;
		temp->next=G->adj[y];
		G->adj[y]->next=temp;
		
	}
	int counter=0;
	
	return G;
}































































	

