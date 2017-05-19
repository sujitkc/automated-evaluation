#include<iostream>
#include<vector>
#include<unordered_map>
#include<limits>
#include<queue>
#include<stack>
using namespace std;

template <typename V, typename W> class Graph{
	protected:
		class Heap{
				struct Node{
					int v;
					W priority;

					Node(int v, W p){
						this->v = v;
						this->priority = p;
					}
				};

				vector<Node> a;
				int size;
				vector<int> pos;
				bool minHeap;

				int parent(int i){
					return (i-1)/2;
				}

				int left(int i){
					return 2*i + 1;
				}

				int right(int i){
					return 2*i + 2;
				}

				bool compare(W a, W b){
					if(minHeap) return a < b;
					return a > b;
				}

				void swap(Node &a, Node &b){
					Node t = a;
					a = b;
					b = t;

					swap(pos[a.v], pos[b.v]);
				}

				void swap(int &a, int &b){
					int t = a;
					a = b;
					b = t;
				}

			public:

				Heap(int l, W inf, bool mh = true);
				void top_down_heapify(int i);
				void bottom_up_heapify(int i);
				void update(int i, W k);
				int top();
		};

		struct Edge{
			int d;
			W wt;

			Edge(int v, W w){
				d = v;
				wt = w;
			}
		};

		vector<vector<Edge> > adjList;
		const W INF;
		int size;

	public:

		Graph(int n, W x) : INF(x){
			this->size = 0;
			for(int i = 0; i < n; ++i){
				insert_node();
			}
		}
		void insert_node();
		void insert_edge(V src, V dest, W wt = 1);
		long long int dijkstra(V rt);
		Graph get_transpose();
		void build_hospital();
};

/* Graph Functions - START */
template <typename V, typename W> void Graph<V, W>::insert_node(){
	adjList.push_back(vector<Edge>());
	this->size++;
}

template <typename V, typename W> void Graph<V, W>::insert_edge(V src, V dest, W wt){
	adjList[src].push_back(Edge(dest, wt));
}

template <typename V, typename W> long long int Graph<V, W>::dijkstra(V root){
	Heap m(this->size, INF);
	vector<W> dist(this->size, INF);
	long long int data;

	m.update(root, 0);
	dist[root] = 0;

	for(int i = 0; i < this->size; ++i){
		root = m.top();
		if(dist[root] == INF){
			return INF;
		}
		data = dist[root];

		for(typename vector<Edge>::iterator j = adjList[root].begin(); j != adjList[root].end(); ++j){
			if(dist[root] + j->wt < dist[j->d]){
				dist[j->d] = dist[root] + j->wt;
				m.update(j->d, dist[j->d]);
			}
		}
	}

	return data;
}
/* Graph Functions - END */

/* Heap Functions - START */
template <typename V, typename W> Graph<V, W>::Heap::Heap(int l, W inf, bool mh){
	this->size = l;
	minHeap = mh;

	for(int i = 0; i < this->size; ++i){
		a.push_back(Node(i, inf));
		pos.push_back(i);
	}
}

template <typename V, typename W> void Graph<V, W>::Heap::top_down_heapify(int i){
	int l = left(i), r = right(i);
	int j = i;
	while(r < this->size){
		j = (compare(a[l].priority, a[r].priority) ? l : r);

		if(compare(a[i].priority, a[j].priority)){
			break;
		}
		else{
			swap(a[i], a[j]);
			i = j;
			l = left(i);
			r = right(i);
		}
	}

	if(l == this->size-1 && compare(a[l].priority, a[j].priority)){
		swap(a[l], a[j]);
	}
}

template <typename V, typename W> void Graph<V, W>::Heap::update(int i, W k){
	if(compare(a[pos[i]].priority, k)){
		a[pos[i]].priority = k;
		top_down_heapify(pos[i]);
	}
	else{
		a[pos[i]].priority = k;
		bottom_up_heapify(pos[i]);
	}
}

template <typename V, typename W> int Graph<V, W>::Heap::top(){
	swap(a[0], a[--this->size]);
	top_down_heapify(0);
	return a[this->size].v;
}

template <typename V, typename W> void Graph<V, W>::Heap::bottom_up_heapify(int i){
	int p = parent(i);
	while(p > 0){
		if(compare(a[i].priority, a[p].priority)){
			swap(a[p], a[i]);
			i = p;
			p = parent(i);
		}
		else{
			break;
		}
	}

	if(compare(a[i].priority, a[p].priority)){
		swap(a[p], a[i]);
	}
}
/* Heap Functions - END */

template <typename V, typename W> void Graph<V, W>::build_hospital(){
	// Graph<V, W> trans = get_transpose();
	long long int ans = INF, temp;
	int node;

	for(int i = 0; i < size; ++i){
		temp = dijkstra(i);
		if(temp < ans){
			ans = temp;
			node = i;
		}
	}

	if(ans == INF) cout<<-1;
	else cout<<node+1<<" "<<ans;
	cout<<endl;
}

int main(){
	int t, n, m, i, j, d;
	cin>>t;
	while(t--){
		cin>>n>>m;
		Graph<int, int> g(n, numeric_limits<int>::max());
		while(m--){
			cin>>j>>i>>d;
			g.insert_edge(i-1, j-1, d);
		}
		g.build_hospital();
	}
}
