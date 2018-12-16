import collections

class Graph:
  def __init__(self):
    self.nodes = set()
    self.edges = collections.defaultdict(list)
    self.distances = {}

  def add_node(self, value):
    self.nodes.add(value)

  def add_edge(self, from_node, to_node, distance):
    self.edges[from_node].append(to_node)
    self.edges[to_node].append(from_node)
    self.distances[(from_node, to_node)] = distance
    self.distances[(to_node, from_node)] = distance

def getspath(graph,initial,visited,path,n):
    spath = 0
    parent=path[n]
    #n=len(path)+1
    if (parent==initial):
        return graph.distances[(parent,n)]
    else:
        return getspath(graph,initial,visited,path,path[n])+graph.distances[parent,n]


def dijsktra(graph, initial):
  visited = {initial: 0}
  path = {}

  nodes = set(graph.nodes)

  while nodes:
    min_node = None
    for node in nodes:
      if node in visited:
        if min_node is None:
          min_node = node
        elif visited[node] < visited[min_node]:
          min_node = node

    if min_node is None:
      break

    nodes.remove(min_node)
    current_weight = visited[min_node]

    for edge in graph.edges[min_node]:
      weight = current_weight + graph.distances[(min_node, edge)]
      if edge not in visited or weight < visited[edge]:
        visited[edge] = weight
        path[edge] = min_node

  return [visited, path]

def dijsktramodifed(graph, initial,b):
    visited = {initial: 0}
    path = {}

    nodes = set(graph.nodes)

    while nodes:
      min_node = None
      for node in nodes:
        if node in visited:
          if min_node is None:
            min_node = node
          elif visited[node] < visited[min_node]:
            min_node = node

      if min_node is None:
        break

      nodes.remove(min_node)
      current_weight = visited[min_node]

      for edge in graph.edges[min_node]:
        #i=edge;
        weight = current_weight + graph.distances[(min_node, edge)]
        if edge not in visited or weight < visited[edge]:
            if b[edge]==0:
                visited[edge] = weight
                path[edge] = min_node

    return [visited, path]

t=input()
for i in range(t):
    l=map(int,raw_input().split())
    n=l[0]
    m=l[1]
    o=map(int,raw_input().split())
    s=o[0]
    t=o[1]
    graph=Graph()
    for j in range(1,n+1):
        graph.add_node(j)
    for j in range(m):
        p=map(int,raw_input().split())
        x=p[0]
        y=p[1]
        d=p[2]
        graph.add_edge(x,y,d)
    sp_1=dijsktra(graph,1)
    sp_n=dijsktra(graph,n)
    path=sp_1[1]
    #print path
    visited=sp_1[0]
    pathrev=sp_n[1]
    visitedrev=sp_n[0]
    #print pathrev
    spath_1_n=getspath(graph,1,visited,path,3)
    #print spath_1_n
    b=[0]*(n+1)
    #print b
    # for i in range(0,n):
    #     b[i].append(0)
    for v in range(1,n):
        spath_1_v=visited[v]
        spath_n_v=visitedrev[v]
        if(spath_1_n==spath_1_v + spath_n_v):
            b[v]=1
    sp_s=dijsktramodifed(graph,s,b)
    print visited[t]
