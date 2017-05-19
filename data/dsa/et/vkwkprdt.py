 
from collections import defaultdict
  
class Graph:
  
    def __init__(self,vertices):
        self.V= vertices 
        self.graph = defaultdict(list) 
 
    def addEdge(self,v,w):
        self.graph[v].append(w) 
        self.graph[w].append(v) 
  
    def Cycle(self,v,visited,parent):
 
     
        visited[v]= True
 
    
        for i in self.graph[v]:
            
            if  visited[i]==False : 
                if(self.Cycle(i,visited,v)):
                    return True
        
            elif  parent!=i:
                return True
         
        return False
         
  
    
    def isCycle(self):
        
        visited =[False]*(self.V)
        
        
        for i in range(self.V):
            if visited[i] ==False:
                if(self.Cycle(i,visited,-1))== True:
                    return True
         
        return False
 

g = Graph(5)
g.addEdge(1, 0)
g.addEdge(0, 2)
g.addEdge(2, 0)
g.addEdge(0, 3)
g.addEdge(3, 4)
 
if g.isCycle():
    print "Graph contains cycle"
else :
    print "Graph does not contain cycle(DAG) "
g1 = Graph(3)
g1.addEdge(0,1)
g1.addEdge(1,2)
 
 
if g1.isCycle():
    print "Graph contains cycle"
else :
    print "contain no cycle(DAG)"
