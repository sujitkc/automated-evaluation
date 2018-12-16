#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
  int data,colour,priority,heap,d,f;
  struct node *pie;
  struct adj_node *next;
};
struct adj_node{
  int data,cost;
  struct node *root;
  struct adj_node *next;
};
struct stack{
  struct node *node;
  struct stack *next;
};
struct q{
    int data;
    struct node *next;
};
void add_edge(struct node *arr[],int start,int end,int weight);
void dfs(struct node *node[],int n,int start,int arr[]);
void enque(struct queue **head,struct queue **tail,struct node *node);
struct node *deque(struct queue **head,struct queue **tail);
void push(struct stack **head,struct node *root);
struct node *pop(struct stack **head,int arr1[]);
void check_cycle(int arr[],int l);


void print(int arr[],int i){
	int k;
	for(k=0;k<i;k++){
	printf("%d\n",arr[k]);
}
}
void add_uedge(struct node *arr[],int start,int end,int weight){
	add_edge(arr,start,end,weight);
	add_edge(arr,end,start,weight);
}

int t;
int main(){

  struct node *node[100];
  int arr1[100];
  arr1[1]=3;
  for(t=0;t<100;t++){
    node[t]=malloc(sizeof(struct node));
    node[t]->next=NULL;
    node[t]->data=t;
  }
  add_edge(node,0,1,3);
  add_edge(node,1,2,4);
  add_edge(node,1,3,-2);
  add_edge(node,2,3,-8);
  add_edge(node,3,4,-8);
  //add_edge(node,3,4,-8);
  //add_edge(node,4,5,-8);
  //print(arr1,10);
 // puts("hi");
  dfs(node,10,0,arr1);
  //print(arr1,10);
  //check_cycle(arr,4);
}
void add_edge(struct node *arr[],int start,int end,int weight){
  struct adj_node *adj=malloc(sizeof(struct adj_node)),*cur;
  adj->data=arr[end]->data;
  adj->cost=weight;
  adj->root=arr[end]; adj->next=NULL;
  cur=arr[start]->next;
  adj->next=arr[start]->next;
  arr[start]->next=adj;
}

void dfs(struct node *node[],int n,int start,int arr1[]){
  struct stack *head=NULL;
  struct node *u; struct adj_node *cur;
  int i;
  for(i=0;i<n;i++) node[i]->colour=0;
  push(&head,node[start]);
  node[0]->colour=1;
  while(head!=NULL){
    u=pop(&head,arr1);
    //print(arr1,10);
    if(u->colour==1){
      u->colour=2;
      cur=u->next;
      while(cur!=NULL){
        if(cur->root->colour==0){
            cur->root->pie=u;
            push(&head,cur->root);
            cur->root->colour=1;
        }
        else if(cur->root->colour==1){
          push(&head,cur->root);
          cur->root->pie=u;
        }
        cur=cur->next;
      }
    }
  }
}
void check_cycle(int arr[],int l){
	int i=0;
	for(i=0;i<l;i++){
		if(arr[i]==arr[l-1]){
		//	print(arr,i);
		//printf("%d\n",i);
		}
	}
}
void push(struct stack **head,struct node *node){
  struct stack *new;
  new=malloc(sizeof(struct stack));
  new->node =node;
  new->next=*head;
  *head=new;
}
struct node *pop(struct stack **head,int arr1[]){
  struct stack *temp=*head;
  int i=0;
  if(temp!=NULL){
    *head=(*head)->next;
    arr1[i]=temp->node->data;
    printf("%d\n",arr1[i]);
    i++;
     return temp->node;
   }
  else return NULL;
}
