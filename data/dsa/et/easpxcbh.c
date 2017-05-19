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
void add_edge(struct node *arr[],int start,int end,int weight);
void shortest_path(struct node *arr[],int n,int start);
void btmup(struct node *arr[],int i);
void topdown(struct node *arr[],int i,int len);
void insert(struct node *arr[],int *len,struct node *ptr);
void decrease(struct node *arr[],int i,int x);
struct node *delete_min(struct node *arr[],int *len);
void swap(struct node **a,struct node **b,int l1,int l2);

int main(){
  int t,i,j,k,n,m,a,b,w,nd,min,cur_max,cur_nd;
  scanf("%d",&t);
  for(i=0;i<t;i++){
    min=-1;
    scanf("%d %d",&n,&m);
    struct node *node[n];
    for(j=0;j<n;j++){
      node[j]=malloc(sizeof(struct node));
      node[j]->next=NULL;
      node[j]->data=j+1;
    }
    for(j=0;j<m;j++){
      scanf("%d %d %d",&a,&b,&w);
      add_edge(node,b-1,a-1,w);
    }


    for(j=0;j<n;j++){
      shortest_path(node,n,j);
      cur_max=-1;
      for(k=0;k<n;k++){
        if(node[k]->colour!=2){
          cur_max=-1;
          break;
        }
        else if(node[k]->priority>cur_max){
          cur_max=node[k]->priority;
          cur_nd=j+1;
        }
      }
      if(cur_max!=-1){
        if(min=-1){
          min=cur_max;
          nd=cur_nd;
        }
        else if(cur_max<min){
          min=cur_max;
          nd=cur_nd;
        }

      }
    }
    if(min==-1) printf("%d\n",-1);
    else printf("build at %d and max diatance is %d\n",nd,min);
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
void shortest_path(struct node *arr[],int n,int start){
  struct node *hp[n],*u;
  int hl=0;
  for(int i=0;i<n;i++) arr[i]->colour=0;
  insert(hp,&hl,arr[start]);
  arr[start]->priority=0;
  arr[start]->colour=1;
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
  //free(arr[*len-1]);
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
