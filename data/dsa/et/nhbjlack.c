// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
  
#include <stdio.h>
#include <limits.h>
  
// Number of vertices in the graph
#define V 9
  
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == 0 && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}
  
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
  printf("%d",dist[n]);
      return dist[n];
}
  
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src, int des)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
  
     int sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
  
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;
  
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
  
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
  
       // Mark the picked vertex as processed
       sptSet[u] = 1;
  
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
  
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
  
     // print the constructed distance array
     printSolution(dist, des);
}
  
// driver program to test above function
int main()
{
	
/* Let us create the example graph discussed above */
   
  int t,n,m,s,x,y,d,j,i,k;

	scanf("%d", &t);
for(k=0;k<t;k++)
{
	scanf("%d%d",&n,&m);
	scanf("%d%d",&s,&t);
int graph[n][n];
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{
graph[i][j]=0;
}
}
	
int a[n];
for(i=0;i<n;i++)
{
a[i]=0;
}

for(i=0;i<m;i++)
{ 
scanf("%d%d%d",&x,&y,&d);
graph[x][y]=graph[x][y]+d;
graph[y][x]=graph[y][x]+d;
}
      
    
   
int l1=dijkstra(graph,0,n-1);
int l2,l3;
for(i=0;i<n;i++)
{

l2=dijkstra(graph,0,s);
l3=dijkstra(graph,s,n-1);
if(l3+l2==l1);
{
a[i]==1;
}
	
}
for(i=0;i<n;i++)
{
if(a[i]==1)
{
for(j=0;i<n;j++)
{
graph[i][j]=0;
graph[j][i]=0;
}
}

}
int l4=dijkstra(graph,s,t);
}
    
  
   return 0;
}
