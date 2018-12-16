import copy

class Graph:
	def __init__(self):
		self.vertices = {}
		self.invVertices = []
		self.adjList = []
		self.size = 0
		self.hosp=[]
		self.checkfull=[]

	def insert_node(self, name):
		self.invVertices.append(name)
		self.vertices[name] = self.size
		self.adjList.append([])
		self.hosp.append([])
		self.checkfull.append(0)
		self.size += 1

	def insert_edge(self, src, dest, weight = 1):
		self.adjList[self.vertices[src]].append((self.vertices[dest], weight))


	def dijkstra(self, rt):
		root = self.vertices[rt]
		INF = float('inf')
		m = Heap(size = self.size, inf = INF)
		dist = [INF for i in xrange(self.size)]
		pi = [0 for i in xrange(self.size)]

		m.update(root, 0)
		pi[root] = root
		dist[root] = 0

		for i in xrange(self.size):
			root = m.extract_top()

			if dist[root] == INF:
				break

			for node, wt in self.adjList[root]:
				if dist[root] + wt < dist[node]:
					dist[node] = dist[root] + wt
					m.update(node, dist[node])
					pi[node] = root

		for i in xrange(self.size):
			if dist[i] != INF:
				print "Node: ", self.invVertices[i],"\tDistance: ",dist[i],"\tPi(",self.invVertices[i],"): ",self.invVertices[pi[i]]
			else:
				self.checkfull[int(rt)]=-1
		for i in xrange(self.size):
			self.hosp[i].append(dist[i])


	def printhosp(self):
		for i in range(self.size):
			print self.hosp[i]


	def printhospnode(self):
		count=0
		for i in range(self.size):
			if(self.checkfull[i]==-1):
				count=count+1
		print count
		if(count==self.size):
			print -1
		else:
			max=[0]*self.size
			for i in range(self.size):
				for j in self.hosp[i]:
					if max[i]<j:
						max[i]=j
			min=max[0];
			mini=0;
			for i in range(self.size):
				if min>max[i]:
					min=max[i]
					mini=i
			print mini
			print self.hosp[mini]


class UndirectedGraph(Graph):
	def __init__(self):
		Graph.__init__(self)

	def insert_edge(self, node1, node2, wt = 1):
		Graph.insert_edge(self, node1, node2, wt)
		#Graph.insert_edge(self, node2, node1, wt)

	

class Heap:
	@staticmethod
	def parent(n):
		return (n-1)/2

	@staticmethod
	def left(n):
		return 2*n + 1

	@staticmethod
	def right(n):
		return 2*n + 2

	def compare(self, a, b):
		return (a < b if self.isMin else a > b)

	def swap(self, i, j):
		self.pos[self.heap[i][0]] = j
		self.pos[self.heap[j][0]] = i
		self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

	def __init__(self, size, inf, isMin = True):
		self.pos = [i for i in xrange(size)]
		self.heap = [[i, inf] for i in xrange(size)]
		self.size = size
		self.isMin = isMin

	def update(self, i, newVal):
		if self.compare(self.heap[self.pos[i]][1], newVal):
			self.heap[self.pos[i]][1] = newVal
			self.top_down_heapify(self.pos[i])

		else:
			self.heap[self.pos[i]][1] = newVal
			self.bottom_up_heapify(self.pos[i])

	def extract_top(self):
		retVal = self.heap[0][0]
		self.size -= 1
		self.swap(0, self.size)
		self.heap.pop()
		self.top_down_heapify(0)
		return retVal

	def top_down_heapify(self, i):
		l = Heap.left(i)
		r = Heap.right(i)
		j = i

		while r < self.size:
			j = l if self.compare(self.heap[l][1], self.heap[r][1]) else r

			if self.compare(self.heap[i][1], self.heap[j][1]):
				break

			else:
				self.swap(i, j)
				i = j
				l = Heap.left(i)
				r = Heap.right(i)

		if l == self.size - 1 and self.compare(self.heap[l][1], self.heap[j][1]):
			self.swap(l, j)

	def bottom_up_heapify(self, i):
		p = Heap.parent(i)
		while(p >= 0):
			if self.compare(self.heap[i][1], self.heap[p][1]):
				self.swap(i, p)
				i = p
				p = Heap.parent(i)

			else:
				break

if __name__ == "__main__":
	a = UndirectedGraph()
	n=input("enter n:")
	m=input("enter m:")
	for i in range(n):
		a.insert_node(str(i))


	for i in range(m):
		x=input()
		y=input()
		w=input()
		a.insert_edge(str(x-1),str(y-1),w)



	print "\nDijkstra:"
	for i in range(n):
		a.dijkstra(str(i));
	a.printhosp()
	a.printhospnode()
