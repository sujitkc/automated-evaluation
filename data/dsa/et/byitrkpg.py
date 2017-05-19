#implementing bfs and dfs using adjacency list
from collections import defaultdict

class Graph:

    def __init__(self):
        self.graph=defaultdict(list)

    def add_edge(self,u,v):
        self.graph[u].append(v)

    def BFS(self,s):
        visited=[False]*(len(self.graph))

        queue=[]

        queue.append(s)
        visited[s]=True

        while queue:
            s=queue.pop(0)
            print s

            for i in self.graph[s]:
                if visited[i]==False:
                    queue.append(i)
                    visited[i]=True


g=Graph()
g.add_edge(5,8)
g.add_edge(5,4)
g.add_edge(4,2)
g.add_edge(4,6)



print "\n"
print "Adjacency list representation of graph is:",g.graph
print "\n"

print "BFS is:", g.BFS(2)
