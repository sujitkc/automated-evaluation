#creating graph

graph={1:[2,3],2:[1,3,4],3:[1,2,4,5],4:[2,3,6],5:[3,6],6:[4,5]}



visited=[]              #empty list
queue=[]
queue.append(1)
visited.append(1)                   #insert first key to visited list


#breadth first traversal

while len(queue)!=0:
    del_queue=queue.pop(0)
    print del_queue,
    for neighbour in range(len(graph[del_queue])):
            if graph[del_queue][neighbour] not in visited:
                visited.append(graph[del_queue][neighbour])
                queue.append(graph[del_queue][neighbour])
                

