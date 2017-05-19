#include<stdio.h>
#include<stdlib.h>
struct node{
	int vertex,cost;
	struct node *next;
};
struct vrtx{
	int color,pri,pi,v;
};
void insert(struct node **root,int val,int c){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->vertex=val;
	new->cost=c;
	new->next=*(root);
	*root=new;
}
void Graph(struct node * graph[],int n,int m){
	int i;
	//printf("Enter the edges:\n");
	for(i=0;i<m;i++){
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		insert(&(graph[u-1]),v,d);
		insert(&(graph[v-1]),u,d);
	}
}
void TopDownMin(struct vrtx arr[],int i,int n){
	int lc=2*i+1,rc=2*i+2,j;
	struct vrtx t;
	while(rc<n){
		if(arr[lc].pri<arr[rc].pri)
			j=lc;
		else
			j=rc;
		if(arr[i].pri<arr[j].pri)
			break;
		else{
			t=arr[i];
			arr[i]=arr[j];
			arr[j]=t;
		}
		i=j;
		lc=2*i+1;
		rc=2*i+2;
	}
	if(lc==n-1&&arr[i].pri>arr[lc].pri){
		t=arr[i];
		arr[i]=arr[lc];
		arr[lc]=t;
	}
}
void BottomUpMin(struct vrtx arr[],int i){
	int p;
	struct vrtx t;
	while(i>0){
		p=(i-1)/2;
		if(arr[p].pri>arr[i].pri){
			t=arr[i];
			arr[i]=arr[p];
			arr[p]=t;
		}
		else
			break;
		i=p;		
	}
}
void deletemin(struct vrtx arr[],int n){
  arr[0]=arr[n-1];
  TopDownMin(arr,0,n);
}
void insertmin(struct vrtx arr[],int n,struct vrtx key){
  if(n==0){
    arr[0]=key;
    return;  
  }
  else{
    arr[n]=key;
    BottomUpMin(arr,n);
  }
}
void decreasekey(struct vrtx arr[],int n,struct vrtx change,int new){
	int i;
	for(i=0;i<n;i++){
		if(arr[i].v==change.v){
			arr[i].pri=new;
			BottomUpMin(arr,n);
			break;
		}
	}
}
void dijkstra(struct node *graph[],struct vrtx vertices[],int Bool[],int s){
	struct vrtx min[100000];
	int cntmin=0;
	vertices[s-1].pri=0;
	vertices[s-1].color=1;
	vertices[s-1].pi=s;
	insertmin(min,cntmin,vertices[s-1]);
	cntmin++;
	while(cntmin!=0){
		int del=min[0].v;
		deletemin(min,cntmin);
		cntmin--;
		vertices[del-1].color=2;
		struct node *curr;
		curr=graph[del-1];
		while(curr!=NULL){
			if(Bool[(curr->vertex)-1]!=1){
			if(vertices[(curr->vertex)-1].color==0){
				vertices[(curr->vertex)-1].color=1;
				vertices[(curr->vertex)-1].pri=vertices[del-1].pri+curr->cost;
				vertices[(curr->vertex)-1].pi=del;
				insertmin(min,cntmin,vertices[(curr->vertex)-1]);
				cntmin++;
			}
			else if(vertices[(curr->vertex)-1].color==1){
				if(vertices[(curr->vertex)-1].pri>vertices[del-1].pri+curr->cost){
					decreasekey(min,cntmin,vertices[(curr->vertex)-1],vertices[del-1].pri+curr->cost);
					vertices[(curr->vertex)-1].pri=vertices[del-1].pri+curr->cost;
					vertices[(curr->vertex)-1].pi=del;
				}
			}
			}
			curr=curr->next;
		}
	}
}
int main(){
	int t,x;
	scanf("%d",&t);
	for(x=0;x<t;x++){
		int n,m,s,t,i;
		scanf("%d%d",&n,&m);
		scanf("%d%d",&s,&t);
		struct node *graph[n];
		int Bool[n];
		for(i=0;i<n;i++){
			Bool[i]=0;
		}
		for(i=0;i<n;i++){
			graph[i]=malloc(sizeof(struct node));
			graph[i]=NULL;	
		}
		Graph(graph,n,m);
		struct vrtx vertices[n];
		for(i=0;i<n;i++){
			vertices[i].color=0;
			vertices[i].pri=12345;
			vertices[i].pi=-1;
			vertices[i].v=i+1;
		}
		dijkstra(graph,vertices,Bool,1);
		int arra[n];
		for(i=0;i<n;i++){
			arra[i]=vertices[i].pri;
		}
		for(i=0;i<n;i++){
			vertices[i].color=0;
			vertices[i].pri=12345;
			vertices[i].pi=-1;
			vertices[i].v=i+1;
		}
		dijkstra(graph,vertices,Bool,n);
		int arrb[n];
		for(i=0;i<n;i++){
			arrb[i]=vertices[i].pri;
		}
		for(i=0;i<n;i++){
			if(arra[i]+arrb[i]==arra[n-1]){
				Bool[i]=1;
			}
			else
				Bool[i]=0;
		}
		for(i=0;i<n;i++){
			vertices[i].color=0;
			vertices[i].pri=12345;
			vertices[i].pi=-1;
			vertices[i].v=i+1;
		}
		dijkstra(graph,vertices,Bool,s);
		if(vertices[t-1].pri!=12345){
			printf("%d\n",vertices[t-1].pri);
		}
		else{
			printf("NOT POSSIBLE\n");
		}
	}
}
