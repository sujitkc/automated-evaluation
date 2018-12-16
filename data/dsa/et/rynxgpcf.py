graph = {}
node = {}

def push(ls, s):
    ls.append(s)

def addNode(n, index):
    node[n] = index
    graph[n] = []
    return index+1

def addEdge(u, v):
    graph[u].append(v)

def check(s,b):

    ls = []
    stack1 = []
    push(stack1, s)
    color1[node[s]] = 'Y'

    while(stack1):

        u = stack1.pop()
        if(color1[node[u]] == 'Y'):
            ls.append(u)
          #  print "Node Visited : " ,u
            color1[node[u]] = 'B'
            if(len(graph[u]) == 0):
                return []
            for v in graph[u]:
                if(v == b):
                    ls.append(v)
                    return ls
                if(color1[node[v]] == 'R'):
                    push(stack1, v)
                    color1[node[v]] = 'Y'
                elif(color1[node[v]] == 'Y'):
                    push(stack1, v)
                
       # print "Stack state : " ,stack            

    for n in node:
        if(color1[node[n]] == 'R'):
            DFS(n)

    return []

    
def DFS(s):

    stack = []
    push(stack, s)
    pi[s] = None
    color[node[s]] = 'Y'

    while(stack):

        u = stack.pop()
        if(color[node[u]] == 'Y'):
          #  print "Node Visited : " ,u
            color[node[u]] = 'B'
            for v in graph[u]:
                if(color[node[v]] == 'B'):
                    lst = check(v,u)
                    if(len(lst)!=0):
                        print "Cycle Found "
                        lst.append(v)
                        print "Cycle is:"
                        for i in lst:
                            print i

                        return
                if(color[node[v]] == 'R'):
                    push(stack, v)
                    color[node[v]] = 'Y'
                    pi[v] = u
                elif(color[node[v]] == 'Y'):
                    push(stack, v)
                    pi[v] = u

       # print "Stack state : " ,stack            

    for n in node:
        if(color[node[n]] == 'R'):
            DFS(n)

    print "DAG"
    return pi

t = input()

for i in range(t):
    a = map(int,raw_input().split(" "))
    n = a[0]
    m = a[1]
    index = 0

    for j in range(n):
        index = addNode(str(j+1),index)

    for k in range(m):
        a = map(int,raw_input().split(" "))
        addEdge(str(a[0]),str(a[1]))

    pi = {}
    color = []
    color1 = []

    for i in node:
        color.append('R')
        color1.append('R')

    print "Graph : ", graph

    pi = DFS('1')