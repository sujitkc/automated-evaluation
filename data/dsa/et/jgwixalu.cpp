	#include<stdio.h>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<utility>
int testglob=20000,globele=-1;
using namespace std;
void ass(int arr1[][3],int arr2[][3],int i,int j){
    arr1[i][0]=arr2[j][0];
    arr1[i][1]=arr2[j][1];
    arr1[i][2]=arr2[j][2];
}
void merge(int arr[][3],int start,int n){
    if(n-start==2){
        int temp[3];
        if (arr[start][0]>arr[start+1][0]){
            temp[0]=arr[start][0];
            temp[1]=arr[start][1];
            temp[2]=arr[start][2];
            arr[start][0]=arr[start+1][0];
            arr[start][1]=arr[start+1][1];
            arr[start][2]=arr[start+1][2];
            arr[start+1][0]=temp[0];
            arr[start+1][1]=temp[1];
            arr[start+1][2]=temp[2];
        }
        return;
    }
    else if(n-start==1 || n-start==0){
        return;
    }
    else{
        merge(arr,start,(n-start)/2+start+1);
        merge(arr,(n-start)/2+start+1,n);
        int fi[n][3],i,j=start,k=(n-start)/2+start+1;
        for(i=start;i<n;i++){
            if(k>=n){
                fi[i][0]=arr[j][0];
                fi[i][1]=arr[j][1];
                fi[i][2]=arr[j][2];
                j++;
            }
            else if(j>=(n-start)/2+start+1){
                ass(fi,arr,i,k);
                k++;
            }
            else if(arr[j][0]<arr[k][0]){

                ass(fi,arr,i,j);
                j++;
            }
            else{
                ass(fi,arr,i,k);
                k++;
            }
        }
        for(i=start;i<n;i++){
            ass(arr,fi,i,i);
        }
    }
}
void print(int *arr,int n){
    /*for(int i=0;i<n;i++){
        cout<<arr[i]<<"";

    }*/
    cout<<"";
}
class minHeap{
    int heap[10000], n;
    void bottom_up(int i,int *arr){
        int parent=(i-1)/2;
        int temp;
        if(parent>=0 && arr[parent]>arr[i]){
            temp=arr[parent];
            arr[parent]=arr[i];
            arr[i]=temp;
            bottom_up(parent,arr);
        }
    }
    void formHeap(int *arr,int n){
        for(int i=0;i<n;i++){
            bottom_up(i,arr);
        }
    }
    void top_down(int *arr,int s,int e){
        int temp_data,k=0,go=0;
        int parent=s;
        int l=2*s+1;
        int r=2*s+2;
        if(l<e && arr[l]<arr[parent]){
            temp_data=arr[l];
            arr[l]=arr[parent];
            arr[parent]=temp_data;
            k=1;

        }
        if(r<e && arr[r]<arr[parent]){
            temp_data=arr[r];
            arr[r]=arr[parent];
            arr[parent]=temp_data;

            go=1;
        }
        if(go==1){
            parent=r;
        }
        else if(k==1){
            parent=l;
        }
        if(parent!=s){
            top_down(arr,parent,e);
        }
    }
    void del_top(int *arr,int *n){
        arr[0]=arr[*n-1];
        *n=*n-1;
        print_heap();
        top_down(arr,0,*n);
    }
public:

