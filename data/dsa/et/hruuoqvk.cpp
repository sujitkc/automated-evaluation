#include <stdio.h>
#include <stdlib.h>

struct node

{
 int value;
 struct node *l;
 struct node *r;
}*root = NULL;

 
void printout(struct node*);
struct node* newnode(int);

int main()

{
 root=newnode(5);
 root->l=newnode(4);
 root->r=newnode(8);
 root->l->l=newnode(2);
 root->l->r=newnode(6);
 

printf("tree elements are\n");
printf("\ninorder\n");
printout(root);
printf("\n");
}

 struct node* newnode(int value)
{
 struct node* node = (struct node*)malloc(sizeof(struct node));
 node->value = value;
 node->l = NULL;
 node->r = NULL;
 return(node);
}

void printout (struct node *tree)
{

    if (tree->l)
    {
	  printout(tree->l);
    }
    printf("%d->", tree->value);

    if (tree->r) 
    {
	 printout(tree->r);
    }
}
int node1,node2;
void delete_edge(int node1,int node2)
{
	if(node1==NULL || node2==NULL)
	printf("no such type of node availble");
	
	
}
