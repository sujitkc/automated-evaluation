#include<stdio.h>
#include<stdlib.h>

struct edge{
	int weight;
};
typedef struct edge Edge;
struct node{
	int weight;
	struct node* parent;
	struct node* nextl;
	struct node* nextr;
	Edge* weightedgel;
	Edge* weightedger;
};
typedef struct node Node;
Node *current;
void putlength(Node* start,int p){
	if(p=0){
		if(start->nextl->nextl==NULL){
			start->weightedgel->weight=current->nextl->weight;
			start=start->parent;
		}
		if(start->weightedger==NULL){
			putlength(start,1);
		}
		if(start->weightedgel==NULL){
			start=start->nextl;
			putlength(start,0);
		}
		if(start->weightedgel!=NULL && start->weightedger!=NULL){
			start=start->parent;
		}
	}
}
void main(){
	Node *head=(Node *)malloc(sizeof(Node));
	current=head;
	while(current1->nextl!=NULL){
		if(current->weightedgel!=NULL){
			current=current->nextl;
		}
	}
}
