#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct AdjListNode 
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
struct node
{
	int val;
	struct node *next;
};
struct AdjList
{
    struct AdjListNode *head; 
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
struct node *new(int val)
{
	struct node *newnode=(struct node*)(malloc(sizeof(struct node)));
	newnode->val=val;
	newnode->next=NULL;
	return newnode;
}
void insert(struct node **top,int val)
{
    struct node *newnode=new(val);
    struct node *current;
    if(*top==NULL)
    {
        *top=newnode;
    }
    else
    {
        current=*top;
        while(current->next!=NULL)
        {
            current=current->next;
        }
        current->next=newnode;
    }
}
 
int dijkstra(struct Graph* graph, int src,int d)
{
    int V = graph->V;
    int dist[V];      
 
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
    //printf("distance %d\n",dist[d] );
    return dist[d];
}
void dijkstra1(struct Graph* graph, int src,int d,int emp[])
{
    int V = graph->V;
    int dist[V];     
 	struct node* top=NULL;
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
 	emp[0]=1;
 	
 	if(emp[d]==1)
 	{
 		emp[d]=0;
 	}
    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        if(emp[u]!=1)
        {
        	insert(&top,u);
        }
 
        struct AdjListNode* pCrawl = graph->array[u].head;
        if(emp[u]!=1)
        {
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
    }
 	//printf("from s to t\n");
    //printArr(dist, V);
    printf("distance %d\n",dist[d] );
    struct node *curr= top;
    /*while(curr!=NULL)
    {
    	printf("short path %d\n",curr->val );
    	curr=curr->next;
    }*/
}
void path(struct Graph *graph,int emp[],int p,int q)
{
	int i;
	int k=graph->V;
	for(i=1;i<k-1;i++)
	{
		int n1=dijkstra(graph,0,k-1);
		int n2=dijkstra(graph,0,i);
		int n3=dijkstra(graph,i,k-1);
		if(n1==(n2+n3))
		{
			emp[i]=1;
		}
	}
	dijkstra1(graph,p,q,emp);
}
 
int main()
{
    int V = 6;
    int emp[V];
    int i;
    for(i=0;i<V;i++)
    {
    	emp[i]=0;
    }
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 0, 1);
    addEdge(graph, 0,3,1);
    addEdge(graph, 3,0,1);
    addEdge(graph, 3,4,2 );
 	addEdge(graph,  4,3,2);
 	addEdge(graph,  4,5,1);
 	addEdge(graph,  5,4,1);
 	addEdge(graph,  4,2,4);
 	addEdge(graph,  2,4,4);
 	addEdge(graph,   1,2,3);
 	addEdge(graph,  2,1,3 );
 	addEdge(graph,  1,3,2 );
 	addEdge(graph,   3,1,2);


    //int h=dijkstra(graph, 0,5);
    path(graph,emp,0,4);
 	//printf("%d\n",h );
    return 0;
}