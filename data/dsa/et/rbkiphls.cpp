#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>

using namespace std;

struct adjListNode{
    int v;
    int w;
    adjListNode* next;
};

struct adjList{
    adjListNode* head;
};

struct Graph{
    int v;
    adjList* array;
};

struct heap_node{
    int vertex;
    int key;
};

struct heap_struct{
    int* pos;
    heap_node* heap;
    int size;
    int count;
};

void swap_nodes(heap_struct* heap_struct, int i, int j){
    /*cout << "In swap_nodes" << endl;
    cout << "Swapping nodes " << i << ", " << j << endl;*/
    heap_node* temp1 = new heap_node;
    heap_node* temp2 = new heap_node;
    
    temp1->vertex = heap_struct->heap[i].vertex;
    temp1->key = heap_struct->heap[i].key;

    temp2->vertex = heap_struct->heap[j].vertex;
    temp2->key = heap_struct->heap[j].key;

    heap_struct->pos[heap_struct->heap[i].vertex] = j;
    heap_struct->pos[heap_struct->heap[j].vertex] = i;

    (heap_struct->heap+i)->key = temp2->key;
    (heap_struct->heap+i)->vertex = temp2->vertex;

    (heap_struct->heap+j)->key = temp1->key;
    (heap_struct->heap+j)->vertex = temp1->vertex;/*

    *(heap + i) = *temp1;
    *(heap + j) = *temp2;*/

    /*cout << "Position " << i << " is now " << heap_struct->heap[i].vertex << " " << heap_struct->heap[i].key << endl;
    cout << "Position " << j << " is now " << heap_struct->heap[j].vertex << " " << heap_struct->heap[j].key << endl;*/
}

void min_heapify(heap_struct* heap_struct, int i){
    int l = 2*i+1, r = 2*i+2, min = i;
    
    if(l < heap_struct->size && heap_struct->heap[i].key > heap_struct->heap[l].key)
        min = l;
    if(r < heap_struct->size && heap_struct->heap[min].key > heap_struct->heap[r].key)
        min = r;
    if(min != i){
        /*heap_struct->pos[heap_struct->heap[i].vertex] = min;
        heap_struct->pos[heap_struct->heap[min].vertex] = i;*/
        swap_nodes(heap_struct, i, min);
        min_heapify(heap_struct, min);
    }
    
}
/*
void min_heapify(heap_struct* heap_struct, int i){
    cout << "In minheapify" << endl;

    int l = 2*i+1, r = 2*i+2, min = i;

    cout << "l is " << l << ", r is " << r << "& i is " << i << endl;

    heap_node* arr = heap_struct->heap;
    if(l < heap_struct->size && arr[min].key > arr[l].key)
        min = l;
    if(r < heap_struct->size && arr[min].key > arr[r].key)
        min = r;
    int count = 0;
    if(min != i){
        count = 1;
        heap_struct->pos[arr[i].vertex] = min;
        heap_struct->pos[arr[min].vertex] = i;
        swap_nodes(arr, i, min);

        cout << "Swapping nodes " << i << ", " << min << endl;
        cout << "Position " << i << " is now " << arr[i].vertex << " " << arr[i].key << endl;
        cout << "Position " << min << " is now " << arr[min].vertex << " " << arr[min].key << endl;

        min_heapify(heap_struct, heap_struct->pos[arr[min].vertex]);
    }
    if(count != 1)
        cout << "Condition not satisfied" << endl;
}
*/

heap_node* extract_min(heap_struct* heap_struct){
    heap_node* result = new struct heap_node;

    result->vertex = heap_struct->heap[0].vertex;
    result->key = heap_struct->heap[0].key;

    /*heap_struct->pos[heap_struct->heap[0].vertex] = heap_struct->size - 1;
    heap_struct->pos[heap_struct->heap[heap_struct->size - 1].vertex] = 0;

    heap_struct->heap[0] = heap_struct->heap[(heap_struct->size - 1)];*/
    swap_nodes(heap_struct, 0, heap_struct->size-1);
    
    heap_struct->size--;

     
    min_heapify(heap_struct, 0);

    return result;
}

