import heapq
class Graph:
  def __init__(self,nodes):
    self.nodes=no
    self.nodeslist = []
    self.edgeslist = []
    for i in range(self.nodes):
        self.edgeslist.append({})
        self.adjlist.append(0)
  def add_node(self, value):
    node1=node(value)
    self.nodeslist[node1.value]=node1

  def add_edge(self, from_node, to_node, distance):
    self.egdeslist[from_node.value].append([from_node, to_node])
    self.adjlist[from_node]={}
class node:
    def __init__(self,value):
        self.value=value
        self.bool=0
def dijsktra(graph, s,t):
    Q=[]
    d={s:0}
    Qd={}
    p={}
    visited_set=set([s])

    for v in graph.adjlist[s]:
        d[v]=edgelist[s,v]
        item=[d[v],s,v]
        if v.bool==0:
            heap.heappush(Q,item)
        Qd[v]=item
    while Q:
         cost, parent, u = heapq.heappop(Q)
        if u not in visited_set:
            p[u]= parent
            visited_set.add(u)
            if u == t:
                return p, d
            for v in graphadjlist[u]:
                if d.get(v):
                    if d[v] > graph.edjelist[u, v] + d[u] and v.bool==0:
                        d[v] =  costs[u, v] + d[u]
                        Qd[v][0] = d[v]    
                        Qd[v][1] = u
                        heapq._siftdown(Q, 0, Q.index(Qd[v]))
                else:
                    d[v] = costs[u, v] + d[u]
                    item = [d[v], u, v]
                    heapq.heappush(Q, item)
                    Qd[v] = item    
    return None
for i in range(len(graph.nodeslist)):
    p1,d1=dijisktra(graph,air,T)
    p2,d2=dijisktra(graph,T,air)
for i in graph.nodeslist:
    if d1[i]+d2[i]=d1[T]:
        graph.nodeslist(i).bool=1
print dijisktras(graph,s,t)    
