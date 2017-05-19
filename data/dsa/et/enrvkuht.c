#include <stdio.h>
#include <string.h>
#include <math.h>
#define IN 99
#define N 6
int dijkstra(int cost[][N], int source, int target);
int dijsktrapm(int cost[][N],int source,int target);
int dijsktra(int cost[][N],int source,int target){
    int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j;
    char path[N];
    for(i=1; i<N; i++){
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0){
        min = IN;
        m = 0;
        for(i=1; i<N; i++){
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0){
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0){
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1){
        path[j++] = start+65;
        start = prev[start];
    }
    path[j]='\0';
    strrev(path);
    printf("%s", path);
    return dist[target];
}
int dijsktrapm(int cost[][N],int source,int target){
    int dist[N],prev[N],selected[N]={0},i,m,min,start,d,j,b;
    char path[N];
    for(i=1;i< N;i++){
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0){
        min = IN;
        m = 0;
        for(i=1;i< N;i++){
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0){
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0){
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1){
        for (b=0; b<N; b++){
            cost[start][b]=IN;
        }
        path[j++] = start+65;
        start = prev[start];
    }
    path[j]='\0';
    strrev(path);
    printf("%s", path);
    return dist[target];
}

int main(){
    int cost[N][N],i,j,w,ch,co,k,testcases,m, pm1=1, pm2=18, t;
    int source, target,x,y;
    for(i=1;i< N;i++){
        for(j=1;j< N;j++){
            cost[i][j] = IN;
        }
    }
    printf("enter the number of test cases\n");
    scanf("%d", &testcases);
    if (k<=10 && k>0){
        for (k=0; k<=testcases; k++){
            printf("Enter The Source:");
            scanf("%d", &source);
            printf("\nEnter The target");
            scanf("%d", &target);
            printf("\nenter the number of roads whos distances you want to enter");
            scanf("%d", &m);
            for(k=0; k<=m; k++){
                printf("\nenter the two nodes between which you want to enter the distance of");
                scanf("%d %d %d", &x, &y, &w);
                cost[x][y]=cost[y][x]=w;
            }
            dijkstrapm(cost, pm1, pm2);
            co = dijsktra(cost,source,target);
            printf("\n%d",co);
        }
    }
}
