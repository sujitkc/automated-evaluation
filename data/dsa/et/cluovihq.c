#include<stdio.h>
#include<stdlib.h>

struct adjnode {
	int dest;
	int weight;
	struct adjnode *next;
};

struct adjlist{
	struct adjnode *head;
};

struct graph{
	int vertices;
	struct adjlist *arr;
};

struct adjnode *newnode(int dest,int weight){
	struct adjnode *newNode=(struct adjnode *)malloc(sizeof(struct adjnode));
	newNode->dest=dest;
	newNode->weight=weight;
	newNode->next=NULL;
	return newNode;
}

struct graph *creategraph(int vertices){
	struct graph *newGraph=(struct graph *)malloc(sizeof(struct graph));
	newGraph->vertices=vertices;
	newGraph->arr=(struct adjlist *)malloc(vertices *(sizeof(struct adjlist)));
	int i;
	for(i=0;i<vertices;i++){
		newGraph->arr[i].head=NULL;
	}
	return newGraph;
}

void addedge(struct graph *G,int source,int dest,int weight){
	struct adjnode *edge=newnode(dest,weight);
	edge=newnode(source,weight);
	edge->next=G->arr[dest].head;
	G->arr[dest].head=edge;
}

struct MinHeapNode{
	int value;
	int distance;
};

struct MinHeap{
	int size;
	int capacity;
	int *pos;
	struct MinHeapNode **arr;
};

struct MinHeapNode *newheapNode(int value,int distance){
	struct MinHeapNode *heapnode=(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	heapnode->value=value;
	heapnode->distance=distance;
	return heapnode;
}

struct MinHeap *newheap(int capacity){
	struct MinHeap *heap =(struct MinHeap*) malloc(sizeof(struct MinHeap));
	heap->pos=(int *)malloc(capacity * sizeof(int));
	heap->capacity=capacity;
	heap->size=0;
	heap->arr=(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return heap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void Heapify(struct MinHeap *heap,int i){
	int min,left,right;
	min=i;
	left=2*i+1;
	right=2*i+2;
	if(left<heap->size && heap->arr[left]->distance<heap->arr[min]->distance){
		min=left;
	}
	if(right<heap->size && heap->arr[right]->distance<heap->arr[min]->distance){
		min=right;
	}
	if(min!=i){
		struct MinHeapNode *minimum=heap->arr[min];
		struct MinHeapNode *inode=heap->arr[i];
		swapMinHeapNode(&heap->arr[min],&heap->arr[i]);
		Heapify(heap,min);
	}
}

struct MinHeapNode *extractMin(struct MinHeap *heap){
	if(heap->size==0){
		return NULL;
	}
	struct MinHeapNode *root=heap->arr[0];
	struct MinHeapNode *last=heap->arr[heap->size-1];
	heap->arr[0]=last;
	heap->pos[root->value]=heap->size-1;
	heap->pos[last->value]=0;
	heap->size=heap->size-1;
	Heapify(heap,0);
	return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist){
    int i = minHeap->pos[v];
    minHeap->arr[i]->distance = dist;
    while (i && minHeap->arr[i]->distance < minHeap->arr[(i - 1) / 2]->distance){
        minHeap->pos[minHeap->arr[i]->value] = (i-1)/2;
        minHeap->pos[minHeap->arr[(i-1)/2]->value] = i;
        swapMinHeapNode(&minHeap->arr[i],  &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int c=10000,b; 
void printArr(int scr,int dist[], int n){
	int i;
    int o=-1;
    for (i = 0; i < n; ++i){
    	if(dist[i]>o){
    		o=dist[i];
		}
	}
	if(o<c){
		c=o;
		b=scr;
	}
}
 
void dijkstra(struct graph* graph, int src){
	int v;
    int V = graph->vertices;
    int dist[V];
    struct MinHeap* minHeap = newheap(V); 
    for (v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->arr[v] = newheapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->arr[src] = newheapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (minHeap->size!=0){
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->value;
        struct adjnode * pCrawl = graph->arr[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (minHeap->pos[v] < minHeap->size && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]){
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    printArr(src,dist, V);
}
 
int main(){
    int V,t,E,k=0,z=0;
    scanf("%d",&t);
    while(z<t){
    scanf("%d%d",&V,&E);
    struct graph* graph = creategraph(V);
    while(k<E){
    	int p,q,r;
    	scanf("%d%d%d",&p,&q,&r);
    	addedge(graph,p-1,q-1,r);
		k++;	
	}
	k=1;
    while(k<=V){
    	dijkstra(graph, k-1);
    	k++;
	}
    if(c==10000){
    	c=-1;
	}
	if(c==-1){
		printf("-1");
	}
	else{
		printf("The hospital must be built at node %d whose mix cost is %d\n",b+1,c);
	}
    z++;
    }
    return 0;
}
