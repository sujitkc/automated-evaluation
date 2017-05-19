

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

void add_edge(struct node *arr[],int start,int end,int weight);
void dfs(struct node *node[],int n);
void push(struct stack **head,struct node *node);
void printcycle( struct node *u; struct node *a;);
struct node *pop(struct stack **head);

int t;
struct node *a;struct node *u;
int main(){

  struct node *node[100];
  for(t=0;t<100;t++){
    node[t]=malloc(sizeof(struct node));
    node[t]->next=NULL;
    node[t]->data=t;
  }
  add_edge(node,0,1,3);
  add_edge(node,0,2,4);
  add_edge(node,1,2,-2);
  dfs(node,3);
  
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

void dfs(struct node *node[],int n){
  struct stack *head=NULL;
  struct adj_node *cur;
  int i,cycle=0;
  
  for(i=0;i<n;i++) node[i]->colour=0;
  push(&head,node[0]);
  node[0]->colour=1;
  while(head!=NULL){
    u=pop(&head);
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
        else if(cur->root->colour==2 && cur!=u->pie){
        	cycle++;
			a=u;
			break;
			}
        
        cur=cur->next;
      }
    }
  }
  printf("%d",cycle); 
  printcycle(u,a);

}
void printcycle(struct node *a;){

  while(u->pie->data!=a->data){
  	  u=a;
  	  printf("%d\n",u->pie->data);
  	  u=u->pie;

}}
void push(struct stack **head,struct node *node){
  struct stack *new;
  new=malloc(sizeof(struct stack));
  new->node =node;
  new->next=*head;
  *head=new;
}
struct node *pop(struct stack **head){
  struct stack *temp=*head;
  if(temp!=NULL){
    *head=(*head)->next;
  //  printf("%d\n",temp->node->data);
     return temp->node;
   }
  else return NULL;
}
