#include <stdio.h>
#include<stdlib.h>
struct ed{
	int a,b;
}*arr;
int sum;
struct listnode{
	int verno;
	int status;
	int value;
	struct listnode *nxt;
};
struct graph{
	int V;
	int E;
	struct listnode *adj;
};
int max(int i1,int i2){
	if(i1<i2){
		return i2;
	}
	else
		return i1;
}
int min(int i1,int i2){
	if(i1<i2){
		return i1;
	}
	else
		return i2;
}
struct graph *adjgraph(){
	int i,v,u,m,n;
	struct listnode *temp,*t;
	struct graph *G;
	G=(struct graph*)malloc(sizeof(struct graph));
	scanf("%d",&G->V);
	G->E=G->V-1;
	G->adj=malloc(sizeof(struct listnode)*(G->V+1));
	sum=0;
	for(i=1;i<=G->V;i++){
		G->adj[i].verno=i;
		G->adj[i].nxt=NULL;
		G->adj[i].status=1;
		scanf("%d",&G->adj[i].value);
		sum=sum+G->adj[i].value;
	}
	arr=malloc(sizeof(struct ed)*G->E);
	for(i=0;i<G->E;i++){
		scanf("%d %d",&m,&n);
		v=min(m,n);
		u=max(m,n);
		arr[i].a=v;
		arr[i].b=u;
		temp=(struct listnode *)malloc(sizeof(struct listnode));
		temp->verno=u;
		temp->value=G->adj[u].value;
		temp->nxt=NULL;
		t=&G->adj[v];
		while(t->nxt!=NULL){	
			t=t->nxt;
		}
		t->nxt=temp;
	}
	return G;
}
int DFS(struct graph *g,int z){
	struct listnode *temp; 
	int stk[g->V],tr=0,t,i,suma=0;
	t=g->adj[z].verno;
	stk[tr]=t;
	tr++;
	g->adj[t].status=1;
	while(tr!=0){
		tr--;
		t=stk[tr];
		suma=suma+g->adj[t].value;
		//printf("%d  ",t);
		g->adj[t].status=3;
		printf("\n");
		temp=&g->adj[t];
		while(temp != NULL){
			if(g->adj[temp->verno].status==1){
				stk[tr]=temp->verno;
				g->adj[stk[tr]].status=2;
				tr++;	
			}
			temp=temp->nxt;
		}
	}
	return suma;
}
void main(){
	int t,i,j,mini,l,x=-100000;
	scanf("%d",&t);
	for(i=0;i<t;i++){
		struct graph *G;
		G=adjgraph();
		for(j=0;j<G->E;j++){
			l=DFS(G,arr[j].a);
			mini = min(l,sum-l);
			x=max(x,mini);
		}
		printf("\n\nAns=%d",x);
	}
}
