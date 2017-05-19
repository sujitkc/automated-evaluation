g={1:{2:8,3:44,4:37},2:{4:10},3:{1:41,2:23},4:{3:13},5:{1:13}}
parent=[]
def buildheap(a,l1,l2):
    heap=[]
    for i in range(len(a)):
        heap.append(a[i])
        n=len(heap)-1
        insertheap(heap,n,l1,l2)
    return heap
def insertheap(heap,n,l1,l2):
    while n>0:
        p=(n-1)/2
        if(heap[n]<heap[p]):
            t=heap[n]
            heap[n]=heap[p]
            heap[p]=t
            t=l2[n]
            l2[n]=l2[p]
            l2[p]=t
            t=l1[l2[n]]
            l1[l2[n]]=l1[l2[p]]
            l1[l2[p]]=t
        n=p
    return
def extractmin(heap,l1,l2,dist):
    n=len(heap)-1
    x=l2[0]
    y=heap[0]
    heap[0]=heap[n]
    t=l1[l2[0]]
    l1[l2[0]]=l1[l2[n]]
    l1[l2[n]]=t
    l2[0]=l2[n]
    heap.pop(n)
    k=0
    l=0
    r=0
    while k<n:
        j=k
        l=2*k+1
        r=2*k+2
        if l<n and heap[l]<heap[j]:
            j=l
        if r<n and heap[r]<heap[j]:
            j=r
        if j!=k:
            t=heap[j]
            heap[j]=heap[k]
            heap[k]=t
            t=l2[j]
            l2[j]=l2[k]
            l2[k]=t
            t=l1[l2[j]]
            l1[l2[j]]=l1[l2[k]]
            l1[l2[k]]=t
        k=l
    dist[x]=y
    return x
def decreasekey(heap,i,val,l1,l2):
    heap[i]=val
    insertheap(heap,i,l1,l2)
## start from here--
def dijktra(g,i):
    n=len(g)
    l1=[]
    l2=[] 
    a=[9999]*n
    dist=[9999]*n
    parent=[-1]*n
    for i in range(n):
        l1.append(i)
        l2.append(i)
    visited=[0]*n
    v=i
    a[v]=0
    heap=buildheap(a,l1,l2)
    v=extractmin(heap,l1,l2,dist)
    visited[v]=1
    while len(heap):
        for i in g[v]:
            if visited[i]==0 and heap[l1[i]]>dist[v]+g[v][i]:
                decreasekey(heap,l1[i],dist[v]+g[v][i],l1,l2)
                parent[i]=v
        v=extractmin(heap,l1,l2,dist)
        visited[v]=1
    print parent,dist
maximum_list=[]
for i in g:
	dijkstra(g,i)
	y=max(dist)
	maximum_list.append(y)
	k=max(maximum_list)
	if y<k:
		node=i
print node 

