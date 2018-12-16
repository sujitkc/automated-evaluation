#include <stdio.h>
#include <stdlib.h>
int n,e;
int boolean[10];
struct node{
    int color; // if colour=1->red,colour=2->yellow,colour=3->blue
    int p;// p=priority
};
struct node *arr[10];// array is storing all pointer to the nodes

struct node2{
    int a;// name (here the number) of  the node
    int w;// weight
    struct node2 *ptr;
};
struct node2 *arr2[10];

void create_graph()
{
    int i,j,r,x,y,d,m;
    printf("enter the number of nodes in the graph:");
    scanf("%d",&e);
    struct node *l;
    for(i=1;i<e+1;i++)
    {
        l=(struct node*)malloc(sizeof(struct node));
        l->color=1;
        l->p=0;
        arr[i]=l;
    }
    printf("enter m");
    scanf("%d",&m);
    printf("enter the number of nodes u want to connect to two nodes and weight ");
    for(i=0;i<m;i++)
    {
        scanf("%d %d %d",&x,&y,&d);
        struct node2* p=NULL;
        struct node2* q=NULL;
        p=arr2[x];
        while(p!=NULL)
        {
            p=(struct node2*)malloc(sizeof(struct node2));
            p->a=y;
            p->w=d;
        }
        q=arr2[y];
        while(q!=NULL)
        {
            q=(struct node2*)malloc(sizeof(struct node2));
            q->a=x;
            q->w=d;
        }
    }
    
}
int arr3[10];
int c=1,d=1;//c is index to the left most element in the array
// d is index to the right most element in the array
void insert_minheap(int n)
{
arr3[d]=n;
int k=d;
while(k>c)
{
	if(arr[arr3[k/2]]->p>arr[arr3[k]]->p)
	{
		int t;
		t=arr3[k/2];
		arr3[k/2]=arr3[k];
		arr3[k]=t;
		k=k/2;
	}
	else
	{
		break;
	}
}
}

int dijktras(int j, int r)
{
    int i; 
    arr3[1]=j;
    struct node2 *b;
    while(c<=d)
    {
    	arr[arr3[c]]->color=3;
    	b=arr2[arr3[c]];
    	int y=c,f=0;	
    	while(b!=NULL)
    	{
                if(boolean[b->a]==1)
                    {
                        arr[b->a]->p=1000;
                    }   
    			else if(arr[b->a]->color==1)
    			{
                    arr[b->a]->color=2;
    				arr[b->a]->p=arr[arr3[y]]->p+b->w;
                    d++;
    				insert_minheap(b->a);
    			}
    			else
                    {
                        if(arr[b->a]->p>arr[arr3[y]]->p+b->w)
                        {
                        arr[b->a]->p=arr[arr3[y]]->p+b->w;  
                        }
                    }
    		b=b->ptr;
    	}
    	c++;
}
printf("%d",arr[r-1]->p);
return arr[r]->p;
}
int main()
{
    int d;
    scanf("%d",&d);// no:of test cases
    while(d)
    {
    int i,s,t;
    for(i=1;i<e+1;i++)
    {
        boolean[i]=0;
    }
    int p,q;
    create_graph();
    dijktras(1,4);
    for(i=1;i<e+1;i++)
    {
        p=dijktras(1,i);
        q=dijktras(i,e);
        if(p==q)
        {
            boolean[i]=1;// passing through this point;
        }
    }
    scanf("%d %d",&s,&t);
    if(dijktras(s,t)==0)
    {
        printf("NOT POSSIBLE");
    }
    else
    {
    printf("%d",dijktras(s,t));
     }
}
d--;
}
































