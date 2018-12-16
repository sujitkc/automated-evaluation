#include<stdio.h>
#include<stdlib.h>
 
#define MAX 100  
 
#define initial 1
#define visited 2

void push(int i);
void DF_Traversal();
void DFS(int v);
 int n;    
int adj[MAX][MAX];
int state[MAX]; 
void create_graph();

 int main()
 {	create_graph();
 	DF_Traversal();
 	return 0;
 }
 
struct stack
{
    int stk[];
    int top;
};
typedef struct stack STACK;
STACK s;

void push (int i)
{
    int num=i;
    if (s.top == (n - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
       
        s.top = s.top + 1;
        s.stk[s.top] = num;
    }
    return;
}

void DF_Traversal()
{
    int v;
    
    for(v=0; v<n; v++) 
    {   state[v] = initial;}
    
    printf("Enter Start Vertex for DFS: \n");
    scanf("%d", &v);
    DFS(v);
}
void DFS(int v)
{	int j,i=v;
	state[v]=visited;
	push(v);
	printf("%d\n",v);
 	for(j=0;j<n;j++)
 	{if(adj[v][j]==1&&state[j]==initial)
 		{DFS(j);
		 }
	 }
}

void create_graph()
{
    int count,maxedge,origin,destin,test_cases;
    printf("no of test cases");
    scanf("%d,&test_cases");
    printf("Enter number of vertices  ");
    scanf("%d",&n);
    maxedge = n*(n-1);
    printf("to stop enter (-1)\n");
    for(count=1; count<=maxedge; count++)
    {  
        printf("Enter edge %d : ",count);
        scanf("%d %d",&origin,&destin);
 
        if((origin == -1) && (destin == -1))
            break;
 
        if(origin>=n || destin>=n || origin<0 || destin<0)
        {
            printf("Invalid edge!\n");
            count--;
        }
        else
        {
            adj[origin][destin] = 1;  
        }
    }
}


