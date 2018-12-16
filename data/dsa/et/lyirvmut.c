#include<stdio.h>
#include<stdlib.h>
struct node
{
	int heap;
	int data;
	struct node_ll *next;
	int colour;//0->red,1->yellow,2->blue red siginifies that the node is not yet added in the data structure and yellow siginifies we have added that node in data structure and blue siginifes we have deleted the node from data structure
	struct node *p;
	int pri;
};
struct node_ll
{
	int data;
	struct node_ll *next;
	struct node *parent;
	int weight;
};
void bottom_up_heapyfy(struct node* arr[] , int i);
void top_down_heapyfy(struct node* arr[] , int i);
void swap(struct node** a,struct node** b);
void enqueue(struct node* arr[],struct node* n);
struct node* dequeue(struct node* arr[]);
void add_edge(struct node *arr[],struct node *s,struct node *e,int w,int n);
void dijkstra(struct node *arr[],struct node *s,int n);
void print_path(struct node *v);
int curr=0;
void find_min();
struct node *reqheap[100];
void main()
{	int t,k,i,j,dis,p,q;
	scanf("%d",&t);
	int n,m;
	scanf("%d%d",&n,&m);
	for(k=0;k<m;k++){
		for(p=0;p<3;p++){
			scanf("%d%d%d",&i,&j,&dis);	
		}
	}
//let n=5,m=7;
	int a1,a2,a3,a4;
	struct node *a,*b,*c,*d,*e;
	struct node_ll *cur;
	a = (struct node*)malloc(sizeof(struct node));
	b = (struct node*)malloc(sizeof(struct node));
	c = (struct node*)malloc(sizeof(struct node));
	d = (struct node*)malloc(sizeof(struct node));
	e = (struct node*)malloc(sizeof(struct node));
	a->data=1;
	b->data=2;
	c->data=3;
	d->data=4;
	e->data=5;
	a->colour=0;
	b->colour=0;
	c->colour=0;
	d->colour=0;
	e->colour=0;
	struct node *arr[5];
	arr[0]=a;
	arr[1]=b;
	arr[2]=c;
	arr[3]=d;
	arr[4]=e;
	add_edge(arr,a,d,4,5);
	add_edge(arr,a,b,2,5);
	add_edge(arr,b,c,6,5);
	add_edge(arr,b,d,1,5);
	add_edge(arr,d,e,1,5);
	add_edge(arr,e,b,4,5);
	add_edge(arr,e,c,1,5);
	for(i=0;i<5;i++)
	{
		printf("%d\t",arr[i]->data);
		cur = arr[i]->next;
		while(cur!=NULL)
		{
			printf("%d %d\t",cur->data,cur->weight);
			cur = cur->next;
		}
		printf("\n");
	}
	int arr1[100];
	for(i=0;i<n;i++){  //let a=hospital node 
		a1=dijkstra(arr,b,a);
		a2=dijkstra(arr,c,a);
		a3=dijkstra(arr,d,a);
		a4=dijkstra(arr,e,a);	
		for(i=0;i<n;i++){
			arr1[i]=find_max(a1,a2,a3,a4);// by using merge sort
		}
	}
	find_min()	
	print_path(c);
	print_maxlengthtohospital();
	
}
void find_min(int n)
	{	
		/*maximum found in the above step*/
		hosp_node=sort(arr1,0,n);
	}
int print_maxlengthtohospital();
	{
		/*maximum distances from other nodes to a*/;
	}
