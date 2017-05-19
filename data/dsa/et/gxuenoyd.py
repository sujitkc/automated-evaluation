t=input()
for q in range(t):
    n,m=map(int,raw_input().split())
    d={}
    for j in range(n):
        d[j]={}
    for j in range(m):
        x,y,z=map(int,raw_input().split())
        d[x-1][y-1]=d[x-1].get(y-1,0)+z
    #print d
    def transpose(d):
        dt={}
        p=len(d)
        for j in range(d):
            d[j]={}
        for j in range(d):
            for k in j:
                dt[k][j]=dt[k].get(j,0)+d[j][k]
        return dt
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
    ## start from here---
    def dijktra(g,v):
        n=len(g)
        l1=[] # keep of track position of a,b,c in heap means let say l1[a]=0 (0 is index of heap)
        l2=[] # keep track of position of heap index in a,b,c let say l2[0]=a
        a=[999999]*n
        dist=[999999]*n
        parent=[-1]*n
        for i in range(n):
            l1.append(i)
            l2.append(i)
        visited=[0]*n # to check wheather it is extracted or not
            #say rootnode for prim"s is 0
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
        d1={}
        return dist
    d1={}
    l=100000
    s=0
    for j in range(n):
        w=dijktra(d,j)
        for k in range(len(w)):
            if k==j:
                w[k]=-2
            if w[k]==999999:
                w[k]=-1
        e=w[0]
        r=j
        for k in range(len(w)):
            if w[k]>e:
                e=w[k]
                r=k
        if l>e:
            l=e
            s=r
        #print w,e,l
    print s+1,l
        
    
    
