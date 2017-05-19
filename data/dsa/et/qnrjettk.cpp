//DIJKSTRA SSSP ....

#include<bits/stdc++.h>

using namespace std;

int dijkstra(list<pair<int,int> > *adj , int src , int V);
int main()
{
	int t;
	int min = INT_MAX;
	cin>>t;
	while(t--)
	{
	int V , E , v1 , w , v2 ;
	
	cout<<" \n Enter the no of vertices and edges \n" ;
	cin>>V>>E;
	
	list<pair<int,int> > adj[V+1] ;
	
	for(int i = 0;i < E;i ++)
	{
		cin>>v1>>v2>>w;
		adj[v1].push_back(make_pair(v2,w));
	}
	
	int src;
	for(src = 1;src <=5 ;src ++)
	{
		int min1 = dijkstra(adj , src , V);
		if(min > min1)
			min = min1;
	}
}
cout<<min;
}


int dijkstra(list<pair<int,int> > *adj , int src ,int V)
{
	set<pair<int,int> > setd ;
	
	vector<int> dist(V,INT_MAX) ;
	
	setd.insert(make_pair(0,src));
	dist[src] = 0;
	
	while (!setd.empty())
    {
        pair<int, int> tmp = *(setd.begin());
        setd.erase(setd.begin());
 
        int u = tmp.second;
 
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin();i != adj[u].end();i ++)
        {
           
            int v = (*i).first;
            int weight = (*i).second;
 
            if (dist[v] > dist[u] + weight)
            {
                if (dist[v] != INT_MAX)
                    setd.erase(setd.find(make_pair(dist[v], v)));
 
                dist[v] = dist[u] + weight;
                setd.insert(make_pair(dist[v], v));
            }
        }
    }
 	int count = 1;
 	int sum = 0;
    for (int it = 1;it <=V;it ++)
        {
        	if(dist[it]!=INT_MAX)
        		count++;
        	else
				break;	
		}
	if(count == V)
	{
		for(int it = 1;it <=V;it ++)
			sum += dist[it];	
	}
	return sum;
}
