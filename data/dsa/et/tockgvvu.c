#include<stdio.h>
#include<stdlib.h>
struct AdjListNode{
    int dest;
    struct AdjListNode* next;
};
struct AdjList{
    struct AdjListNode *head;
};
struct Graph{
    int V;
    struct AdjList* array;
};
struct node {
  int info;
  struct node *next;
}struct node stack[2];
struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}
struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}
void addEdge(struct Graph* graph, int src, int dest){
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
void printGraph(struct Graph* graph){
    int v;
    for (v = 0; v < graph->V; ++v){
        struct AdjListNode* print = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (print){
            printf("-> %d", print->dest);
            print = print->next;
        }
        printf("\n");
    }
}
struct node {
  int info;
  struct node *next;
}
void push(int x){
  struct node *temp=malloc(sizeof(struct node));
  temp->info = x;
  temp->next =head;
  head =temp;
}
int pop(){
  struct node *temp;
  int item;
  if(head ==NULL){
    printf("\nEmpty\n");
  }
  else{
    while(head!=NULL){
    temp = head;
    head = temp->next;
  }
  free(temp);
}
struct node  stack[1] *head1;
struct node stack[2] * head2;
 int main(){
  head =NULL;
  int V = 5;
  struct Graph* graph = createGraph(V);
  addEdge(graph, 5,8);
  addEdge(graph, 5, 4);
  addEdge(graph, 4, 2);
  addEdge(graph, 4, 6);
  return 0;

}
