#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	int weight;
	int color;
	struct node *next;
};

int n=4;

void clr(struct node *arr,int a,int cl){
	arr[a].color=cl;
	struct node *temp1=arr[a].next;
	while(temp1!=NULL){
		struct node *temp2=arr[temp1->value].next;
		while(temp2->value!=a)
			temp2=temp2->next;
		temp2->color=cl;
		temp1=temp1->next;
	}
}

void pushup(int *heap,int i,int *map,int name){
	int p=(i-1)/2,temp,x=0;
	if(i==0) return;
	if(heap[p]<=heap[i]) return;
	else{
		temp=heap[p];
		heap[p]=heap[i];
		heap[i]=temp;
		while(map[x]!=p)
			x++;
		map[x]=i;
		map[name]=p;
		pushup(heap,p,map,name);
	}
}

void pushdown(int *heap,int i,int c,int *map) {
    int l,r,min,temp,x,y;
    l=(2*i)+1;
    r=(2*i)+2;
    if(l<=c && heap[l]<heap[i])
		min=l;
	else
		min=i;
	if(r<=c && heap[r]<heap[min])
		min=r;
	if(min!=i){
		temp=heap[i];
		heap[i]=heap[min];
		heap[min]=temp;
		x=0;
        while(map[x]!=i)
         	x++;
        y=0;
        while(map[y]!=min)
          	y++;
        map[y]=i;
        map[x]=min;
        pushdown(heap,min,c,map);
	}
}

int insert(int *heap,int key,int c,int *n,int *map,int name){
	c++;
	if(c==*n){
		heap=realloc(heap,2*(*n));
		*n=(*n)*2;
	}
	heap[c]=key;
	map[name]=c;
	pushup(heap,c,map,name);
	return c;
}

int delete_min(int *heap,int c,int *map,int name){
	int temp,x=0,i=0;
	temp=heap[i];
	heap[i]=heap[c];
	heap[c]=temp;
	while(map[x]!=c)
		x++;
	map[x]=i;
	c--;
	map[name]=-1;
	pushdown(heap,i,c,map);
	return c;
}

void add_edge(struct node *arr,int i,int j,int w,int n){
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->value = i;
	new1->color=0;
	new1->weight = w;
	new1->next=NULL;
	if(arr[j].next==NULL)
		arr[j].next=new1;
	else{
		struct node *temp=arr[j].next;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=new1;
	}
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2->value = j;
	new2->color;
	new2->weight = w;
	new2->next=NULL;
	if(arr[i].next==NULL)
		arr[i].next=new2;
	else{
		struct node *temp2=arr[i].next;
		while(temp2->next!=NULL)
			temp2=temp2->next;
		temp2->next=new2;
	}
}

int dijkstra(struct node *arr,int *heap,int *map,int c,int dest,int n){
	int name,checker=0,i,m;
	int pd[n][2];
	for(i=0;i<n;i++){
		pd[i][0]=-1;
		pd[i][1]=1000;
	}
	while(c>=0){
		name=0;
		while(map[name]!=0)
			name++;
		if(checker!=0)
			pd[name][1]=heap[map[name]];
		else
			pd[name][1]=0;
		c=delete_min(heap,c,map,name);
		checker++;
		struct node *temp=arr[name].next;
		while(temp!=NULL){
			if(map[temp->value]>=0 && (pd[name][1]+temp->weight)<heap[map[temp->value]]){
				heap[map[temp->value]]=pd[name][1]+temp->weight;
				pushup(heap,map[temp->value],map,temp->value);
				pd[temp->value][0]=name;
			}
			temp=temp->next;
		}
	}
	return pd[dest][1];
}

int distance(struct node *arr,int *heap,int *map,int c,int src,int dest,int n){
	c=-1;
	int i=0;
	for(i=0;i<n;i++){
		if(i==src)
			c=insert(heap,0,c,&n,map,i);
		else
			c=insert(heap,1000,c,&n,map,i);
	}
	return dijkstra(arr,heap,map,c,dest,n);
}

int distance2(struct node *arr,int *heap,int *map,int c,int src,int dest,int n){
	c=-1;
	int i=0;
	for(i=0;i<n;i++){
		if(arr[i].color==0){
			if(i==src)
				c=insert(heap,0,c,&n,map,i);
			else
				c=insert(heap,1000,c,&n,map,i);
		}
		else
			map[i]=-1;
	}
	return dijkstra(arr,heap,map,c,dest,n);
}

void func(struct node *arr,int *heap,int *map,int c,int n){
	int i,d1,d2;
	for(i=0;i<n;i++){
		d1=distance(arr,heap,map,c,0,i,n);
		d2=distance(arr,heap,map,c,i,n-1,n);
		if((d1+d2)==distance(arr,heap,map,c,0,n-1,n))
			clr(arr,i,1);
	}	
}

void main(){
	int c=-1,i,m,n,S,T,ST,EN,w,t,k,u,ans;
	
	scanf("%d",&t);
	for(k=0;k<t;k++){
		c=-1;
		int *heap,*map;
		scanf("%d %d",&n,&m);
		scanf("%d %d",&S,&T);
		heap=malloc(sizeof(int)*n);
		map=malloc(sizeof(int)*n);
		struct node arr[n];
		for(i=0;i<n;i++){
			arr[i].value=i;
			arr[i].weight=0;
			arr[i].color=0;
			arr[i].next=NULL;
		}
		for(u=0;u<m;u++){
			scanf("%d %d %d",&ST,&EN,&w);
			add_edge(arr,ST-1,EN-1,w,n);
		}
		func(arr,heap,map,c,n);
		ans=distance2(arr,heap,map,c,0,3,n);
		if(ans==1000)
			printf("NOT POSSIBLE\n");
		else
			printf("%d\n",ans);
	}
}