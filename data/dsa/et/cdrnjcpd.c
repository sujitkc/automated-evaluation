#include <stdio.h>
#include <stdlib.h>

void dfs(int v, int r[], int *t[], int vert)
{
    int i;
    r[v]=1;
    for(i=0;i<vert;i++)
    {
        if(t[v][i]&&!r[i])
        {
            dfs(i, r, t, vert);
        }
    }
}

int main()
{
    
    int vert,edge, i, j, e1, e2, count;
    printf("number of verticles: ");
    scanf("%d",&vert);
    printf("number of connections: ");
    scanf("%d",&edge);

    int *r;
    int **t;
    r=(int*)malloc((vert+1)*sizeof(int));
    t=(int**)malloc((vert+1)*sizeof(int *)); 
    for( i=0; i<vert; i++)
    {
        t[i]=(int*)malloc((vert+1)*sizeof(int));
         //printf("ok\n");
    }
    for(i=0;i<vert;i++)
    {
        r[i]=0;
        for(j=0;j<vert;j++)
        {
            t[i][j]=0;
        }
    }

    



    for(i=0;i<edge;i++)
   {
    scanf("%d", &e1);
    scanf("%d", &e2);
    if (t[e1-1][e2-1]==1) {
       printf("duplicated edge between %d and %d",e1, e2);
       exit(-1);
    } else t[e1-1][e2-1]=1;
       printf("ok %d\n", t[e1-1][e2-1]);
   }



    /*for(i=0;i<edge;i++)
    {
        scanf("%d", &e1);
        scanf("%d", &e2);
        t[e1-1][e2-1]=1;
        //printf("ok %d\n", t[e1-1][e2-1]);
    }*/
    

    for(i=0;i<vert;i++)
    {
        for(j=0;j<vert;j++)
        {
           //printf("%d\n",t[i][j]);
        }
    }

    dfs(1, r, t, vert);
    printf("\n");

    for(i=0;i<vert;i++)
    {
        if(r[i])
            count++;
        printf("count: %d ", count);
        printf("\n");
    }
    if(count==vert)
        printf("graph have cycle");
    else
        printf("---DAG---   ");
return 0;

}