from collections import defaultdict
class graph:
    summ = 0
    def __init__(self):
        self.graph=defaultdict(list)
    def addedge(self,u,v):
        self.graph[u].append(v)
    def BFS(self,s):
        visited=[False]*(len(self.graph))
        queue=[]
        queue.append(s)
        graph.summ = graph.summ + s
        visited[s]=True
        while queue:
            s=queue.pop(0)
            #print s,
            for i in self.graph[s]:
                if visited[i]==False:
                    queue.append(i)
                    visited[i]=True
        print graph.summ