/*
heap_node* extract_min(heap_struct* heap_struct){
    cout << "In extract_min" << endl;

    heap_node* arr = heap_struct->heap;
    int* position = heap_struct->pos;
    int size = heap_struct->size;
    heap_node* result = (heap_node*)malloc(sizeof(heap_node));

    result->vertex = (arr+0)->vertex;
    result->key = (arr+0)->key;

    *(arr+0) = *(arr + size - 1);

    //heap_struct->heap[0] = heap_struct->heap[heap_struct->size - 1];

    *(position + 0) = size - 1;

    //heap_struct->pos[0] = heap_struct->size - 1;
    *(position + size - 1) = 0;

    //heap_struct->pos[heap_struct->size - 1] = 0;

    heap_struct->size -= 1;

    cout << "Minheapifying now.." << endl;
    min_heapify(heap_struct, 0);

    return result;
}
*/

void decrease_key(heap_struct* heap_struct, int v, int key){
    /*cout << "In decrease_key" << endl;*/
    //int i = heap_struct->pos[v];
    heap_node* arr = heap_struct->heap;
    int* position = heap_struct->pos;
    int i = position[v];
    /*cout << "Decresing key at position " << i << endl;*/

    arr[i].key = key;

    while(i != 0 && arr[(i-1)/2].key > arr[i].key){
        /*position[arr[i].vertex] = (i-1)/2;
        position[arr[(i-1)/2].vertex] = i; */
        swap_nodes(heap_struct, i, (i-1)/2);
        //swap(heap_struct->heap[i], heap_struct->heap[(i-1)/2]);

        i = (i-1)/2;
    }
}

bool in_heap(heap_struct* heap_struct, int v){
    if(heap_struct->pos[v] <= heap_struct->size)
        return true;
    return false;
}

Graph* build(int v){
    Graph* graph = new Graph;
    graph->v = v;
    graph->array = (adjList*)malloc(v*sizeof(adjList));
    adjList* list = graph->array;
    for(int i = 0; i < v; i++)
        list[i].head = NULL;
    return graph;
}

void insert_edge(int u, int v, int w, Graph* graph){
    adjListNode* newNode = new adjListNode;
    newNode->v = v;
    newNode->w = w;
    newNode->next = (graph->array)[u].head;
    (graph->array)[u].head = newNode;

    adjListNode* newNode2 = new adjListNode;
    newNode2->v = u;
    newNode2->w = w;
    newNode2->next = (graph->array)[v].head;
    (graph->array)[v].head = newNode2;
}

void print_graph(Graph* graph){
    int n = graph->v;
    adjList* array = graph->array;

    adjListNode* temp;
    for(int i = 0; i < n; i++){
        temp = array[i].head;
        /*cout << i << " ";*/
        while(temp != NULL){
            /*cout << temp->v << " ";*/
            temp = temp->next;
        }
        /*cout << endl;*/
    }
}

/*void prim(Graph* graph){
    int n = graph->v;
    heap_struct* heap_struct = new struct heap_struct;
    heap_struct->pos = new int[n];
    heap_struct->heap = new struct heap_node[n];
    heap_struct->size = n;

    int parent[n];
    int black[n];
    int key[n];

    for(int i = 0; i < n; i++){
        heap_struct->heap[i].vertex = i;
        heap_struct->heap[i].key = INT_MAX;
        black[i] = false;
        key[i] = INT_MAX;
    }

    heap_struct->heap[0].key = 0;
    black[0] = true;

    key[0] = 0;
    adjListNode* track = NULL;

    heap_node* extracted_min;
    while(heap_struct->size > 0){
        extracted_min = extract_min(heap_struct);
        black[extracted_min->vertex] = 0;

        track = graph->array[extracted_min->vertex].head;

        while(track != NULL){
            if(!black[track->v]){
                if(key[track->v] > track->w){
                    black[track->v] = true;
                    parent[track->v] = extracted_min->vertex;
                    key[track->v] = track->w;
                    decrease_key(heap_struct, track->v, track->w);
                }
            }
            track = track->next;
        }

        
    }
    for(int i = 1; i < n; i++)
        cout << parent[i] << " - " << i << endl;

}
*/

