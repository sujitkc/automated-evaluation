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
struct queue{
  struct node *node;
  struct queue *next;
};
struct stack{
  struct node *node;
  struct stack *next;
};
struct ll{
  struct node *node;
  struct ll *next;
};
void add_edge(struct node *arr[],int start,int end,int weight);
void shortest_path(struct node *arr[],int n);
void shortest_path_top(struct ll *l,int n);
void prim(struct node *arr[],int n);
void bfs(struct node *node[],int n);
void dfs(struct node *node[],int n);
struct ll *rec_dfs(struct node *node[],int start,int n);
void dfs_visit(struct node *node[],struct node *u,struct ll **ll);
void do_transpose(struct node *G[],struct node *GT[],int n);
// SSC- Strongly Connected Components
int find_index(struct node *arr[],int data);
void ssc(struct node *node[],int n);
void enque(struct queue **head,struct queue **tail,struct node *node);
struct node *deque(struct queue **head,struct queue **tail);
void push(struct stack **head,struct node *root);
struct node *pop(struct stack **head);
void swap(struct node **a,struct node **b,int l1,int l2);
void btmup(struct node *arr[],int i);
void topdown(struct node *arr[],int i,int len);
void insert(struct node *arr[],int *len,struct node *ptr);
void decrease(struct node *arr[],int i,int x);
struct node *delete_min(struct node *arr[],int *len);
/*
red=0
yellow=1
blue=2
*/
int t;
int main(){

  struct node *node[100];
  for(t=0;t<100;t++){
    node[t]=malloc(sizeof(struct node));
    node[t]->next=NULL;
    node[t]->data=t;
  }
  add_edge(node,0,1,3);
  add_edge(node,0,2,4);
  add_edge(node,2,1,-2);
  ssc(node,3);
}
void shortest_path_top(struct ll *l,int n){
  int i;
  struct node *u;
  struct adj_node *v;
  struct ll *l1=l;
  for(;l!=NULL;l=l->next) l->node->priority=1000;
  if(l1!=NULL)l1->node->priority=0;
  while(l1!=NULL){
    u=l1->node;
    v=u->next;
    while(v!=NULL){
      if(v->root->priority>u->priority+v->cost){
        v->root->priority=u->priority+v->cost;
        v->root->pie=u;
      }
      v=v->next;
    }
    l1=l1->next;
  }
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
void shortest_path(struct node *arr[],int n){
  struct node *hp[n],*u;
  int hl=0;
  for(int i=0;i<n;i++) arr[i]->colour=0;
  insert(hp,&hl,arr[0]);
  arr[0]->priority=0;
  arr[0]->colour=1;
  while(hl!=0){
    u=delete_min(hp,&hl);
    u->colour=2;
    struct adj_node *v;
    v=u->next;
    while(v!=NULL){
      if(v->root->colour==0){
        v->root->priority=u->priority+v->cost;
        v->root->colour=1;
        insert(hp,&hl,v->root);
        v->root->pie=u;
      }
      else if(v->root->colour==1){
        if(v->root->priority>u->priority+v->cost){
        //  v->root->priority=u->priority+v->cost;
          decrease(hp,v->root->heap,u->priority+v->cost);
          v->root->pie=u;
        }
      }
      v=v->next;
    }
  }

}
void bfs(struct node *node[],int n){
  struct queue *head=NULL,*tail=NULL;
  struct node *u;
  struct adj_node *v;
  for(int i=0;i<n;i++) node[i]->colour=0;
  u=node[0];
  enque(&head,&tail,u);
  u->colour=1;
  while(head!=NULL){
    u=deque(&head,&tail);
    u->colour=2;
    v=u->next;
    while(v!=NULL){
      if(v->root->colour==0){
        v->root->colour=1;
        enque(&head,&tail,v->root);
        v->root->pie=u;
      }
      v=v->next;
    }
  }

}
void dfs(struct node *node[],int n){
  struct stack *head=NULL;
  struct node *u; struct adj_node *cur;
  for(int i=0;i<n;i++) node[i]->colour=0;
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
        cur=cur->next;
      }
    }
  }
}
struct ll *rec_dfs(struct node *node[],int start,int n){
  for(int i=0;i<n;i++) node[i]->colour=0;
  struct ll *l=NULL;
  node[start]->pie=node[start];
  t=0;
  dfs_visit(node,node[start],&l);
  return l;
}
void dfs_visit(struct node *node[],struct node *u,struct ll **l){
  u->colour=1;
  u->d=t++;
  struct adj_node *v=u->next;
  while(v!=NULL){
    if(v->root->colour==0){
      v->root->pie=u;
      dfs_visit(node,v->root,l);
    }
    v=v->next;
  }
  struct ll *ll1=malloc(sizeof(struct ll));
  ll1->node=u;
  ll1->next=(*l);
  (*l)=ll1;
  u->colour=2;
  u->f=t++;
}
void do_transpose(struct node *G[],struct node *GT[],int n){
  struct node *u;
  struct adj_node *v;
  for(int i=0;i<n;i++){
    GT[i]=malloc(sizeof(struct node));
    GT[i]->data=G[i]->data;
    GT[i]->next=NULL;
  }
  for(int i=0;i<n;i++){
    u=G[i];
    v=u->next;
    while(v!=NULL){
      add_edge(GT,find_index(G,v->data),find_index(G,u->data),v->cost);
      v=v->next;
    }
  }
}
int find_index(struct node *arr[],int data){
  int i=0;
  while(1){
    if(arr[i]->data==data) return i;
    i++;
  }
}
void ssc(struct node *node[],int n){
  struct node *T[n];
  struct ll *ll=rec_dfs(node,0,n);
  do_transpose(node,T,n);
  for(int i=0;i<n;i++) node[i]->colour=0;
  struct ll *l[n]; int k=0;
  for(int i=0;i<n;i++){
    if(node[i]->colour==0) l[k++]=rec_dfs(node,i,n);
  }
}

