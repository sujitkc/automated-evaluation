#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void Ayush(vector<int> a[], int*s, int*d, int i, int*check){
    check[i]=1;
    if(a[i].size()==0){
        d[i]=s[i];
    }
    else{
        for(int j=0;j<a[i].size();j++){
            if(check[a[i].at(j)-1]==0){
                Ayush(a, s, d, a[i].at(j)-1, check);
                d[i]+=d[a[i].at(j)-1];
                check[a[i].at(j)-1]=1;
            }
        }
        d[i]+=s[i];
    }
}
int main() {
    int n, m, i, j, x, l, r;
    cin>>n;
    vector<int> v[n];
    int b[n], c[n], s[n], d[n], check[n];
    for(i=0;i<n;i++){
        cin>>s[i];
        d[i]=check[i]=0;
    }
    for(i=0;i<n-1;i++){
        cin>>l>>r;
        v[l-1].push_back(r);
        v[r-1].push_back(l);
    }
    Ayush(v, s, d, 0, check);
    m=d[0];
    for(i=0;i<n;i++){
        if(d[0]-2*d[i]>=0 && d[0]-2*d[i]<m){
            m=d[0]-2*d[i];
            l=d[i];
        }
        else if(2*d[i]-d[0]>=0 && 2*d[i]-d[0]<m){
            m=2*d[i]-d[0];
            l=d[i];
        }
    }
    cout<<l;
}

