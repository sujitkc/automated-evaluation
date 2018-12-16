#!/usr/bin/python

import random
import graph as G
# create a graph with n nodes, and with density * n * (n - 1) edges.
# Works similar to create_complete_graph, except that, in the end, it
# removes a few edges to make the edge density 'density'.
def create_dense_graph(n, density):
  g = G.Graph.empty_graph()
  nodes = []
  for i in range(n):
    nodes.append(g.generate_new_node_name())

  pairs = [(n1, n2) for n1 in nodes for n2 in nodes]
  edges = [G.Edge(n1, 1, n2) for (n1, n2) in pairs if n1 != n2]
  random.shuffle(edges)
  if(density != 1):
    edges = edges[ : int(-((1 - density) * len(edges)))]
  for e in edges:
    g.add_edge(e)
  return g

# create a complete graph with n nodes
def create_complete_graph(n):
  return create_dense_graph(n, 1)

# return a graph with len(nlist) complete graphs. Each complete graph has
# n1, n2 ... nodes where nlist = [n1, n2, ...]
def create_clusters(nlist, create_graph):
  g = G.Graph.empty_graph()
  for n in nlist:
    newg = create_graph(n)
    g.merge(newg)
  return g

# Given a graph g, modify g so that it has some edges (n of them) added to it randomly.
def add_random_edges(g, n):
  if(len(g.nodes) < 2):
    raise Exception("Can't add edges in a graph with fewer than two nodes.")
  # find non-neighbour node pairs.
  def find_non_neighbour_pair():
    nodes = g.nodes.keys()
    random.shuffle(nodes)
    i = 0
    while(i < len(nodes) - 1):
      (n1, n2) = (nodes[i], nodes[i + 1])
      if(not g.are_neighbours(n1, n2)):
        return (n1, n2)
      i += 1
    raise Exception("Couldn't find any non-neighbours in this graph.")

  i = 0
  while(i < n):
    (n1, n2) = find_non_neighbour_pair()
    g.add_edge(G."n1", 1, "n2")
    i += 1

####### test cases ###########
def t1():
  g = create_complete_graph(10)
  print len(g.nodes)
  print len(g.edges)
  print(g)

# This test case creates a cluster with 3 dense graphs each with 5, 10, 3 nodes
# respectively and all with edge density (0.9).
# Further, it adds 10 edges to the graph.
def t2():
  density = 0.9
  cluster = create_clusters([5, 10, 3], lambda g: create_dense_graph(g, density))
  print(cluster)
  print len(cluster.nodes)
  print len(cluster.edges)
  add_random_edges(cluster, 10)
  print len(cluster.nodes)
  print len(cluster.edges)
  print(cluster)

if __name__ == "__main__":
  t1()
  t2()
