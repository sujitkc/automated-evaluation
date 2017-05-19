class Heap:

    def __init__(self, size, default, marked = {}):
        self.pos = [i for i in range(size)]
        self.heap = [[i, default] for i in range(size)]
        # print self.heap
        self.size = size

    def parent(self, n):
        return (n-1)/2

    def left(self, n):
        return 2*n + 1

    def right(self, n):
        return 2*n + 2

    def compare(self, a, b):
        return (a < b)                  # To get max heap change this to (a > b)

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

    def __init__(self, d):
        self.node = {}
        self.invVertices = []
        self.adjList = []
        self.b = d

    def addNode(self, n):
        self.invVertices.append(n)
        self.node[n] = len(self.node)
        self.adjList.append([])

    def addEdge(self, u, v, w):
        self.adjList[self.node[u]].append((self.node[v], w))

    def dijkstra(self, s):

        val = {}
        root = self.node[s]
        size = len(self.node)
        my_infinity = float('INF')
        h = Heap(size, my_infinity, self.b)
        # print h.heap
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
                if(dist[node] > dist[root] + w):
                    dist[node] = dist[root] + w
                    h.alter(node, dist[node])
                    pi[node] = root

        for i in range(size):
            if(dist[i] != my_infinity):
                val[self.invVertices[i]] =  dist[i]
                # print self.invVertices[i], dist[i]

        return val


g = Graph({})

g.addNode(1)
g.addNode(2)
g.addNode(3)
g.addNode(4)
g.addNode(5)

g.addEdge(1, 2, 1)
g.addEdge(2, 3, 2)
g.addEdge(1, 4, 3)
g.addEdge(2, 4, 4)
g.addEdge(4, 5, 5)
g.addEdge(5, 3, 6)
g.addEdge(5, 2, 7)

g.addEdge(2, 1, 1)
g.addEdge(3, 2, 2)
g.addEdge(4, 1, 3)
g.addEdge(4, 2, 4)
g.addEdge(5, 4, 5)
g.addEdge(3, 5, 6)
g.addEdge(2, 5, 7)

d1 = g.dijkstra(1)
ls = []
src = {}

for i in d1:
    ls.append(g.dijkstra(i))

k = 0
for i in ls:
    for j in i:
        if(i[j] == 0):
            src[j] = k
            k = k + 1

pm_dist = input()

b = {}
for i in ls:
    for j in i:
        if(j != 0):
            l1 = j
            for l2 in ls[src[l1]]:
                if(l2 !=0 and l1 + l2 == pm_dist):
                    b[l1] = True

print b

g1 = Graph(b)
g1.addNode(1)
g1.addNode(2)
g1.addNode(3)
g1.addNode(4)
g1.addNode(5)

g1.addEdge(1, 2, 1)
g1.addEdge(2, 3, 2)
g1.addEdge(1, 4, 3)
g1.addEdge(2, 4, 4)
g1.addEdge(4, 5, 5)
g1.addEdge(5, 3, 6)
g1.addEdge(5, 2, 7)

g1.addEdge(2, 1, 1)
g1.addEdge(3, 2, 2)
g1.addEdge(4, 1, 3)
g1.addEdge(4, 2, 4)
g1.addEdge(5, 4, 5)
g1.addEdge(3, 5, 6)
g1.addEdge(2, 5, 7)

# print g1.dijkstra(1)
