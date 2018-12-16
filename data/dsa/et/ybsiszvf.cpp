#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>

using namespace std;

struct adjListNode{
    int v;
    int w;
    int weight;
    adjListNode* next;
};

struct adjList{
    adjListNode* head;
};

struct Graph{
    int v;
    adjList* array;
};

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
        cout << i << " ";
        while(temp != NULL){
            cout << temp->v << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

struct glo{
    int max;
    int u;
};

struct minglo{
    int min;
    int u;
};


void test(Graph* graph, int* weights){

    int n = graph->v;
    adjList* array = graph->array;
    adjListNode* head, *temp;
    
    int max = INT_MIN, min = INT_MAX;
    glo* glomax = new glo;


    for(int i = 0; i < n; i++){
        head = array[i].head;
        temp = head;
        max = INT_MIN;
        min = INT_MAX;
        while(temp != NULL){
            if(weights[temp->v] > max)
                max = weights[temp->v];
            if(max > glomax->max){
                glomax->max = max;
                glomax->u = i;
            }
            if(max == glomax->max){
                if(weights[i] > weights[glomax->u])
                    glomax->u = i;
            }
            temp = temp->next;
        }
        
    }
    temp = array[glomax->u].head;

    int othernode;

    while(temp != NULL){
        if(weights[temp->v] < min){
            min = weights[temp->v];
            othernode = temp->v;
        }
        temp = temp->next;
    }

    cout << glomax->u + 1 << " " << othernode + 1<< endl;
}

int main(){
    int v;

    int t;
    cin >> t;
    for(int j = 0; j < t; j++){

        cin >> v;

        Graph* graph = build(v);

        int weights[v];

        for(int i = 0; i < v; i++){
            cin >> weights[i];
        }

        int u, w;

        for(int i = 0; i < v-1; i++){
            cin >> u;
            cin >> w;
            insert_edge(u-1, w-1, 3, graph);
        }
        /*insert_edge(0, 4, 3, graph);
        insert_edge(1, 2, 5, graph);
        insert_edge(3, 4, 0, graph);
        insert_edge(2, 4, 1, graph);
        insert_edge(0, 1, 7, graph);*/

        //print_graph(graph);
        test(graph, weights);

        //print_graph(graph);
        cout << endl;
    }
}
/*
0  1  4
1  2
2  4
3  4
4
*/