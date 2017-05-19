#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <queue>
using namespace std;

class G_adj_list_node{

public:
	int vertex;
	int weight;
	G_adj_list_node * next;
	G_adj_list_node(int vertex = 0, int weight = 0){
		this -> vertex = vertex;
		this -> weight = weight;
		next = NULL;
	}
};


class Adj_list{
public:
	G_adj_list_node * head;
	Adj_list(){
		head = NULL;
	}
};

class Heap_node{
public:
	int v;
	int dist;
};

class Min_heap{
public:
	Heap_node * arr;
	int size;
	int * pos;
	Min_heap(int no_vertex){
		arr = new Heap_node[no_vertex];
		pos = new int[no_vertex];
		size = no_vertex;
	}
	void swap(int a,int b){
		int temp;
		temp = arr[a].v;
		arr[a].v = arr[b].v;
		arr[b].v = temp;
		temp = arr[a].dist;
		arr[a].dist = arr[b].dist;
		arr[b].dist = temp;
	}
	void new_node(int v, int dist, int i){
		arr[i].v = v;
		arr[i].dist = dist;
	}
	void print(){
		for(int i=1; i<size; i++){
			cout<<arr[i].v<<' '<<arr[i].dist<<'\n';
		}
	}
	bool isempty(){
		if(size == 0)
			return true;
		else
			return false;
	}
	Heap_node extractmin(){
		
		Heap_node root = arr[0];
		Heap_node last = arr[size - 1];
		arr[0] = last;
		pos[root.v] = size - 1;
		pos[last.v] = 0;
		size--;
		top_bottom_heapify(0);
		return root;
	}

	void top_bottom_heapify(int in){
		int l = 2*in +1;
		int r = 2*in +2,j;
		Heap_node temp;
		if(l == size-1 && arr[in].dist > arr[l].dist){
			pos[arr[in].v] = l;
			pos[arr[l].v] = in;	
			temp = arr[l];
			arr[l] = arr[in];
			arr[in] = temp;

			return;
		}
		while( r < size){
			if(arr[l].dist < arr[r].dist)
				j=l;
			else
				j=r;
			if(arr[in].dist < arr[j].dist)
				break;
			else{
				pos[arr[j].v] = in;
				pos[arr[in].v] = j;	
				temp = arr[j];
				arr[j] = arr[in];
				arr[in] = temp;
			}
			in=j;
			l=2*in+1;
			r=2*in+2;
			if(l == size-1 && arr[in].dist > arr[l].dist){
				pos[arr[in].v] = l;
				pos[arr[l].v] = in;	
				temp = arr[l];
				arr[l] = arr[in];
				arr[in] = temp;
				return;
			}
		}
	}
	void decrease_key(int v,int val){
		int i = pos[v];
		arr[i].dist = val;
		int p = (i-1)/2;
		while(arr[i].dist < arr[p].dist){
			pos[arr[i].v] = p;
			pos[arr[p].v] = i;
			swap(i,p);
			i = p;
			p = (i-1)/2;
		}
	}
	bool isinheap(int n){
		if(pos[n] < size)
			return true;
		return false;
	}
};


class G_adj_list{

private:
	int no_vertex;
	Adj_list * arr;
	int time;
	int * dfinal;
public:
	G_adj_list(int no_vertex){
		this -> no_vertex = no_vertex;
		arr = new Adj_list[no_vertex];
		time = 0;
		dfinal = new int[no_vertex];
		for(int i=0; i<no_vertex; i++){
			dfinal[i] = 0;
		}
	}

	void add_edge(int src, int dest, int weight){
		G_adj_list_node * temp = new G_adj_list_node( dest,weight);
		temp -> next = arr[src].head;
		arr[src].head = temp;
	}

	void print(){
		G_adj_list_node * temp;
		for(int i=1; i<no_vertex; i++){
			temp = arr[i].head;
			cout<<"src : "<<i<<"--"; 
			while ( temp != NULL){
				cout<<temp->vertex<<"/"<<temp->weight<<" ";
				temp = temp -> next;
			}
			cout<<'\n';
		}
	}
	void djkistra( int src){
		int ctr=-1;
		Min_heap h(no_vertex);
		int dist[no_vertex];
		for(int i=1; i<no_vertex; i++){
			dist[i] = INT_MAX;
			h.new_node(i,dist[i],i);
			h.pos[i] = i;
		}
		dist[src] = 0;
		h.decrease_key(src,dist[src]);
		h.print();
		while(!h.isempty()){
			Heap_node n = h.extractmin();
			if(n.dist != INT_MAX)
				ctr++;
			int u = n.v;
			G_adj_list_node * temp = arr[u].head;
			while(temp != NULL){
				int v = temp -> vertex;
				if(h.isinheap(v) && dist[u] != INT_MAX && temp -> weight + dist[u] < dist[v]){
					dist[v] = dist[u] + temp->weight;
					h.decrease_key(v,dist[v]);
				}
				temp = temp -> next;
			}
			cout<<'\n';
			h.print();
		}
		cout<<ctr<<'\n';
		for(int i=1; i<no_vertex; i++){
			cout<<dist[i]<<' ';
		}
	}
	void prob(){
		for(int i=1; i<no_vertex; i++){

		}
	}
};

int main(){

	int t;
	cin >> t;
	int no_vertex,no_edge;
	cin >> no_vertex;
	no_vertex++;
	cin >> no_edge;
	G_adj_list g(no_vertex);
	for(int i=0; i<no_edge; i++){
		int a,b,c;
		cin >>a;
		cin >> b;
		cin >> c;
		g.add_edge(a,b,c);
	}
   	g.djkistra(3);
    g.print();
   
}