    minHeap(int *arr,int n){
        this->n=n;
        for(int i=0;i<n;i++){
            heap[i]=arr[i];
        }
        formHeap(heap,n);
        //print_heap();
    }
    void print_heap(){
        for(int i=0;i<n;i++){
            //cout<<heap[i]<<" ";
        }
        //cout<<"\n";
    }
    int get_min(){
        if(this->n==0){
            return -1;
        }
        int temp=heap[0];
        del_top(heap,&n);
        return temp;
    }

};
class graph{
protected:
    enum color{
        red,blue,yellow
    };
    void do_dfs(int n){
        color lis[1000];
        for(int i=0;i<this->no;i++){
            lis[i]=red;
        }
        std::stack <int> stk;
        stk.push(0);
        lis[0]=yellow;
        int temp;
        while(!stk.empty()){
            cout<<stk.top()<<" ";
            temp=stk.top();
            lis[temp]=blue;
            stk.pop();
            for(int i=0;i<connected[temp].size();i++){
                if(lis[connected[temp][i].first]==red){
                    stk.push(connected[temp][i].first);
                    lis[connected[temp][i].first]=yellow;
                }
            }
        }
        //cout<<"\n";
    }
    void do_bfs(int n){
        color lis[1000];
        for(int i=0;i<this->no;i++){
            lis[i]=red;

        }
        queue <int> que;
        que.push(0);
        lis[0]=yellow;
        int temp;
        while(!que.empty()){
            cout<<que.front()<<" ";
            temp=que.front();
            lis[temp]=blue;
            que.pop();
            for(int i=0;i<connected[temp].size();i++){
                if(lis[connected[temp][i].first]==red){
                    que.push(connected[temp][i].first);
                    lis[connected[temp][i].first]=yellow;
                }
            }
        }
        cout<<"\n";
    }

public:
    int no;
    std::vector <pair<int,int> > connected[1000];
    graph(int no){
        this->no=no;
    }
    void topological(int n,vector <int> & arr,int *visited){
        visited[n]=1;
        for(int i=0;i<connected[n].size();i++){
            if(visited[connected[n][i].first]==0){
                topological(connected[n][i].first,arr,visited);
            }
        }
        arr.push_back(n);

    }
    void add_edge(int x,int y,int weight){
        pair <int,int> temp;
        temp = make_pair(y,weight);
        connected[x].push_back(temp);
    }
    void DFS(){
        do_dfs(0);
    }
    void BFS(){
        do_bfs(0);
    }
    void topo_sort(){
        vector <int> arr;
        int visited[this->no];
        for(int i=0;i<this->no;i++){
            visited[i]=0;
        }
        topological(0,arr,visited);
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
    }
    void dijkstra(int node,bool poss[],int maxi[]){
        int D[this->no];
        int visited[this->no]={0};
        int mapping[10000]={-1};
        int s;
        int hep[10000];
        for(int i=0;i<this->no;i++){
            D[i]=20000;
        }
        D[node]=0;
        while(node!=-1){
            visited[node]=1;
            s=connected[node].size();
            // for(int i=0;i<s;i++){
            //     hep[i]=connected[node][i].second;
            //     mapping[connected[node][i].second]=connected[node][i].first;
            // }

            for(int i=0;i<s;i++){
                if(D[node] + connected[node][i].second < D[connected[node][i].first]){
                    D[connected[node][i].first]=D[node]+connected[node][i].second;
                }
            }
           print(D,this->no);
            minHeap h(D,this->no);
            for(int i=0;i<this->no;i++){
                if(visited[i]!=1 || mapping[D[i]]==-1){
                    mapping[D[i]]=i;
                }
            }
            int got=h.get_min();
            while (visited[mapping[got]]==1 && got!=-1){
                got=h.get_min();
            }
            if(got==-1){
                node=-1;
            }
            else{
                node=mapping[got];
            }
        }
        for(int i=0;i<this->no;i++)
		{
        	cout<<D[i]<<" "<<i<<endl;
			if(D[i]>=20000)
        	{
        		poss[i]=false;     		
			}
            if(poss[i]&&maxi[i]<D[i])
			{
				maxi[i]=D[i];
			}
			//edit and see			
		}	
    }
};

int main(){
	int T;
	scanf("%d",&T);
	while(T>0)
	{
	int m,n,u,v,d;
	scanf("%d%d",&n,&m);
  	graph g(n);
  	for(;m>0;m--)
  	{
	scanf("%d %d %d",&u,&v,&d); 
    g.add_edge(u-1,v-1,d);
	}
	bool poss[n];
    int maxi[n];
    for(int i=0;i<n;i++)
    {
	maxi[i]=0;
	poss[i]=true;
	}
	for(int i=0;i<n;i++)
    {
	g.dijkstra(i,poss,maxi);
	for(int j=0;j<n;j++)
    if(poss[j])
	printf("1\n");
	else
	printf("0\n");
		
	}
	
	/*
	for(int j=0;j<n;j++)
    if(!poss[j])
	g.dijkstra(j,poss,maxi);
	*/
	for(int j=0;j<n;j++)
    if(poss[j])
	printf("1\n");
	else
	printf("0\n");
	
	
	int mine =20000,minel=-1;
	for(int j=0;j<n;j++)
    {
    	printf("%d\n",maxi[j]);
    	if(poss[j]&&maxi[j]<mine)
    	{
    		minel=j;
    		mine=maxi[j];
		}
	}
	printf("%d,%d",minel+1,mine);
	
	T--;
	}
return 0;
}
