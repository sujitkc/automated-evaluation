
G = { 1:[2], 2:[3], 3:[4], 4:[5], 5:[]}


def cycle_exists(G):                     
    color = { u : "white" for u in G  }  
    found_cycle = [False]                                                                                       
    for u in G:
        #print u
        if color[u] == "white":
            dfs_visit(G, u, color, found_cycle)
        if found_cycle[0]:
            break
    return found_cycle[0]

def dfs_visit(G, u, color, found_cycle):
    if found_cycle[0]:                          
        return
    color[u] = "grey"
    #print "u", u,color[u]
    for v in G[u]:                              
        if color[v] == "grey":
            #print "v", v,color[v]
            found_cycle[0] = True       
            return
        if color[v] == "white":
            #print "v", v,color[v]
            dfs_visit(G, v, color, found_cycle)
    color[u] = "black"
    #print "u", u, color[u]

if cycle_exists(G):
    print "cycle found"
else:
    print "DAG"
