#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void input{
  int testcases,nodes,edges;
  scanf("%d"&testcases);
  scanf("%d"&nodes);  
  scanf("%d"&edges);
};  
  
struct node{
  int data,priority,d,f;
  struct node *pie;
  struct adj_node *next;
};

struct adj_node{
  int data;
  struct node *root;
  struct adj_node *next;
};  

struct queue{
  struct node *node;
  struct queue *next;
};

struct stack{
  struct node *node;
  struct stack *next;
};


void add_edge(struct node *arr[],int start,int end,int weight);
void dfs(struct node *node[],int n);
struct ll *rec_dfs(struct node *node[],int start,int n);
void dfs_visit(struct node *node[],struct node *u,struct ll **ll);

void add_edge(struct node *arr[],int start,int end,int weight){
  






if (node[n]!=node[0]){
  void dfs;
  

else{
    


