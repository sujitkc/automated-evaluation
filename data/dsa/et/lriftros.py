from collections import defaultdict
class Graph:
    def __init__(self):
        self.graph = defaultdict(list)
    def addEdge(self,u,v):
        self.graph[u].append(v)
        print self.graph
    def cal_total():
    	for i in self.graph:
    		w=weight[i]
    		for j in self.graph[i]:
    			w+=weight[j]
    		total.append(w)
    def answer():
    	for i in self.graph:
    		for j in self.graph[i]:
    			v1=total[i]-weight[j]
    			v2=total[j]-weight[i]
    			min_weight.append(min(v1,v2))

weight=[5,4,8,2,6]
total=[]
min_weight=[]
g = Graph()
g.addEdge(1, 2)
g.addEdge(2, 1)
g.addEdge(1, 3)
g.addEdge(3, 1)
g.addEdge(4, 2)
g.addEdge(2, 4)
g.addEdge(2, 5)
g.addEdge(5, 2)
for i in range(0,len(min_weight)):
	mini=9797979
	if(mini<i):
		mini=i
print mini