void bottom_up_heapyfy(struct node *arr[] , int i)
{
	int p = (i-1)/2;
	while(p>=0)
	{
		if(arr[i]->pri<arr[p]->pri)
		{
			arr[i]->heap=p;
			arr[p]->heap=i;
			swap(&arr[i],&arr[p]);
		}
		else
			break;
		i = p;
		p = (i-1)/2;
	}
}
void top_down_heapyfy(struct node* arr[] , int i)
{
	int l = 2*i+1;
	int r = 2*i+2;
	int j;
	int k=i;
	while(r<curr)
	{
		if(arr[l]->pri <= arr[r]->pri)
			j = l;
		else
			j = r;
		if(arr[i]->pri > arr[j]->pri)
		{
			arr[i]->heap=j;
			arr[j]->heap=i;
			swap(&arr[i],&arr[j]);
		}
		else
			break;
		i = j;
		l = 2*i+1;
		r = 2*i+2;
	}
	if (l == curr-1 && arr[i] > arr[l])
	{
		arr[i]->heap=l;
		arr[l]->heap=i;
		swap(&arr[i],&arr[l]);
	}
}
void swap(struct node** a,struct node** b)
{
	struct node* t;
	t = *a;
	*a = *b;
	*b = t;
}
void enqueue(struct node* arr[],struct node* n)//adding an noe with priority i
{
	arr[curr] = n;
	n->heap=curr;			
	bottom_up_heapyfy(arr,curr);
	curr++;
}
struct node* dequeue(struct node* arr[])//removing the least priority node
{
	if(curr > 0)
	{
		arr[0]->heap=curr-1;
		arr[curr-1]->heap=0;
		swap(&arr[0],&arr[curr-1]);
		curr--;
		top_down_heapyfy(arr,0);
		return arr[curr];
	}
	return NULL;
}
void add_edge(struct node *arr[],struct node *s,struct node *e,int w,int n)
{
	struct node_ll *new;
	int i;
	new=(struct node_ll*)malloc(sizeof(struct node_ll));
	new->data=e->data;
	new->weight=w;
	for(i=0;i<n;i++)
	{
		if(arr[i]->data==e->data)
			break;
	}
	new->parent=arr[i];
	for(i=0;i<n;i++)
	{
		if(s->data == arr[i]->data)
				break;
	}
	if(arr[i]->next == NULL)
		arr[i]->next = new;
	else
	{
		struct node_ll *cur = arr[i]->next;
		while(cur->next!=NULL)
			cur = cur->next;
		cur->next = new;
		new->next = NULL;
	}
}
void dijkstra(struct node *arr[],struct node *s,int n)
{
	struct node *u,*w;
	struct node_ll *v;
	int i=0;
	enqueue(reqheap,s);
	s->colour = 1;
	s->p=s;
	s->pri=0;
	while(curr>0)
	{
		u=dequeue(reqheap);
		printf("%d %d %d\n",u->data,(u->p)->data,u->pri);
		u->colour = 2;
		v=u->next;
		while(v!=NULL)
		{
			w = v->parent;
			if(w->colour==0)
			{
				w->pri=u->pri+v->weight;
				w->colour=1;
				w->p=u;
				enqueue(reqheap,w);
			}
			else if(w->colour==1)
			{
				if(w->pri>u->pri+v->weight)
				{
					w->pri=u->pri+v->weight;
					bottom_up_heapyfy(reqheap,w->heap);
					w->p=u;
				}
			}
			v=v->next;
		}
	}
}
void print_path(struct node *v)
{
	if(v->p==v)
		printf("%d\t",v->data);
	else
	{
		print_path(v->p);
		printf("%d\t",v->data);
	}
}

int b[10];
int find_min(int a[],int left,int mid,int right)
{
int p=mid+1,k=left,n=0,i;
	while(p<=right && k<=mid)
	{
		if(a[p]<=a[k])
			{
			b[n]=a[p];
			n++;
			p++;
			}	
		else
			{
			b[n]=a[k];
			n++;
			k++;
			}
	}
while(p<=right)
{
	b[n]=a[p];
	n++;
	p++;
}
while(k<=mid)
	{
			b[n]=a[k];
			n++;
			k++;
			}
for(i=0;i<n;i++)
a[left+i]=b[i];
return a[0];
}

void sort(int a[],int left,int right)
{
if(left<right)
{
int mid=(right+left)/2;
sort(a,left,mid);
sort(a,mid+1,right);

merge(a,left,mid,right);
}
}
void print(int a[],int size)
{
int i;
for(i=0;i<size;i++)
	{
	printf("%d\n ",a[i]);
	}
}
