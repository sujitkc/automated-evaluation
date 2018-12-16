#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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
    int i;
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (i = 0; i < V; ++i)
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
    int size;      
    int capacity;  
    int *pos;     
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
 
int isEmpty(struct MinHeap* minHeap)
{   
    return minHeap->size==0;
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
    int i;
    printf("Vertex   Dist[vertex]\n");
    for (i = 1; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
   
 }
void dijkstra(int * check,int *dist,struct Graph* graph, int src)
{
    int u,V = graph->V;// Get the number of vertices in graph
 struct MinHeapNode* minHeapNode;
    struct MinHeap* minHeap = createMinHeap(V);
   int v;
    for ( v = 0; v < V; ++v)
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
       //printf("%p\n",*(minHeap->array[0]) );
        if(check[(minHeap->array[0])->v]==0)
{
        minHeapNode = extractMin(minHeap);
        
        u = minHeapNode->v; 

        struct AdjListNode* headnode = graph->array[u].head;
        while (headnode != NULL)
        {
            int v = headnode->dest;
 
            if (isInMinHeap(minHeap, v)==1 && dist[u] != INT_MAX && headnode->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + headnode->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            headnode = headnode->next;
        }

 }

       
    }

    printArr(dist, V);
}
 
 
int main()
{   
   int check[9]={0};
  

    int i,V = 8;
    int dist[V],dist1[V];
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 4, 2);
    addEdge(graph, 1, 1, 5);
    addEdge(graph, 1, 7, 6);
    addEdge(graph, 2, 2, 6);
    addEdge(graph, 2, 6, 4);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 4, 8, 3);
   
    addEdge(graph, 5, 6, 3);
    addEdge(graph, 6, 7, 2);
    addEdge(graph, 6, 8, 7);
  
 
    dijkstra(check,dist,graph, 1);
    dijkstra(check,dist1,graph,8);
    for(i = 0; i < V;++i)
    {
        if(dist[i]+dist1[i]==dist[8])
        {
        
            check[i]=1;
        }   
    }
    int dist3[V];
    dijkstra(check,dist3,graph,4);
    printf("shortest path is dist3[7]\n");
    return 0;
}
