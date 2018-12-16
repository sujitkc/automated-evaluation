
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>
#include<unordered_map>
using namespace std;


template <class W>
class Heap{

  W INF;//=(numeric_limits<W>::infinity());
  struct Node{
      W priority;
      int key;
      Node(W p=0,int k=-1){
          priority=p;
          key=k;
      }
  };
  Node *root;
  int *mapping;
  int n;
  int maxSize;
  int type;
  int c(Node n1,Node n2){
      return type*n1.priority<type*n2.priority;
  }
  void swap(Node &n1,Node &n2){

    Node t=n1;
    n1=n2;
    n2=t;
    swap(mapping[n1.key],mapping[n2.key]);
  }
  void swap(int &n1,int &n2){

    int t=n1;
    n1=n2;
    n2=t;
  }

public:
  Heap(int type,int maxSize): INF(numeric_limits<W>::max()/2){ //Build a new heap from an existing array
    this->root=new Node[maxSize];
    this->maxSize=maxSize;
    this->mapping=new int[maxSize];
    this->n=maxSize;
    this->type=type;
    for(int i=0;i<maxSize;i++){
        root[i].priority=INF*type;
        root[i].key=i;
        mapping[i]=i;
    }
  }

  W getDistance(int i){
      return root[mapping[i]].priority;
  }

  int size(){
      return n;
  }
  void bottomUpHeapify(int index){
    int t=index;
    int p=(t-1)/2;
    while (t&&c(root[t],root[p])){
      swap(root[t],root[p]);
      t=p;
      p=(t-1)/2;
    }
  }
  int viewTop(){
      return root[0].key;
  }
  bool isEmpty(){
    return !n;
  }
  void topDownHeapify(int index){
    int t=index;
    int r=t*2+2;
    int l=t*2+1;
    int j;
    while(r<n){
      if(c(root[t],root[r])&&c(root[t],root[l]))return;
      if(c(root[l],root[r]))j=l;
      else j=r;
      swap(root[j],root[t]);
      t=j;
      r=t*2+2;
      l=t*2+1;
    }
    if(l==n-1 && c(root[l],root[t]))swap(root[t],root[l]);
  }
  int deleteTopNode(){
    swap(root[0],root[--n]);
    topDownHeapify(0);
    return root[n].key;
  }
  void viewHeap(){
    for(int i=0;i<n;i++)
      cout<<root[i]<<" ";
    cout<<endl;
  }
  void updateKey(int key,int x){
    int index=mapping[key];
    Node n(x,-1);
    root[index].priority=x;
    bottomUpHeapify(index);
  }

};

template <class T, class W>
class Graph{
protected:
    class Edge{
    public:
        W weight;
        int destination;
    Edge(W weight,int destination){
        this->weight=weight;
        this->destination=destination;
        }
    };
    W INF;
    vector<T> inverseVertices;
    unordered_map<T, int> vertices;
    vector< vector<Edge > > adjList;
    int size;
public:
    Graph(T node=0,int size=0) : INF(numeric_limits<W>::max()/2){
        this->size=0;
        for(int i=0;i<size;i++)insertNode(node+i);

    }
    void insertNode(T n){
        vertices[n]=size;
        inverseVertices.push_back(n);
        vector<Edge> list;
        adjList.push_back(list);
        size++;
    }
    void insertEdge(T n1, T n2,W weight=1){
        Edge e(weight,vertices[n2]);
        adjList[vertices[n1]].push_back(e);
    }
    void showNodes(){
        for(int i=0;i<size;i++){
            cout<<inverseVertices[i]<<endl;
        }
        cout<<endl;
        for(int i=0;i<size;i++){
            cout<<vertices[inverseVertices[i]]<<endl;
        }
    }
    Graph reverseGraph(){
        Graph <T,W>G;
        for(int i=0;i<size;i++){
            G.insertNode(inverseVertices[i]);
        }
        for(int i=0;i<size;i++){
            for(typename vector< Edge >::iterator j=adjList[i].begin();j!=adjList[i].end();j++){
                G.insertEdge(inverseVertices[j->destination],inverseVertices[i],j->weight);
            }
        }
        return G;
    }
    W DKS(T root){
        int startNode=vertices[root];
        bool *visited=new bool[size]();
        int *PI=new int[size]();
        Heap<W> DKSqueue(1,size);
        DKSqueue.updateKey(startNode,0);
        PI[startNode]=startNode;
        visited[startNode]=true;
        W dist;
        while(DKSqueue.isEmpty()==false){
            int node=DKSqueue.viewTop();
            DKSqueue.deleteTopNode();
            visited[node]=true;
            dist=DKSqueue.getDistance(node);

            for(typename vector< Edge >::iterator i=adjList[node].begin();i!=adjList[node].end();i++){
                int adjNode=i->destination;
                if(visited[adjNode]==false){
                    if(dist+i->weight<DKSqueue.getDistance(adjNode)){
                        DKSqueue.updateKey(adjNode,dist+i->weight);
                        PI[adjNode]=node;
                    }
                }
            }
        }

        delete[] visited;
        delete[] PI;
        return dist;
    }

    void findMostReachableNode(){
        Graph reverseG=reverseGraph();
        W min=INF;
        int minNode=-1;
        W temp;
        for(int i=0;i<size;i++){
            temp=reverseG.DKS(inverseVertices[i]);
            if(temp<min){
                min=temp;
                minNode=i;
            }
        }
        if(minNode==-1)cout<<-1<<endl;
        else cout<< inverseVertices[minNode]<<" "<<min<<endl;
    }

    template <class L, class M>
    friend ostream& operator<<(ostream& os, const Graph<L,M>&);
};


template <class T, class W>
ostream& operator<<(ostream& os,const Graph<T,W>& g){
    for(int i=0;i<g.adjList.size();i++){
        os<<g.inverseVertices[i]<<"->";
        for(int j=0;j<g.adjList[i].size();j++){
            os<<g.adjList[i][j].weight<<","<<g.inverseVertices[g.adjList[i][j].destination]<<"\t";
        }
        os<<endl;
    }
    return os;
}

int main(){

    int t;
    cin>>t;
    while(t--){
        int n,m,n1,n2,d;
        cin>>n>>m;
        Graph<int,int> G(1,n);
        for(int i=0;i<m;i++){
            cin>>n1>>n2>>d;
            G.insertEdge(n1,n2,d);
        }
        G.findMostReachableNode();
    }

}
