#include<stdio.h>

int a[20][20],q[20],visited[20],n,i,j,total,m,min=0,f=0,r=-1;
void bfs(int v , int total, int m)
{
 for(i=1;i<=n;i++)
  if(a[v][i] && !visited[i])
   q[++r]=i;
 if(f<=r)
 {
  visited[q[f]]=1;
   if(m>total-m)
	   m=total-m;
   if(m>min)
	   min=m;
  bfs(q[f++],total,m);
 }
}
int main()  
{
int T,total,n,i,v,j,m,min=0;
int A[10000][100000];
scanf("%d",&T);
if(0<T<1001)
	for(i=0;i<T;i++){
			scanf("%d",&n);
			}
	if(0<n<100001)
        for(i=0;i<n;i++){
			for(j=0;j<n;j++){
			A[i][j]=0;
			}
			}
		for(i=0;i<n;i++){
			
			scanf("%d",&i);
			total=total+i;
			}
		for(i=0;i<n;i++){
			
			scanf("%d %d",&i,&j);
			A[i][j]=1;
			}
		for(i=1;i<=n;i++)
		{
		  q[i]=0n;
		  visited[i]=0;
		  		    }
     		 for(i=1;i<=n;i++){
		 
		     for(j=1;j<=n;j++){
				
			    scanf("%d",&A[i][j]);
		}
	}
			 v=1;
			 bfs(v, total, m);
    printf("%d",min);		
}