void prim(Graph* graph,int source,int destination){
    int n = graph->v;
    heap_struct* heap_struct = (struct heap_struct*)malloc(sizeof(struct heap_struct));
    heap_struct->pos = (int*)malloc(n*sizeof(int));
    heap_struct->size = heap_struct->count = n;

    heap_struct->heap = new heap_node[n];

    int parent[n];
    int key[n],key1[n],key2[n],key3[n];
    bool is_present[n];

    for(int i = 1; i < n; i++){
        parent[i] = -1;
        key[i] = INT_MAX;
        key1[i]= INT_MAX;
        key2[i]= INT_MAX;
        key3[i]= INT_MAX;
        heap_struct->heap[i].vertex = i;
        heap_struct->heap[i].key = INT_MAX;
        heap_struct->pos[i] = i;
    }
    key[0] = 0;
    
    
    heap_struct->heap[0].vertex = 0;
    heap_struct->heap[0].key = 0;
    heap_struct->pos[0] = 0;

    /*cout << "Printing the contents of the heap" << endl;
    for(int i = 0; i < heap_struct->size; i++){
        cout << heap_struct->heap[i].vertex << " ";
        cout << heap_struct->heap[i].key << endl;
    }*/

    heap_node* min_node , *min_node1;
    adjListNode* track,*track1,*track2;    

    int count_1 = 0, m = 0;
    while(heap_struct->size > 0){
        /*cout << "Printing the contents of the heap" << endl;
        for(int i = 0; i < n; i++){
            cout << heap_struct->heap[i].vertex << " ";
            cout << heap_struct->heap[i].key << endl;
        }*/

        min_node = extract_min(heap_struct);
        int u = min_node->vertex;
        int u11=n-1;
        int u12=source;
        int u13=destination;
        /*cout << "The extracted min is the vertex " << u << endl;*/

        track = graph->array[u].head;
        track1=graph->array[u11].head;
        track2=graph->array[u12].head;
        
		 
        while(track != NULL){
            int v = track->v;
            if(in_heap(heap_struct, v) && track->w +key[u]< key[v]){
                /*cout << "Lesser found and updating" << endl;*/
                key[v] = track->w + key[u];
                parent[v] = u;
                decrease_key(heap_struct, v, key[v]);
            }


            track = track->next;
        }
        /* Question part */
        int short_path[n];int short_path1[n];
        
        while(track1 != NULL ){
        	int v,v2,ix=0;
            v = track1->v;
            if(in_heap(heap_struct, v) && track1->w+key[v]==key[n-1])
			{
                short_path[ix]=v;
                ix++;
            }


            track1 = track1->next;
        }
        
        while(track2!= NULL ){
        	int v,v2,ix=0,ix1=0;
            v = track2->v;
            if(in_heap(heap_struct, v) && track2->w+key[v]==key[n-1])
			{
                
                for(ix1=0;ix1<n;ix1++)
                {
                	if(v==short_path[ix])
                	{
                		if(key[v]>key[n-1]-key[v])
                		{
                			short_path1[ix]=v;
						}
					}
					else
					{
						short_path1[ix]=v;
					}
                	
				}
                ix++;
            }


            track2 = track2->next;
        }
         
    }
    /*for(int i = 0; i < n; i++)
        cout << i << " is at a distance of " << key[i] << " from 0." << endl;*/
    cout << key[destination]+key[source];    
       
}


int main()
{
    int t,n,m,j1,j2,s,t1,x1,y1,d1;
    cin >> t;
    for(j1=0;j1<t;j1++)
    {
    	cin >> n;
        cin >> m;
        Graph* graph = build(n);
        cin >> s;
        cin >> t1;
        for(j2=0;j2<m;j2++)
        {
        	cin >> x1;
        	cin >> y1;
        	cin >> d1;
        	insert_edge(x1,y1,d1,graph);
		}
		prim(graph,s,t1);
	}
    
    
    

    /*insert_edge(0, 1, 4, graph);
    insert_edge(0, 7, 8, graph);
    insert_edge(1, 2, 8, graph);
    insert_edge(1, 7, 11, graph);
    insert_edge(2, 3, 7, graph);
    insert_edge(2, 8, 2, graph);
    insert_edge(2, 5, 4, graph);
    insert_edge(3, 4, 9, graph);
    insert_edge(3, 5, 14, graph);
    insert_edge(4, 5, 10, graph);
    insert_edge(5, 6, 2, graph);
    insert_edge(6, 7, 1, graph);
    insert_edge(6, 8, 6, graph);
    insert_edge(7, 8, 7, graph);*/
    /*prim(graph,s,t1);*/
    
}


