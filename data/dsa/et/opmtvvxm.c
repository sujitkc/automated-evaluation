#include<stdio.h>
 
void DFS(int);
int G[10][10],visited[10],n,k; 
 int sum=0; long long int a[10000000],min=0 ;
 
 
void main()
{
    int i,j;
   
    printf("Enter number of vertices:");
   
    scanf("%d",&n);
 
    
    printf("\nEnter adjecency matrix of the graph:");
   
    for(i=0;i<n;i++)
    {
       for(j=0;j<n;j++){
	   
            scanf("%d",&G[i][j]);
            sum =sum+G[i][j];
        }
    }
  for(i=0;i<n;i++)
    {
       for(j=0;j<n;j++){
       	
       	if(g[i][j]-sum/2=min&&g[i][j]<sum/2)
       

   for(i=0;i<n;i++)
        visited[i]=0;
 
    DFST(0);
}
void delete()
{

}
 
void DFST(int i)
{
    int j;
    printf("\n%d",i);
    
    visited[i]=1;
    a[k]=visited[i];
    k++;
    printf("\n%d",sum);
    
    for(j=0;j<n;j++)
       if(!visited[j]&&G[i][j]==1)
            DFST(j);
}
