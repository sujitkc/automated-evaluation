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

	def insert_edge(self, src, dest, weight = 1):
		self.adjList[self.vertices[src]].append((self.vertices[dest], weight))

	

	
class UndirectedGraph(Graph):
	def __init__(self):
		Graph.__init__(self)

	def insert_edge(self, node1, node2, wt = 1):
		Graph.insert_edge(self, node1, node2, wt)
		Graph.insert_edge(self, node2, node1, wt)


	def span_forest_kruskal(self, isMin = True):
		edgeList = []

		for i in xrange(self.size):
			for node, wt in self.adjList[i]:
				if node >= i:
					edgeList.append((i, node, wt))

		sorted(edgeList, key = lambda x: x[2], reverse = isMin)

		spanForest = [[] for i in xrange(self.size)]
		getComp = [i for i in xrange(self.size)]
		sizeComp = [1 for i in xrange(self.size)]

		for curredge in edgeList:
			if getComp[curredge[0]] != getComp[curredge[1]]:
				minSizeComp = getComp[curredge[0]]
				maxSizeComp = getComp[curredge[1]]
				if sizeComp[minSizeComp] > sizeComp[maxSizeComp]:
					minSizeComp, maxSizeComp = maxSizeComp, minSizeComp

				for edge in spanForest[minSizeComp]:
					getComp[edge[0]] = maxSizeComp
					getComp[edge[1]] = maxSizeComp

				sizeComp[maxSizeComp] += sizeComp[minSizeComp]
				sizeComp[minSizeComp] = 0

				spanForest[maxSizeComp].append(curredge)
				getComp[curredge[0]] = maxSizeComp
				getComp[curredge[1]] = maxSizeComp

				spanForest[minSizeComp] = []

		for tree in spanForest:
			if tree:
				print "Tree:"
				for edge in tree:
					print "Node 1: ",self.invVertices[edge[0]],"\tNode 2: ",self.invVertices[edge[1]],"\tEdge Weight: ",edge[2]

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

	a.insert_node('1')
	a.insert_node('2')
	a.insert_node('3')
	a.insert_node('4')
	a.insert_node('0')
	
	
	a.insert_edge('1', '2', 3)
	a.insert_edge('3', '4', 5)
	a.insert_edge('2', '3', 10)
	a.insert_edge('4', '0', 4)

	
	print "\nMinimum Span Forest Kruskal's:"
	a.span_forest_kruskal()

	print "\nMaximum Span Tree Kruskal's:"
	a.span_forest_kruskal(False)

	