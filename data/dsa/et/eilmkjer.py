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

	def dfs_iterative(self, source):
		source = self.vertices[source]
		visit = [True for i in xrange(self.size)]
		stack = [source]
		pi = {source : source}

		while len(stack) != 0:
			c = stack.pop()

			if visit[c]:
				print "Node: ", self.invVertices[c], "\t Pi(", self.invVertices[c], "): ", self.invVertices[pi[c]]

				visit[c] = False

			for n,w in self.adjList[c]:
				if visit[n]:
					stack.append(n)
					pi[n] = c

	def vertices_decreasing_finish_time_visit(self, root, visit, sortedVertices):
		visit[root] = False

		for node, wt in self.adjList[root]:
			if visit[node]:
				self.vertices_decreasing_finish_time_visit(node, visit, sortedVertices)

		sortedVertices.insert(0, root)

	def vertices_decreasing_finish_time(self):
		visit = [True for i in xrange(self.size)]
		sortedVertices = []

		for i in xrange(self.size):
			if visit[i]:
				self.vertices_decreasing_finish_time_visit(i, visit, sortedVertices)

		return sortedVertices

	def get_transpose(self):
		transpose = copy.deepcopy(self)
		transpose.adjList = [[] for i in xrange(transpose.size)]

		for i in xrange(self.size):
			for node, wt in self.adjList[i]:
				transpose.adjList[node].append((i, wt))

		return transpose

	def strongly_connected_components(self):
		transpose = self.get_transpose()
		visit = [True for i in xrange(self.size)]
		scc = []

		for i in self.vertices_decreasing_finish_time():
			if visit[i]:
				l = []
				transpose.vertices_decreasing_finish_time_visit(i, visit, l)
				scc.append(l)
		if len(scc)>0:
			return scc[0]
		else:
			return "DAG"
class UndirectedGraph(Graph):
	def __init__(self):
		Graph.__init__(self)

	def insert_edge(self, node1, node2, wt = 1):
		Graph.insert_edge(self, node1, node2, wt)
		Graph.insert_edge(self, node2, node1, wt)

T = input()
for j in xrange(T):
	n, m = map(int, raw_input().strip().split())
	l = [raw_input().strip().split() for i in xrange(m)]

	if __name__=="__main__":
		a = UndirectedGraph()
		for i in xrange(n):
			a.insert_node(str(i))
		for i in xrange(m):
			a.insert_edge(l[i][0], l[i][1])

		print "\nStrongly Connected Components: "
		print a.strongly_connected_components()