void enque(struct queue **head,struct queue **tail,struct node *node){
  struct queue *newptr;
  newptr=malloc(sizeof(struct queue ));
  newptr->next=NULL;
  newptr->node=node;
  if((*head)!=NULL){
    (*tail)->next=newptr;
    (*tail)=(*tail)->next;
  }
  else{
    *head=newptr;
    *tail=newptr;
  }
}
struct node *deque(struct queue **head,struct queue **tail){
  struct node *temp;
  if((*head)!=NULL){
    if(head==tail){
      temp=(*head)->node;
      *head=NULL;
      *tail=NULL;
    }
    else{
      temp=(*head)->node;
      *head=(*head)->next;
    }
    printf("%d\n",temp->data);
    return temp;
  }
  else return NULL;
}
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
    printf("%d\n",temp->node->data);
     return temp->node;
   }
  else return NULL;
}
void btmup(struct node *arr[],int i){
  int p=(i-1)/2;
  while(i>0){
    if(arr[i]->priority<arr[p]->priority){
      swap(&arr[i],&arr[p],i,p);
      i=p;
      p=(i-1)/2;
    }
    else break;
  }
}
void topdown(struct node *arr[],int i,int len){
  int r=2*i+2,l=2*i+1,j;
  if(l==(len-1)&&arr[i]->priority>arr[l]->priority){
    swap(&arr[i],&arr[l],i,l);
  }
  else{
    while(r<len){
      //j=mini(arr,r,l);
      if(arr[l]->priority>arr[r]->priority) j=r;
      else j=l;

      if(arr[i]->priority<arr[j]->priority) break;
      else{
        swap(&arr[i],&arr[j],i,j);
        i=j;
        r=2*i+2;
        l=2*i+1;
      }
    }
  }
}
void insert(struct node *arr[],int *len,struct node *ptr){
  arr[*len]=malloc(sizeof(struct node));
  arr[*len]=ptr;
  arr[*len]->heap=(*len);
  btmup(arr,*len);
  *len=*len+1;
}
void decrease(struct node *arr[],int i,int x){
  arr[i]->priority=x;
  btmup(arr,i);
}
struct node *delete_min(struct node *arr[],int *len){
  struct node *temp=arr[0];
  arr[0]=arr[*len-1];
  arr[0]->heap=0;
  topdown(arr,0,*len-1);
  //free(arr[*len]);
  *len=*len-1;
  return temp;
}
void swap(struct node **a,struct node **b,int l1,int l2){
  struct node *temp=*a;
  *a=*b;
  *b=temp;
  (*b)->heap=l1;
  (*a)->heap=l2;
}
