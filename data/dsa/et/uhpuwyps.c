#include<stdio.h>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<utility>
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
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";

    }
    cout<<"\n";
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
            cout<<heap[i]<<" ";
        }
        cout<<"\n";
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
        cout<<"\n";
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

};
class Und_Graph : public graph{
public:
    Und_Graph(int n) : graph(n){}
    void add_edge(int x,int y,int weight){
        pair <int,int> temp;
        temp = make_pair(y,weight);
        connected[x].push_back(temp);
        temp = make_pair(x,weight);
        connected[y].push_back(temp);
    }
    void SSC(){
        vector <int> arr;
        int visited[this->no];
        for(int i=0;i<this->no;i++){
            visited[i]=0;
        }
        topological(0,arr,visited);
        Und_Graph Rev(this->no);
        for(int i=0;i<this->no;i++){
            for(int j=0;j<this->connected[i].size();j++){
                Rev.add_edge(this->connected[i][j].first,i,this->connected[i][j].second);
            }
        }
        for(int i=0;i<this->no;i++){
            visited[i]=0;
        }
        for(int i=0;i<arr.size();i++){
            if(visited[arr[i]]==0){
                visited[arr[i]]=1;
                do_bfs(arr[i]);
                cout<<"\n";
            }
        }

    }
};
int main(){
    graph g(3);
    g.add_edge(0, 1 ,3);
    g.add_edge(1, 2 ,2);
    cout<<"hey \n";
    g.topo_sort();
    g.DFS();

    return 0;
}
