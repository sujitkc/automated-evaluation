#include <stdio.h>
#include <limits.h>
#define V 8
int arr[V];
int d1[V];
int dn[V];
int ds[V];
int k=0;
int b[V]={0};
void TopDown(int arr[],int i,int n){
	int lc=2*i+1,rc=2*i+2,j,t;
	while(rc<n){
		if(arr[lc]<arr[rc])
			j=lc;
		else
			j=rc;
		if(arr[i]<arr[j])
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
	if(lc==n-1&&arr[i]>arr[lc]){
		t=arr[i];
		arr[i]=arr[lc];
		arr[lc]=t;
	}
}
void BottomUp(int arr[],int i){
	int p,t;
	while(i>0){
		p=(i-1)/2;
		if(arr[p]>arr[i]){
			t=arr[i];
			arr[i]=arr[p];
			arr[p]=t;
		}
		else
			break;
		i=p;		
	}
}
int minDistance(int dist[], int arr[])
{
   int min = INT_MAX, min_index;
   int v; 
   for (v = 0; v < V; v++)
     if (arr[v] == 0 && dist[v] <= min)
         min = dist[v], min_index = v;
   return min_index;
}
void IncreaseKey(int arr[],int n,int i1,int x){
	arr[i1]=x;
	TopDown(arr,i1,n);
}
void DecreaseKey(int arr[],int i1,int x){
	arr[i1]=x;
	BottomUp(arr,i1);
}
void BuildHeap(int arr[],int n){
	int i=n/2;
	while(i>=0){
		TopDown(arr,i,n);
		i--;
	}
}
int printSolution(int dist[], int n)
{
   int i;
   printf("Vertex   Distance from Source\n");
   for (i = 0; i < V; i++)
   {
	  if(k==0)
	  d1[i]=dist[i];
	  else if(k==1)
	  dn[i]=dist[i];
	  else if(k==2)
	  ds[i]=dist[i];
	  if(b[i]==1)
		dist[i]=INT_MAX; 
      printf("%d \t\t %d\n", i, dist[i]);
   }
}
void dijkstra(int graph[V][V], int src)
{
     int dist[V];
	 int i,v;      
     for (i=0;i<V;i++)
        dist[i] = INT_MAX, arr[i] = 0;
     dist[src]=0;
     for (i = 0; i < V-1; i++)
     {
       int u = minDistance(dist, arr);
       arr[u] = 1;
       for (v = 0; v < V; v++)
         if (arr[v]==0 && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v]&&b[u]==0)
            dist[v] = dist[u] + graph[u][v];
     }
     printSolution(dist, V);
}
int main()
{
   /*int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 1, 0, 0, 0, 0, 11, 0},
                      {0, 1, 0, 2, 0, 4, 0, 0, 2},
                      {0, 0, 2, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };*/
    int graph[V][V]={{0,4,0,0,0,0,8,0},
		     {4,0,1,0,0,0,11,0},
		     {0,1,0,2,4,0,0,2},
		     {0,0,2,0,0,0,0,0},
		     {0,0,4,0,0,2,0,0},
                     {0,0,0,0,2,0,1,0},
		     {8,11,0,0,0,1,0,7},
		     {0,0,2,0,0,0,7,0}
					};
    dijkstra(graph, 0);
	k++;
	dijkstra(graph,7);
	k++;
	int i;
	for(i=0;i<V;i++)
		if(d1[i]+dn[i]==d1[7])
			b[i]=1;
	for(i=0;i<V;i++)
		printf("%d %d\n",i,b[i]);
	dijkstra(graph,3); 
    return 0;
}
