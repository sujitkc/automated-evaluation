import copy

class Graph:
	def __init__(self):
		self.vertices = {}
		self.invVertices = []
		self.adjList = []
		self.size = 0

	def insert_node(self, name):
		self.invVertices.append(name)
		self.vertices[name] = self.size
		self.adjList.append([])
		self.size += 1
		self.state=[False]*self.size

	def insert_edge(self, src, dest, weight = 1):
		self.adjList[self.vertices[src]].append((self.vertices[dest], weight))

	def dijkstra(self, s, d):
		root = self.vertices[s]
		destin = self.vertices[d]
		INF = float('inf')
		m = Heap(size = self.size, inf = INF)
		dist = [INF for i in xrange(self.size)]
		pi = [0 for i in xrange(self.size)]

		m.update(root, 0)
		pi[root] = root
		dist[root] = 0
		for i in xrange(self.size):
			root = m.extract_top()
			if self.state[root-1]==False:
				if dist[root] == INF:
					break
				for node, wt in self.adjList[root]:
					if dist[root] + wt < dist[node]:
						dist[node] = dist[root] + wt
						m.update(node, dist[node])
						pi[node] = root

		return dist[destin]

	def check(self):
		for i in range(1,self.size):
			if a.dijkstra(1,i)+a.dijkstra(i,self.size) == a.dijkstra(1,self.size):
				self.state[i]=True

class UndirectedGraph(Graph):
	def __init__(self):
		Graph.__init__(self)

	def insert_edge(self, node1, node2, wt = 1):
		Graph.insert_edge(self, node1, node2, wt)
		Graph.insert_edge(self, node2, node1, wt)

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
	t=input()
	for i in range(t):
		a=UndirectedGraph()

		inp=raw_input()
		n=int(inp.split(" ")[0])
		m=int(inp.split(" ")[1])

		inp=raw_input()
		s=int(inp.split(" ")[0])
		t=int(inp.split(" ")[1])

		for j in range(1,n+1):
			a.insert_node(j)

		for j in range(m):
			inp=raw_input()
			x=int(inp.split(" ")[0])
			y=int(inp.split(" ")[1])
			d=int(inp.split(" ")[2])
			a.insert_edge(x,y,d)

		a.check()
		val = a.dijkstra(s,t)
		if(val==float("inf")):
			print "not possible"
		else:
			print val	

	'''
	a = UndirectedGraph()

	a.insert_node('A')
	a.insert_node('B')
	a.insert_node('C')
	a.insert_node('D')
	a.insert_node('E')
	a.insert_node('F')
	a.insert_node('G')
	a.insert_node('H')
	a.insert_node('I')

	a.insert_edge('A', 'B', 4)
	a.insert_edge('B', 'C')
	a.insert_edge('D', 'B', 3)
	a.insert_edge('E', 'D', 7)
	a.insert_edge('E', 'C', 8)
	a.insert_edge('C', 'F')
	a.insert_edge('E', 'A', 3)

	print "Dijkstra:",
	print a.dijkstra('A','D')
	'''