#include <stdio.h>
#include <stdlib.h>

void dfs(int v, int adj[], int *visited[], int node)
{
    int i;
    adj[v]=1;
    for(i=0;i<node;i++)
    {
        if(visited[v][i]&&!adj[i])
        {
            dfs(i, adj, visited, node);
        }
    }
}

int main()
{
    int node,edge, i, j, e1, e2, count;
   printf("number of nodes: ");
    scanf("%d",&node);
   printf("number of connections: ");
    scanf("%d",&edge);

    int *adj;
    int **visited;
    adj=(int*)malloc((node+1)*sizeof(int));
    visited=(int**)malloc((node+1)*sizeof(int *));
    for( i=0; i<node; i++)
    {
        visited[i]=(int*)malloc((node+1)*sizeof(int));
    }
    for(i=0;i<node;i++)
    {
        adj[i]=0;
        for(j=0;j<node;j++)
        {
            visited[i][j]=0;
        }
    }



    for(i=0;i<edge;i++)
    {
        scanf("%d", &e1);
        scanf("%d", &e2);
        visited[e1-1][e2-1]=1;
    }
  

    dfs(1, adj, visited, node);

    for(i=0;i<node;i++)
    {
        if(adj[i])
            count++;
    }
    if(count==node)
        printf("graph have cycle");
    else
        printf("graph doesn't have cycle");
return 0;

}
