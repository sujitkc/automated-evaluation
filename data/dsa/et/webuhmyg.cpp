#include<stdio.h>
 
void DFS(int);
int G[10][10],v[10],n;    //n is no of vertices and graph is sorted in array G[10][10]
 
int main()
{
    int i,j;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    printf("\nEnter adjecency matrix of the graph:");
    for(i=0;i<n;i++)
       for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
 
   for(i=0;i<n;i++)
        v[i]=0;
 
    DFS(0);
}
 
void DFS(int i)
{
    int j;
    printf("\n%d",i);
    v[i]=1;
    
    for(j=0;j<n;j++)
       if(!v[j]&&G[i][j]==1)
            DFS(j);
}
