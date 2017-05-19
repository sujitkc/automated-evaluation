#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
  int data;
  int Weight;
  struct node *pie;
  struct adj_node *next;
};
struct adj_node{
  int data,cost;
  struct node *root;
  struct adj_node *next;
};


void add_edge(struct node *arr[],int start,int end,int weight);
int find_index(struct node *arr[],int data);
void compute_sumofweights(struct node *arr[]);


int t,n;




int main(){
int val;

int pn,cn;
  struct node *node[100];

printf("No of elements");
scanf("%d",&n);


  for(t=1;t<n+1;t++)
  {

    printf("Enter the value: ");
    scanf("%d",&val);
    node[t]=malloc(sizeof(struct node));
    node[t]->next=NULL;
    node[t]->data=val;
  }
  

for(t=1;t<n;t++)
  {
    printf("Enter (Parent node,Child node)");
    scanf("%d",pn);
    scanf("%d",cn);
    add_edge(node,pn,cn,0);
  }

compute_sumofweights(node[0]);



}



void add_edge(struct node *arr[],int start,int end,int weight)
{
  struct adj_node *adj=malloc(sizeof(struct adj_node)),*cur;
  adj->data=arr[end]->data;
  adj->cost=weight;
  adj->root=arr[end]; adj->next=NULL;
  cur=arr[start]->next;
  adj->next=arr[start]->next;
  arr[start]->next=adj;
}

int find_index(struct node *arr[],int data){
  int i=0;
  while(1){
    if(arr[i]->data==data) return i;
    i++;
  }
}


void compute_sumofweights(struct *node);
{
  node->Weight=(node->data+compute_sumofweights(node->leftchild)+compute_sumofweights(node->rightchild));
}
