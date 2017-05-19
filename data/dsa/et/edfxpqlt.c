#include<stdio.h>

int n;
int p[n+1];
int w[n+1];
int weight(int v);
int min(int a,int b);

int weight(int v)
{ int w=0,i;
	for(i=1;i<n+1;i++)
	{	if(p[i]==v)
		{w=w[v]+weight(i);
		}
	}
	return w;
}
int min(int a,int b)
{if(a<b)
	{return a;
	}
 else
 	{return b;
	 }
}
int main()
{int i,k,dul[n+1],t=0,x,max[n+1],edge;
 printf("enter no of nodes");
 scanf("%d",&n);
 for(i=1;i<n+1;i++)
 { printf("if node %d has a parent enter it's if not enter 0",i);
   scanf("%d",&k);
   p[i]=k;
 }
 for(i=1;i<n+1;i++)
 {printf("enter weight of node %d",i);
  scanf("%d",&k);
   w[i]=k;
   t=t+k;
 }
  for(i=1;i<n+1;i++)
  {dul[i]=p[i];
  }
  for(i=1;i++;i<n)
  { p[i]=0;
  	x=min(weight(i),weight(dul[i]));
  	if(x==t)
  	{x=0;
	  }
  	max[i]=x;
  }
  k=max[1];
  for(i=1;i<n+1;i++)
  {if(k<max[i])
  	{k=max[i];
	  }
  }
  for(i=1;i<n+1;i++)
  {if(max[i]==k)
		{edge=i;
		}

  }
  printf("the edge to be removed to get maximun is between %d and %d",edge,dul[edge]);
}
