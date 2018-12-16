#include<stdio.h>
#include<stdlib.h>
struct node
{
	int heap;
	int data;
	struct node_ll *next;
	int colour;//0->red,1->yellow,2->blue
	struct node *p;
	int pri;
	int max_dist;
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
void transpose(struct node *arr[],int n);
struct node* hospital_find(struct node* arr[],int n);
int curr=0;
struct node *trans_array[100000];;
struct node *reqheap[100000];
void main()
{
	int t,i,m,n,j,s,e,d;
	struct node *hospital;
	struct node *arr[100000];
	struct node_ll *cur;
	scanf("%d",&t);
	for(i=0;i<t;i++)
	{
		scanf("%d %d",&n,&m);
		for(j=0;j<n;j++)
		{
			arr[j]=(struct node*)malloc(sizeof(struct node));
			arr[j]->data=j+1;
			arr[j]->colour=0;
			arr[j]->max_dist=0;
		}
		for(j=0;j<m;j++)
		{
			scanf("%d %d %d",&s,&e,&d);
			add_edge(arr,arr[s-1],arr[e-1],d,n);
		}
		transpose(arr,n);
		for(j=0;j<n;j++)
		{
			dijkstra(trans_array,trans_array[j],n);
		}
		hospital=hospital_find(trans_array,n);
		printf("%d\t%d\n",hospital->data,hospital->max_dist);
	}
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
	int j;
	for(j=0;j<n;j++)
	{
		arr[j]->colour=0;
	}
	struct node *u,*w;
	struct node_ll *v;
	int i=0;
	enqueue(reqheap,s);
	s->colour = 1;
	s->p=s;
	s->pri=0;
	s->max_dist=0;
	while(curr>0)
	{
		u=dequeue(reqheap);
		if(u->pri>s->max_dist)
		{
			s->max_dist=u->pri;
		}
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
	for(i=0;i<n;i++)
	{
		if(arr[i]->colour==0)
		{ 
			s->max_dist = -1;
			break;
		}
	}
}
void transpose(struct node *arr[],int n)
{
	struct node *u,*w;
	struct node_ll *v;
	int i=0;
	for(i=0;i<n;i++)
	{
		trans_array[i]=(struct node*)malloc(sizeof(struct node));
		trans_array[i]->data=arr[i]->data;
		trans_array[i]->colour=0;
	}
	for(i=0;i<n;i++)
	{
		u = arr[i];
		v=u->next;
		while(v!=NULL)
		{
			w=v->parent;
			add_edge(trans_array,w,u,v->weight,n);
			v=v->next;
		}
	}
}
struct node* hospital_find(struct node* arr[],int n)
{
	int i,min=arr[0]->max_dist;
	struct node *t=arr[0];
	for(i=1;i<n;i++)
	{
		if(arr[i]->max_dist!=-1)
		{
			if(arr[i]->max_dist>0&&min<0)
			{	
				min=arr[i]->max_dist;
				t=arr[i];
			}
			else if(arr[i]->max_dist<min)
			{
				min=arr[i]->max_dist;
				t=arr[i];
			}
		}
	}
	return t;
}
		
