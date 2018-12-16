from collections import defaultdict

class Graph:
    total = 25
    def __init__(self,vertices,val,s):
        self.V = vertices
        self.val = val
        self.sum = s
        self.graph = defaultdict(list)


    def dfs(self,v,visited, stack):
        visited[v]= True
        self.val
        diff = []
        for i in self.graph[v]:
            if visited[i]==False:
                s = s + self.dfs(i, visited, stack)
                self.val = s
                min_sum = total-s
                diff.append(s - min_sum)
                print min(diff)

        stack = stack.append(v)
