#include<stdio.h>
void dfs(int);
int g[10][10],visited[10],n;
int main()
{
	int i,j;
	printf("enter the num of vertices:");
	scanf("%d",&n);
	printf("enter the adjacency matrix:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",g[i][j]);
		}
	}
	for(i=0;i<n;i++)
	{
		visited[i]=0;
	}
	dfs(0);
return 0;
}
void dfs(int i)
{
	int j;
	printf("%d",i);
	visited[i]=1;
	for(j=0;j<n;j++)
	{
		if((visited[j]!=1)&&(g[i][j]==1))
		{
			dfs(j);
		}
	}
}
