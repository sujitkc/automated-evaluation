
#include <stdio.h>
#include <limits.h>

#define V 9

int minDistance(int dist[], int sptSet[],int sir[])
{

   int min = INT_MAX, min_index;
   int v;
   for (v = 0; v < V; v++)
     if (sptSet[v] == 0 && dist[v] <= min && sir[v]==0)
         min = dist[v], min_index = v;
    	

   return min_index;
}

int printSolution(int dist[], int n)
{
   int i;
  printf("Vertex\n");
   for (i = 0; i < V; i++)
   {
   	if(dist[i]>2000)
   	{
	   printf("%d ",i);
	   printf("\t\tno path\n");
	}
	else
      printf("%d \t\t %d\n", i, dist[i]);
  }
}

int dijkstra(int graph[V][V], int src, int v,int sir[],int de)
{

     int dist[V];     

     int sptSet[V];
     int i;

     for (i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

     dist[src] = 0;
     int count;

     for (count = 0; count < V-1; count++)
     {

       int u = minDistance(dist, sptSet,sir);

       sptSet[u] = 1;
       if(u==de)
       {
       	return 0;
	   }
       ///sir=1;
       
       int v;

       for (v = 0; v < V; v++)

         if (!sptSet[de] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
            
			{
			dist[v] = dist[u] + graph[u][v];
           	sir[i]=1;
           	}
           /*if(sptset[de]==1)
           {
           	return 0;
		   }*/
        
            
     }
     ///printf("%d%d%d",sir[5],sir[1],sir[2]);

     printSolution(dist, V);
     ///dijkstracheck(graph, 0,10,4,sir);
     return 0;
    

	 
}
int minDistancen(int dist[], int sptSet[],int sir[])
{

   int min = INT_MAX, min_index;
   int v;
   for (v = 0; v < V; v++)
     if (sptSet[v] == 0 && dist[v] <= min && sir[v]==0)
         min = dist[v], min_index = v;
    	else{
    		
    		
    		break;
    	}
    	
	
   return min_index;
}

void dijkstracheck(int graph[V][V], int src, int v, int de,int sir[])
{

     int dist[V];     

     int sptSet[V];
     int i;

     for (i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

     dist[src] = 0;
     int count;


     for (count = 0; count < V-1; count++)
     {

       int u = minDistancen(dist, sptSet,sir);

       sptSet[u] = 1;
       int v;

       for (v = 0; v < V; v++)

         if (!sptSet[de] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
            sir[i]=1;
            
     }

     printSolution(dist, V);
     

	 
}

int main()
{
	int sir[10],i;

   int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
	int de=4;
	     for(i=0;i<10;i++)
     {
     	sir[i]=0;
	 }
	dijkstra(graph, 0,10,sir,de);
///	printf("%d%d%d",sir[5],sir[1],sir[2]);
   dijkstracheck(graph, 0,10,de,sir);
    

    return 0;
}
