#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
struct AdjListNode 
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
struct Graph
{
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode
{
    int  v;
    int dist;
};
 
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
int arrmarked[10000];
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    struct MinHeapNode* root = minHeap->array[0];
 
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
 
    minHeap->array[i]->dist = dist;
 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
int  isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra2(struct Graph* graph, int src,int dist[])
{
    int V = graph->V;// Get the number of vertices in graph
//    int dist[V];      // dist values used to pick minimum weight edge in cut
 
    struct MinHeap* minHeap = createMinHeap(V);
 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int emp = 1;
        while ( arrmarked[minHeapNode->v] == 0)
        {
        if ( isEmpty(minHeap))
        {
            emp = 0;
            break;
        }   
        minHeapNode = extractMin(minHeap);
        }
        if ( !emp)
        {
            break;
        }
       
        int u = minHeapNode->v; // Store the extracted vertex number
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            if (isInMinHeap(minHeap, v)==1 && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
   
   // printArr(dist, V);
}
 
 
void dijkstra(struct Graph* graph, int src,int dist[])
{
    int V = graph->V;// Get the number of vertices in graph
//    int dist[V];      // dist values used to pick minimum weight edge in cut
 
    struct MinHeap* minHeap = createMinHeap(V);
 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
 
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            if (isInMinHeap(minHeap, v)==1 && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
   // printArr(dist, V);
}
 
 
int main()
{
    int t;
    scanf("%d",&t);
    while( t--)
    {
    int V , m;
    scanf("%d%d",&V,&m);
    struct Graph* graph = createGraph(V);
    int i1;
    int stpm,dtpm;
    scanf("%d%d",&stpm,&dtpm);
    for(i1=0;i1<m;i1++) 
    {
        int x1,y1,d1;
        scanf("%d%d%d",&x1,&y1,&d1);
        addEdge(graph, x1-1, y1-1, d1);
    }
    /*
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);*/
    int dist1[V];
    int dist2[V];
    //printf("enter source and dest of pm\n");
    dijkstra(graph, 0, dist1);
    dijkstra(graph, V-1, dist2);
    int i ;/*
    for(i=0;i<V;i++)
    {
        printf("%d : %d\n",i,dist1[i]);
    }
    printf("Second\n");
        for(i=0;i<V;i++)
    {
        printf("%d : %d\n",i,dist2[i]);
    } */
    memset(arrmarked,-1,sizeof(arrmarked));  
    for(i=0;i<V;i++)
    {
        if(dist1[i]+dist2[i] == dist1[V-1])
        {
            arrmarked[i] = 0;
        }
    }
    if ( arrmarked[stpm-1] == 0 || arrmarked[dtpm-1] == 0)
    {
        printf("NOT POSSIBLE\n");
    }
    else
    {
    //printf("shortest path\n");
    for(i=0;i<V;i++)
    {/*
        if ( arrmarked[i] == 0)
        {
            printf("%d  ",i);
        }*/
    }
    
    printf("\n");
    int dist3[V];
    dijkstra2(graph,stpm-1,dist3);
    if ( dist3[dtpm-1] == INT_MAX)
    {
        printf("NOT POSSIBLE\n");
    }
    else
    {
    printf("so ans is %d\n",dist3[dtpm-1]);
    } }
        
    }
    return 0;
}
