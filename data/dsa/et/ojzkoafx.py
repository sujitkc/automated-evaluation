g={0:{1:20,3:9,5:2},1:{0:20,2:2},2:{1:2,3:3},3:{0:9,2:3,4:2,5:5},4:{3:2,5:3},5:{0:2,4:3,3:5}}
def buildheap(a,l1,l2):
    heap=[]
    for i in range(len(a)):
        heap.append(a[i])
        n=len(heap)-1
        insertheap(heap,n,l1,l2)
        #print heap
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
def dijktra1(g,dest):
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
    v=0
    b=[0]*n
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
        b[v]=1
        if(v==dest):
          break
    parent[1]=-1
    print parent
    return b
def dijktra2(g,dest,b):
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
    v=0
    a[v]=0
    p=0
    heap=buildheap(a,l1,l2)
    v=extractmin(heap,l1,l2,dist)
    visited[v]=1
    while len(heap):
        for i in g[v]:
             if(b[i]==0): 
                  if visited[i]==0 and heap[l1[i]]>dist[v]+g[v][i]:
                    decreasekey(heap,l1[i],dist[v]+g[v][i],l1,l2)
                    parent[i]=v
        v=extractmin(heap,l1,l2,dist)
        visited[v]=1
        b.append(v)
        if(v==dest):
          break 
    print parent
b=[]
b=dijktra1(g,4)
dijktra2(g,5,b)
