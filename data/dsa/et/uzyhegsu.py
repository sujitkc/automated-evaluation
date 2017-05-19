class Graph:
	def __init__(self):
		self.vertex={}
		self.adjlist=[]
		self.reverse={}

	def insertnode(self,name):
		self.reverse[len(self.vertex)]=name
		self.vertex[name] = len(self.vertex)
		self.adjlist.append([])
		dictionary[name]=0

	def insertedge(self,source,destination,weight=1):
		if source not in self.vertex:
			self.insertnode(source)
		if destination not in self.vertex:
			self.insertnode(destination)
		self.adjlist[self.vertex[source]].append((self.vertex[destination],weight))

	def Dijkstra(self,rt):
		root=self.vertex[rt]
		size=len(self.vertex)
		INF=float('inf')
		minheap=Heap(size,INF)
		distance=[INF for i in range(size)]
		pi=[0 for i in range(size)]
		minheap.Update(root,0)
		pi[root]=root
		distance[root]=0
		for i in range(size):
			root=minheap.Extract()
			if distance[root]==INF:
				break

			for node,wt in self.adjlist[root]:
				if distance[root]+wt<distance[node]:
					distance[node]=distance[root]+wt
					minheap.Update(node,distance[node])
					pi[node]=root

		d={}
		for i in range(size):
			d[self.reverse[i]]=distance[i]

		for k in d:
			if(dictionary[k]<d[k]):
				dictionary[k]=d[k]

class Heap:
	def __init__(self,size,inf,isMin=True):
		self.pos=[i for i in range(size)]
		self.heap=[[i,inf]for i in range(size)]
		self.size=size
		self.isMin=isMin

	@staticmethod
	def Left(i):
		return 2*i+1

	@staticmethod
	def Right(i):
		return 2*i+2

	@staticmethod
	def Parent(i):
		return (i-1)/2

	def Compare(self,a,b):
		return (a<b if self.isMin else a>b)

	def Swap(self,i,j):
		self.pos[self.heap[i][0]]=j
		self.pos[self.heap[j][0]]=i
		self.heap[i],self.heap[j]=self.heap[j],self.heap[i]

	def TopDownHeapify(self,i):
		l=Heap.Left(i)
		r=Heap.Right(i)
		j=i
		while r<self.size:
			j=l if self.Compare(self.heap[l][1],self.heap[r][1]) else r
			if self.Compare(self.heap[i][1],self.heap[j][1]):
				break
			else:
				self.Swap(i,j)
				i=j
				l=Heap.Left(i)
				r=Heap.Right(i)
		if l==self.size-1 and self.Compare(self.heap[l][1],self.heap[j][1]):
			self.Swap(l,j)

	def BottomUpHeapify(self,i):
		p=Heap.Parent(i)
		while p>=0:
			if self.Compare(self.heap[i][1],self.heap[p][1]):
				self.Swap(i,p)
				i=p
				p=Heap.Parent(i)
			else:
				break

	def Update(self,i,newVal):
		if self.Compare(newVal,self.heap[self.pos[i]][1]):
			self.heap[self.pos[i]][1]=newVal
			self.BottomUpHeapify(self.pos[i])
		else:
			self.heap[self.pos[i]][1]=newVal
			self.TopDownHeapify(self.pos[i])

	def Extract(self):
		returnVal=self.heap[0][0]
		self.size-=1
		self.Swap(0,self.size)
		self.TopDownHeapify(0)
		return returnVal



if __name__=="__main__":
	for _ in range(input()):
	
		dictionary={}
		G=Graph()
		n,m=map(int,raw_input().split())
		for i in range(m):
		   n1,n2,w=map(int,raw_input().split())
	           G.insertedge(n1,n2,w)
		for i in G.vertex:
			G.Dijkstra(i)

		Min=float('inf')
		node='A'
		for k in dictionary:
			if dictionary[k]<Min:
				Min=dictionary[k]
				node=k

		#print ""
		#print dictionary
		if Min==float('inf'):
			print -1
		else:
			print node," ",Min
