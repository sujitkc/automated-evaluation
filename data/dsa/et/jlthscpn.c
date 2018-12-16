#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	struct node *next;
	int wt;
};

struct arr{
	struct node *head;
};

struct qnode{
	int val;
	struct qnode *next;
	int wt;
};

struct qnode *front= NULL;
struct qnode *rear = NULL;

void add_node(int a){
	struct qnode *curr= (struct qnode *)malloc(sizeof(struct qnode));
	curr->val=a;
	curr->next=NULL;
	
	if(front==NULL && rear==NULL){
		front=curr;
		rear=curr;
	}
	else{
		rear->next=curr;
		rear=curr;
	}
}

int is_empty(){
	if(front ==NULL && rear==NULL)
		return 1;
	else return 0;
}

int rem_node(){
	
	if(front==NULL && rear==NULL)
		printf("empty queue");
	else if(front==rear){
		struct qnode *temp;
		temp=front;
		front=NULL;
		rear=NULL;
		return temp->val;
	}
	else{
		struct qnode *curr=NULL;
		curr=front;
		front=front->next;
		return curr->val;
	}
}



struct node* make_node(int v,int w){
	struct node *curr = (struct node *)malloc(sizeof(struct node));
	curr->val=v;
	curr->next=NULL;
	curr->wt=w;
	return curr;
}

void build_adj_list(int i,int j,struct arr *a,int *w){
	struct node *ni=make_node(i,w[i-1]);
	struct node *nj=make_node(j,w[j-1]);
	
	if(a[i].head==NULL){
		a[i].head=nj;
		a[i].head -> next = NULL;
	}
	else{
		struct node *temp;
		temp=a[i].head;
		a[i].head=nj;
		nj->next=temp;
	}
	
	if(a[j].head==NULL){
		a[j].head=ni;
		a[j].head -> next = NULL;
	}
	else{
		struct node *temp;
		temp=a[j].head;
		a[j].head=ni;
		ni->next=temp;
	}
	
}

void find_max(int * bfs_tree, int * w,int v){
	int m[v],i;
	for(i=v-1;i>0;i--){
		if(v-1<2*i+1)
			m[i]=w[i];
		else{
			int t=i,s=w[i];
			while(t<2*i+1){
				t=2*i+1;
				s=s+w[t];
			}
			while(t<2*i+2){
				t=2*i+2;
				s=s+w[t];
			}
			m[i]=s;
		}
	}

	int max=m[1],a=0,b=1;
	for(i=2;i<v;i++){
		if(m[i]>max){
			max=m[i];
			b=i;
			a=(i-1)/2;
		}
	}
	
	printf("the edge to be removed  is : %d,%d ",a,b);
	
}


void bfs(int v,struct arr *a,int * w){
	int i,label[v+1];
	char color[v+1];
	for(i=0;i<=v;i++)
		color[i]='w'; 
	for(i=0;i<=v;i++)	
		label[i]=-1;
	int bfs_tree[v];
	
	add_node(1);   //assume source is 1
	color[1]='g';
	label[1]=0;

	while(is_empty()==0){
		int x=rem_node();
		printf("%d\n",x);
		color[x]='b';
		bfs_tree[x-1]=x;
		struct node *temp;
		temp=a[x].head;
		while(temp!=NULL){
			if(color[temp->val]=='w'){
				add_node(temp->val);
				color[temp->val]='g';
				label[temp->val]=label[x]+1;
			}
			temp=temp->next;
		}
	}
	
	for(i=1;i<=v;i++)
		printf("%d ",label[i]);
	printf("\n");
	for(i=1;i<=v;i++)
		printf("%c ",color[i]);
	printf("\n");
	for(i=0;i<v;i++)
		printf("%d ",bfs_tree[i]);
	find_max(bfs_tree,w,v);
}


void printadj(struct arr * a,int v){
	int i;
	for( i=1 ; i<=v; i++){
		struct node * temp;
		temp = a[i].head;
		printf("src %d - ", i);
		while( temp != NULL){
			printf("%d,%d ",temp -> val,temp ->wt);
			temp = temp -> next;
		}
		printf("\n");
	
	}
}


void main(){
	int v,e;
	printf("enter number of vertices: ");
	scanf("%d",&v);
	printf("enter number of edges: ");
	scanf("%d",&e);
	struct arr a[v+1];
	int w[v];
	w[0]=0;
	int i,e1,e2;
	for(i=0;i<v+1;i++){
		a[i].head = NULL;
	}
	printf("enter the weight of each node : ");
	for(i=0;i<v;i++)
		scanf("%d",&w[i]);
	
	for(i=0;i<e;i++){
		printf("enter edge : ");
		scanf("%d %d", &e1,&e2);
		build_adj_list(e1,e2,a,w);
	}
	
	printadj(a,v);
	
	bfs(v,a,w);
}
