from collections import defaultdict
inf = float('inf')

class Graph:
    def __init__(self,dir):
        self.adjLists = defaultdict(list)
        self.nodeList = defaultdict()
        self.dir = dir

    def addEdge(self, start, end, wt = 1 ):
        try:
            self.nodeList[start]
        except:
            Start = Node(start)
            self.nodeList[start] = Start
        try:
            self.nodeList[end]
        except:
            End = Node(end)
            self.nodeList[end] = End
            self.adjLists[self.nodeList[end]] = []
        self.adjLists[self.nodeList[start]].append((self.nodeList[end],wt))

        if self.dir == 'undirected':
            self.adjLists[self.nodeList[end]].append((self.nodeList[start],wt))

    def topDown(self, heap, index):
        left = 2*index+1
        right = 2*index+2
        # print index,len(heap),heap[index].index
        while right < len(heap):
            j = -1
            if heap[left].weight<heap[right].weight :
                j=left;
            else:
                j=right;
            if heap[index].weight<heap[j].weight :
                break
            else:

                heap[j].index = index
                heap[index].index = j
                t=heap[index];
                heap[index]=heap[j];
                heap[j]=t;
                index=j;
                left=2*index+1;
                right=2*index+2;

        if left == len(heap)-1 and heap[index].weight>heap[left].weight:
            heap[left].index = index
            heap[index].index = left
            k= heap[index]
            heap[index] = heap[left]
            heap[left] = k



    def bottomUp(self, heap, index):
        p = (index-1)/2
        while index > 0 and len(heap)>1:
            # print index,len(heap)
            if heap[index].weight<heap[p].weight:

                heap[p].index = index
                heap[index].index = p
                a = heap[index];
                heap[index]=heap[p];
                heap[p]=a;
                index=p;
                p=(index-1)/2;

            else:
                break



    def delete(self, heap):

        pop = heap[0]
        if len(heap)>2:
            heap[0] = heap.pop()
            heap[0].index = 0
            self.topDown(heap , 0)
        elif len(heap)==2:
            heap[0] = heap.pop()
            heap[0].index=0
        return pop

    def dijkstra(self, rootNode):


        marked = []
        rootNode.mark = True
        rootNode.weight = 0
        heap = list(self.adjLists.keys())

        for i in range(len(heap)):
            heap[i].index = i
            if heap[i] == rootNode:
                self.bottomUp(heap, i)

        while len(marked) != len(self.adjLists.keys()):

            poppedNode = self.delete(heap)
            if rootNode.maxWeight < poppedNode.weight:
                rootNode.maxWeight = poppedNode.weight
            # print poppedNode.value
            for (adj,wt) in  self.adjLists[poppedNode]:
                if adj.weight > (poppedNode.weight + wt):
                    adj.weight = poppedNode.weight + wt
                    self.bottomUp(heap,adj.index)
            marked.append( poppedNode )
            poppedNode.mark = True
            # print poppedNode.value," ",poppedNode.weight,"   ",

        for nd in marked:
            nd.weight = inf
            nd.marked = False

    def test(self):
        for i in self.adjLists.keys():
            self.dijkstra(i)

        # for i in self.adjLists.keys():
        #     print i.value,i.maxWeight

        minimum = inf
        minNode = ""
        for i in self.adjLists.keys():
            if i.maxWeight < minimum:
                minNode = i
                minimum = i.maxWeight
        print minNode.value,"->", minimum

class Node(Graph):
    def __init__(self,value):
        self.value = value
        self.mark = False
        self.weight = inf
        self.index = -1
        self.maxWeight = -1;


if __name__ == '__main__':

    t = input()
    for _ in xrange(t):
        g=Graph('directed')
        [n,m] = raw_input().split(" ")
        for i in xrange(int(m)):
            s=[]
            s = raw_input().split(" ")
            g.addEdge(s[0],s[1],int(s[2]))

        g.test ()

    # g=Graph('directed')
    # g.addEdge(1,2,4)
    # g.addEdge(2,3,1)
    # g.addEdge(2,4,3)
    # g.addEdge(4,5,7)
    # g.addEdge(3,5,8)
    # g.addEdge(3,6,1)
    # g.addEdge(5,1,3)
    # g.test ()
