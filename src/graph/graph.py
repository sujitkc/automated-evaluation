#!/usr/bin/python
import random
import string

# Adjacency List - start
## Graph - start

class Edge:
  def __init__(self, n1, w, n2):
    self._start_ = n1
    self._weight_  = w
    self._end_ = n2

  def __str__(self):
    return "Edge(" + str(self._start_) + "," + str(self._weight_) + "," + str(self._end_) + ")"

  @property 
  def start_node(self): return self._start_
  @property
  def end_node(self):   return self._end_
  @property
  def weight(self):     return self._weight_

class Graph:
  @staticmethod
  def empty_graph():     return Graph([])

  def __init__(self, edges):
    self._nodes_ = {}
    self.add_edge_list(edges)

  @property
  def nodes(self): return self._nodes_

  @property
  def edges(self):
    edges = []
    for n in self.nodes:
      for (n1, w) in self.nodes[n]:
        edges.append(Edge(n1 = n, w = w, n2 = n1))
    return edges

  def __str__(self):
    s = "Graph(\n"
    for e in self.edges:
      s += "  " + str(e) + ",\n"
    s += ")"
    return s

  def are_neighbours(self, n1, n2):
    if(n1 == n2):
      return False
    for n, w in self.nodes[n1]:
      if n2 == n:
        return True
    for n, w in self.nodes[n2]:
      if n1 == n:
        return True
 
    return False

  def add_edge(self, e):
    #_add_edge_to_edge_list adds an edge to a given edge list.
    # ensures not to add duplicate edges (i.e. edges with identical
    # start and end nodes; adds the weight in that case.
    def _add_edge_to_edge_list(el, (n, w)):
      for i in range(len(el)):
        (n1, w1) = el[i]
        if(n1 == n):
          el[i] = (n, w + w1)
          return
      el.append((n, w))

    if(not e.start_node in self.nodes):
      self.nodes[e.start_node] = []
    if(not e.end_node in self.nodes):
      self.nodes[e.end_node] = []
    edge_list = self.nodes[e.start_node]
    _add_edge_to_edge_list(edge_list, (e.end_node, e.weight))

  def add_edge_list(self, el):
    for e in el:
      self.add_edge(e)

  def generate_new_node_name(self):
    while(True):
      rn = ''.join(random.choice(string.lowercase) for i in range(8))
      if(rn not in self.nodes):
        return rn
 
  # merge g into self. self gets modified. g remains unchanged.
  def merge(self, g):
     
    new_node_names = {}
    def clone_edge(e):
      if(e.start_node not in new_node_names):
        new_node_names[e.start_node] = self.generate_new_node_name()
      if(e.end_node not in new_node_names):
        new_node_names[e.end_node]   = self.generate_new_node_name()
      n1 = new_node_names[e.start_node]
      n2 = new_node_names[e.end_node]
      w  = e.weight
      return Edge(n1, w, n2)

    for e in g.edges:
      self.add_edge(clone_edge(e))

   
## Graph - end
# Adjacency List - end

if __name__ == "__main__":
  e1 = Edge("n1", 100, "n2")
  e2 = Edge("n3", 100, "n2")
  e3 = Edge("n1", 200, "n3")

  g = Graph.empty_graph()
  print g
  g.add_edge_list([e1, e2, e3])
  for e in g.edges:
    print e
