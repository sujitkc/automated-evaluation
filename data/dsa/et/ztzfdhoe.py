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


        def dijkstra(self, rt):
                root = self.vertices[rt]
                INF = 9999999
                m = Heap(size = self.size, inf = 9999999)
                dist = [INF for i in xrange(self.size)]
                pi = [0 for i in xrange(self.size)]

                m.update(root, 0)
                pi[root] = root
                dist[root] = 0

                for i in xrange(self.size):
                        root = m.extract_top()

                        if dist[root] == 9999999:
                                break

                        for node, wt in self.adjList[root]:
                                if dist[root] + wt < dist[node]:
                                        dist[node] = dist[root] + wt
                                        m.update(node, dist[node])
                                        pi[node] = root
                for i in range(self.size):
                        if(arr[i]<dist[i]):
                                arr[i]=dist[i]
                                
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
        while(t):
                n,m=map(int,raw_input().split(' '))
                g=Graph()
                arr=[-1]*n
                for i in range(n):
                        g.insert_node(str(i))
                for i in range(m):
                        temp1,temp2,weight=map(int,raw_input().split(' '))
                        g.insert_edge(str(temp1-1),str(temp2-1),weight)
                for i in range(n):
                        g.dijkstra(str(i))
                t=t-1
                wei=9999999
                for i in range(n):
                    if arr[i]<wei:
                        wei=arr[i]
                        ans=i
                print wei,ans+1

