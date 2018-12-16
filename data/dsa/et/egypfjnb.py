class Heap:

    def __init__(self, size, default):
        self.pos = [i for i in range(size)]
        self.heap = [[i, default] for i in range(size)]
        self.size = size

    def parent(self, n):
        return (n-1)/2

    def left(self, n):
        return 2*n + 1

    def right(self, n):
        return 2*n + 2

    def compare(self, a, b):
        return (a < b)# To get max heap change this to (a > b)

    def swap(self, i, j):
        self.pos[self.heap[i][0]] = j
        self.pos[self.heap[j][0]] = i
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def topDownHeapify(self, i):
        l = self.left(i)
        r = self.right(i)
        j = i

        while(r < self.size):
            if(self.compare(self.heap[l][1], self.heap[r][1])):
                j = l
            else:
                j = r
            if(self.compare(self.heap[i][1], self.heap[j][1])):
                break
            else:
                self.swap(i, j)
                i = j
                l = self.left(i)
                r = self.right(i)

        if(self.size - 1 == l and (not self.compare(self.heap[i][1], self.heap[l][1]))):
            self.swap(l, i)

    def bottomUpHeapify(self, i):
        p = self.parent(i)
        while(p >= 0):
            if(self.compare(self.heap[i][1], self.heap[p][1])):
                self.swap(i, p)
                i = p
                p = self.parent(i)
            else:
                break

    def Top(self):
        val = self.heap[0][0]
        self.size = self.size - 1
        self.swap(0, self.size)
        self.heap.pop()
        self.topDownHeapify(0)
        return val

    def alter(self, i, val):
        if(self.compare(self.heap[self.pos[i]][1], val)):
            self.heap[self.pos[i]][1] = val
            self.topDownHeapify(self.pos[i])
        else:
            self.heap[self.pos[i]][1] = val
            self.bottomUpHeapify(self.pos[i])

class Graph:

    def __init__(self):
        self.node = {}
        self.invVertices = []
        self.adjList = []
        self.shortestpath = []
        self.lon = []
    def addNode(self, n):
    	self.lon.append(n)
        self.invVertices.append(n)
        self.node[n] = len(self.node)
        self.adjList.append([])

    def addEdge(self, u, v, w):
		self.adjList[self.node[u]].append((self.node[v], w))
		self.adjList[self.node[v]].append((self.node[u], w))
    def dijkstra(self, s,liesonsp):
    	self.shortestpath = []
        root = self.node[s]
        size = len(self.node)
        my_infinity = float('INF')
        h = Heap(size, my_infinity)
        dist = [my_infinity for i in range(size)]
        pi = [0 for i in range(size)]

        h.alter(root, 0)
        pi[root] = root
        dist[root] = 0

        for i in range(size):
            root = h.Top()
            # print root
            if(dist[root] == my_infinity):
                break

            for node, w in self.adjList[root]:
                if node not in liesonsp:
	                if(dist[node] > dist[root] + w):
	                    dist[node] = dist[root] + w
	                    h.alter(node, dist[node])
	                    pi[node] = root

        for i in range(size):
            if(dist[i] != my_infinity):
                self.shortestpath.append([self.invVertices[i], dist[i], self.invVertices[pi[i]]])
    def printdijkstra(self,s):
    	return self.shortestpath
    def printnodes(self):
    	return self.lon
    def printadj(self):
		return self.adjList


testcase = input()
for i in range(testcase):
	nodes = []
	edges = []
	g = Graph()
	n,m = raw_input().split()
	s,t = raw_input().split()
	n , m , s ,t = int(n),int(m),int(s),int(t)
	for  i in range(m):
		x,y,d = raw_input().split()
		d = int(d)
		nodes.append(x)
		nodes.append(y)
		edges.append([x,y,d])
	nodes = sorted(set(nodes))
	for i in nodes:
		g.addNode(i)

	for i in edges:
		g.addEdge(i[0],i[1],i[2])
	liesonsp = []
	g.dijkstra('1' , liesonsp)
	lfa = g.printdijkstra('1')
	for i in lfa:
		if int(i[0]) == n:
			lenofpath = i[1]
			break
	
	print lenofpath
	g.dijkstra(str(n) , liesonsp)
	lft =  g.printdijkstra(n)
	for i in g.printnodes():
		for j in lfa:
			for k in lft:
				if(j[0] == i and k[0]==i):
					if(j[1]+k[1] == lenofpath):
						liesonsp.append(i)
	
	print liesonsp
	g.dijkstra(str(s) , liesonsp)
	
	for i in g.printdijkstra(str(s)):
		if (i[0] == str(t)):
			print i[1]
	testcase = testcase + 1