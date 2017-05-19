#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

void bfs(vector<int> a[], int*q, int*d, int i, int*ch)
{
ch[i]=1;

if(a[i].size()==0)
{
d[i]=q[i];
}
else
for(int j=0;j<a[i].size();j++)
{
if(ch[a[i].at(j)-1]==0){
bfs(a, s, d, a[i].at(j)-1, ch);
d[i]+=d[a[i].at(j)-1];
ch[a[i].at(j)-1]=1;
}
}
d[i]+=q[i];
}
}

int main()
{
int n, m, i, j, x, l, r;
cn>>n;
vector<int> v[n];
int b[n], c[n], s[n], d[n], ch[n];
for(i=0;i<n;i++){
cn>>s[i];
d[i]=ch[i]=0;
}

for(i=0;i<n-1;i++){
cn>>l>>r;
v[l-1].push_back(r);
v[r-1].push_back(l);
}

bfs(v, q, d, 0, ch);
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

