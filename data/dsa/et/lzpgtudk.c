#include <stdio.h>
#include<stdlib.h>

void dfs(int v, int reach[], int *tab[], int vert)
{
    int i;
    reach[v]=1;
    for(i=0;i<vert;i++)
    {
        if(tab[v][i]&&!reach[i])
        {
            dfs(i, reach, tab, vert);
        }
    }
}

int main()
{
    
    int vert,edge, i, j, e1, e2, count;
   // enter (nodes:)
    scanf("%d",&vert);
  //  (no of edges:)
    scanf("%d",&edge);

    int *reach;
    int **tab;
    reach=(int*)malloc((vert+1)*sizeof(int));
    tab=(int**)malloc((vert+1)*sizeof(int *)); 
    for( i=0; i<vert; i++)
    {
        tab[i]=(int*)malloc((vert+1)*sizeof(int));
       // printf("ok\n");
    }
    for(i=0;i<vert;i++)
    {
        reach[i]=0;
        for(j=0;j<vert;j++)
        {
            tab[i][j]=0;
        }
    }



   for(i=0;i<edge;i++)
{
    scanf("%d", &e1);
    scanf("%d", &e2);
    if (tab[e1-1][e2-1]==1) {
       printf("duplicated edge between %d and %d",e1, e2);
       exit(-1);
    } else tab[e1-1][e2-1]=1;
    
   // printf("ok %d\n", tab[e1-1][e2-1]);
}

    for(i=0;i<vert;i++)
    {
        for(j=0;j<vert;j++)
        {
           // printf("%d\n",tab[i][j]);
        }
    }

    dfs(1, reach, tab, vert);
   // printf("\n");

    for(i=0;i<vert;i++)
    {
        if(reach[i])
            count++;
        printf("count: %d", count);
    }
    if(count==vert)
        printf("graph have cycle");
    else
        printf("graph doesn't have cycle");
return 0;

}

