#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void BFS(vector<int>v[][2], int i, int n, int*nay){
    int x=0, l=0, b[n], c[n], j;
    for(j=0;j<n;j++){
        c[j]=0;
        b[j]=-1;
    }
    c[i]=1;
    b[0]=i;
    for(j=1;j<n;){
        if(x==v[b[l]][0].size()){
            l++;
            x=0;
        }
        else{
            if(c[v[b[l]][0].at(x)]==0){
                b[j]=v[b[l]][0].at(x);
                j++;
            }
            c[v[b[l]][0].at(x)]=1;
            x++;
        }
        if(j==l)
            break;
    }
    cout<<i<<" : ";
    for(j=0;j<n;j++){
        cout<<c[j]<<" ";
        if(c[j]==0){
            nay[j]=-1;
        }
    }
    cout<<endl;
}
struct Bla{
    int w, n;
};
void botup(Bla*a, int i){
	int p=(i-1)/2;
	while(i>0){
		if(a[i].w<a[p].w){
			swap(a[i], a[p]);
			i=p;
			p=(i-1)/2;
		}
		else
			break;
	}
}
void topdown(Bla*a, int i, int n){
	int l, r, j;
	l=2*i+1;
	r=2*i+2;
	while(r<n){
		if(a[l].w<a[r].w)
			j=l;
		else
			j=r;
		if(a[i].w<a[j].w)
			break;
		else{
			swap(a[i], a[j]);
			i=j;
			l=2*i+1;
			r=2*i+2;
		}
	}
	if(l==n-1 && a[i].w>a[l].w)
		swap(a[i], a[l]);
}
void Dijkstra(vector<int>v[][2], int x, int n, int*ans){
    int vis[n], k, l, i, j;
    Bla heap[n];
    for(i=0;i<n;i++){
        vis[i]=0;
        //heap[i].n=i;
        ans[i]=100000;
    }
    ans[x]=0;
    heap[0].w=0;
    heap[0].n=x;
    k=1;
    for(i=0;i<n;i++){
        l=heap[0].n;
        //cout<<l<<endl;
        if(l<n){
            vis[l]=2;
        for(j=0;j<v[l][0].size();j++){
            if(vis[v[l][0].at(j)]==0){
                heap[k].n=v[l][0].at(j);
                heap[k].w=v[l][1].at(j)+ans[l];
                botup(heap, k);
                vis[v[l][0].at(j)]=1;
                k++;
            }
            if(ans[l]+v[l][1].at(j)<ans[v[l][0].at(j)])
                ans[v[l][0].at(j)]=ans[l]+v[l][1].at(j);
        }
        swap(heap[k-1], heap[0]);
        k--;
            topdown(heap, 0, k);}
    }
    //for(i=0;i<n;i++)
    //    cout<<ans[i]<<" ";
    //cout<<endl;
}

int main() {
	ifstream fin;
	fin.open("input.txt");
    int t;
    fin>>t;
    while(t>0){
        int n, m, i, j, x, l, r;
        fin>>n>>m;
        vector<int> v[n][2];
        for(i=0;i<m;i++){
            fin>>l>>r;
            v[l-1][0].push_back(r-1);
            fin>>r;
            v[l-1][1].push_back(r);
        }
        int nay[n], ans[n], ans1[n];
        for(i=0;i<n;i++){
            nay[i]=ans[i]=ans1[i]=0;
        }
        /*for(i=0;i<n;i++){
            //BFS(v, i, n, nay);
        }*/
        for(i=0;i<n;i++){
            Dijkstra(v, i, n, ans);
            for(j=0;j<n;j++){
                if(ans[j]>ans1[j])
                    ans1[j]=ans[j];
            }
        }
        int z=100000, s=-1;
        for(i=0;i<n;i++){
            //cout<<ans1[i]<<" ";
            if(ans1[i]<z){
                s=i+1;
                z=ans1[i];
            }
        }
        if(s!=-1){
            cout<<s<<" "<<z<<endl;
        }
        else
            cout<<-1<<endl;
        t--;
    }
    fin.close();
    return 0;
}

