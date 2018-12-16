#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
long int dest;
long int weight;
struct node *nextptr;
};

struct heapnode{
  long int vertex;
  long int key;
};

void insert(struct node **startptr,long int newdest,long int newweight);
void view(struct node *startptr);
void minHeapify(struct heapnode arr[],long int i,long int n,long int pos[]);
void swap(struct heapnode arr[],long int i,long int j,long int pos[]);
long int ExtractMin(struct heapnode arr[],long int n,long int pos[]);
void addElementToHeap(struct heapnode arr[],long int i,long int pos[]);
void decreaseKey(struct heapnode A[],long int i,long int x,long int pos[]);
void dijkstra(struct node *graph[],long int v, long int src, long int dijk[]);
void finalDijkstra(struct node *graph[], long int v, long int src, long int des, long int boolean[]);

long int main(){
  long int i;
    long int t;
    scanf("%ld",&t);
    for(i=0;i<t;i++){
      long int v,m,j;
      scanf("%ld %ld",&v,&m);
      struct node *graph[v];
      for(j=0 ; j<v ; j++){
        graph[j] = NULL;
      }
      long int s,t,x,y,d;
      scanf("%ld %ld",&s,&t);
      s--;
      t--;
      for(j=0 ; j<m ; j++){
        scanf("%ld %ld %ld",&x,&y,&d);
        x--;
        y--;
        insert(&graph[x],y,d);
        insert(&graph[y],x,d);
      }
      long int dijk1[v],dijk2[v];
      dijkstra(graph, v, 0,dijk1 );
      dijkstra(graph, v, v-1, dijk2);
      long int boolean[v];
      for(j=0 ; j<v ; j++){
        if(dijk1[j] + dijk2[j] == dijk1[v-1]){
          boolean[j] = 1;
        }
        else{
          boolean[j] = 0;
        }
      }
      printf("check\n");
      // for(j=0; j<v; j++)
      //   printf("%ld %ld %ld %ld\n",dijk1[j],dijk2[j],dijk1[v-1],boolean[j] );
      // printf("\n");
      finalDijkstra(graph,v,s,t,boolean);

    }

  return 0;
}
void insert(struct node **startptr,long int newdest,long int newweight){
  struct node *temp;
  temp=(struct node*)malloc(sizeof(struct node));
  temp->dest=newdest;
  temp->weight=newweight;
  temp->nextptr=*startptr;
  *startptr=temp;
}

void view(struct node *startptr)
{
if((startptr)==NULL)
printf("The linked list is empty");
struct node *currentptr=startptr;
while(currentptr!=NULL)
{
printf("|%ld|%ld ",currentptr->dest,currentptr->weight);//|dest|weight
currentptr=currentptr->nextptr;
}
printf("\n");
}

void dijkstra(struct node *graph[],long int v, long int src, long int dijk[]){
  long int parent[v],i,heapsize=v,pos[v];
  for(i=0;i<v;i++){
    parent[i]=-1;
    pos[i]=i;
  }
  struct heapnode* heap = (struct heapnode*)malloc(v*sizeof(struct heapnode));
  heap[0].vertex=0;
  heap[0].key=0;
  for(i=1;i<v;i++){
    heap[i].vertex=i;
    heap[i].key=INT_MAX;
  }
  swap(heap, 0, src, pos);
  // printf("heap %ld %ld \n",heap[0].vertex,heap[0].key );
  heap[pos[0]].key = INT_MAX;
  heap[pos[src]].key = 0;
  while(heapsize>0){
    long int extractver = heap[0].vertex;
    heapsize = ExtractMin(heap,heapsize,pos);
    struct node *currentptr = graph[extractver];
    while(currentptr != NULL){
      if(pos[currentptr -> dest] < heapsize){
        if(currentptr->weight + heap[pos[extractver]].key < heap[pos[currentptr->dest]].key){
          decreaseKey(heap, pos[currentptr->dest], currentptr->weight + heap[pos[extractver]].key , pos);
          parent[currentptr->dest]=extractver;
        }
        
      }
      currentptr = currentptr->nextptr;
    }
  }
  for(i=0;i<v;i++){
    dijk[i] = heap[pos[i]].key;
  }
  free(heap);
}
void minHeapify(struct heapnode arr[],long int i,long int n,long int pos[]){
  long int l = 2*i+1;
  long int r = 2*i+2,j;
  while(r < n){
    if(arr[l].key < arr[r].key){
      j = l;
    }
    else{
      j = r;
    }
    if(arr[i].key < arr[j].key)
    break;
    else{
      swap(arr,i,j,pos);
      i = j;
      l = 2*i+1;
      r = 2*i+2;
    }
  }
  if(l == n-1){
    if(arr[i].key > arr[l].key){
      swap(arr, i, l, pos);
    }
  }
}
void swap(struct heapnode arr[],long int i,long int j,long int pos[]){
  pos[arr[i].vertex] = j;
  pos[arr[j].vertex] = i;
  long int tempvertex,tempkey;
  tempvertex = arr[i].vertex;
  tempkey = arr[i].key;
  arr[i].vertex = arr[j].vertex;
  arr[i].key = arr[j].key;
  arr[j].vertex = tempvertex;
  arr[j].key = tempkey;
}

long int ExtractMin(struct heapnode arr[],long int n,long int pos[]){
  swap(arr,0,n-1,pos);
  n--;
  minHeapify(arr,0,n,pos);
  return n;
}

void addElementToHeap(struct heapnode arr[],long int i,long int pos[]){
  long int p = (i-1)/2;
  while(i > 0){
    if(arr[p].key > arr[i].key){
      swap(arr, p, i, pos);
      i = p;
      p = (i-1)/2;
    }
    else
      return;
  }
}

void decreaseKey(struct heapnode A[],long int i,long int x,long int pos[]){
  if(A[i].key < x){
    printf("Use 'increaseKey' function\n");
    return;
  }
  A[i].key = x;
  addElementToHeap(A, i, pos);
}
void finalDijkstra(struct node *graph[], long int v, long int src, long int des, long int boolean[]){
  long int parent[v],i,heapsize=v,pos[v];
  for(i=0;i<v;i++){
    parent[i]=-1;
    pos[i]=i;
  }
  struct heapnode* heap = (struct heapnode*)malloc(v*sizeof(struct heapnode));
  heap[0].vertex=0;
  heap[0].key=0;
  for(i=1;i<v;i++){
    heap[i].vertex=i;
    heap[i].key=INT_MAX;
  }
  swap(heap, 0, src, pos);
  heap[pos[0]].key = INT_MAX;
  heap[pos[src]].key = 0;
  while(heapsize>0){
    long int extractver = heap[0].vertex;
    heapsize = ExtractMin(heap,heapsize,pos);
    struct node *currentptr = graph[extractver];
    while(currentptr != NULL){
      if(pos[currentptr -> dest] < heapsize && (boolean[currentptr->dest] == 0)){
        if(currentptr->weight + heap[pos[extractver]].key < heap[pos[currentptr->dest]].key){
          decreaseKey(heap, pos[currentptr->dest], currentptr->weight + heap[pos[extractver]].key , pos);
          parent[currentptr->dest] = extractver;
        }
        
      }
      currentptr = currentptr->nextptr;
    }
  }
  if(heap[pos[des]].key == INT_MAX)
    printf("NOT POSSIBLE\n");
  else
    printf("%ld\n",heap[pos[des]].key );

}