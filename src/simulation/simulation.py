#!/usr/bin/python

import sys
sys.path.append("../graph")
import graph as G
import math
import random
import csv

#input_pos=[[4,6],[3,5],[4,4],[5,5],[9,9],[8,7],[10,7]] # hardcoded starting positions #
input_pos=[[5,0],[-5,0]]
#input_pos=[[5,0],[-2.5,4.33],[-2.5,-4.33]]

# generator
def drange(start, stop, step):
	r = start
	while r < stop:
		yield r
		r += step

class Vector:

  def __init__(self, xs):
    self.X = xs

  @property
  def dimensionality(self): return len(self.X)

  @property
  def magnitude(self):
    squares = [x * x for x in self.X]
    return math.sqrt(sum(squares))

  # gives the unit vector along the same direction
  @property
  def unit_vector(self):
    magnitude = self.magnitude
    newX = [x / magnitude for x in self.X]
    return Vector(newX)

  # gives a vector of zero magnitude of the dimensionality n.
  @staticmethod
  def zero_vector(n): return Vector([0] * n)

  # gives a random vector of dimensionality n and with maximum coordinate component as max.
  @staticmethod
  def random_vector(n, max):
    v = []
    for i in range(n):
      v.append(random.random() * max)
    return Vector(v)

  def __str__(self):
    return reduce(lambda x, y: x + "/" + str(y) , self.X[1:], str(self.X[0]))

  @property
  def neg(self): return Vector([-x for x in self.X])

  def add(self, v):
    if(v.dimensionality != self.dimensionality):
      raise Exception("Dimensionality mismatch")

    newX = self.X[:]
    for i in range(len(newX)):
      newX[i] += v.X[i]
    return Vector(newX)

  def subtract(self, v): return self.add(v.neg)

  # Give a new vector multiplying self by multiplier k
  def multiply(self, k): return Vector([k * x for x in self.X])

class Snapshot:
  def __init__(self, x, v, a):
    self._x_ = x
    self._v_ = v
    self._a_ = a

  @property
  def position(self):     return self._x_
  @property
  def velocity(self):     return self._v_
  @property
  def acceleration(self): return self._a_

  def set_x(self, x): self._x_ = x

  def set_v(self, v): self._v_ = v

  def set_a(self, a): self._a_ = a

  def __str__(self):
    return "Snapshot(\n" + "    x = " + str(self._x_) + "\n    v = " + str(self._v_) + "\n    a = " + str(self._a_) + ")" 

class Simulation:

  def __init__(self, g, d, b, f, r, a, degree):
    self._graph_          = g
    self._dimensionality_ = d
    self._boundary_       = b
    self._snapshots_      = {}
    self._kr_ = r
    self._ka_ = a
    self._kf_ = f
    self._degree_ = degree
    for n in self._graph_.nodes.keys():
      self._snapshots_[n] = []
    self._timestep_ = 0.1   		# fixed number #
    self._static_friction_ = 0.0001 	# fixed number #
    self._velocity_cutoff_ = 0.00001 	# fixed number #	
  # INITIALISATION
  # Place all the node particles in different randomly generated coordinates.
  # The initial velocities will be 0 for all particles.
    key_ind=0
    for p in self._snapshots_:
      new_x = Vector(input_pos[key_ind])
      # Vector.random_vector(self._dimensionality_, self._boundary_) #
      while(self.is_colliding(new_x, p)):
        new_x = Vector.random_vector(self._dimensionality_, self._boundary_)
      s = Snapshot( new_x, Vector.zero_vector(self._dimensionality_), Vector.zero_vector(self._dimensionality_) )
      self._snapshots_[p].append(s)
      key_ind+=1
    
    # finding intial acceleration of all particles	 
    for p in self._snapshots_:
      self._snapshots_[p][0].set_a(self.acceleration(p))

  def last_x(self, p): return self._snapshots_[p][len(self._snapshots_[p]) - 1]._x_

  def last_v(self, p): return self._snapshots_[p][len(self._snapshots_[p]) - 1]._v_

  def last_a(self, p): return self._snapshots_[p][len(self._snapshots_[p]) - 1]._a_

  # force and acceleration are considered interchangeable by assuming mass = 1
  def acceleration(self, particle):
    # attractive force felt by p1 from p2 due to edge weight
    def attractive_force(p1, p2):
      if(not self._graph_.are_neighbours(p1, p2)):
        return Vector.zero_vector(self._dimensionality_)
      else:
        si = 0 # si is the edgeweight(similarity index) between two neighbouring particles #
        for n, w in self._graph_.nodes[p1]: 
      	  if p2 == n:
            si = w
	for n, w in self._graph_.nodes[p2]:
          if p1 == n:
            si = w

      d = self.last_x(p2).subtract(self.last_x(p1))
      if(d.magnitude==0):  
        return Vector.zero_vector(self._dimensionality_) # if the two particles in question are co-inciding; attractive force between them should be zero #
 
      return d.unit_vector.multiply(si*self._ka_/ (d.magnitude**self._degree_ + 0.1)) # softening the attraction # 
    
    # force felt by p1 from p2 due to electrostatic repulsion
    def repulsive_force(p1, p2):
      d = self.last_x(p1).subtract(self.last_x(p2))
      if(d.magnitude==0):  
        return Vector.zero_vector(self._dimensionality_) # if the two particles in question are co-inciding; repulsive force between them should be zero #
 
      return d.unit_vector.multiply(self._kr_ / (d.magnitude**self._degree_ + 0.1)) # softening the repulsion #

    # frictional force felt by p due to its momentum; accounting for kinetic friction ; low-speed viscous drag considered as Re < 1 considered for particles #
    def frictional_force(p1):
      return self.last_v(p1).multiply(-self._kf_)

    mutual_force = Vector.zero_vector(self._dimensionality_)
    for p in self._snapshots_.keys():
      if(p != particle):
        mutual_force = mutual_force.add(attractive_force(particle, p).add(repulsive_force(particle,p)))
    if(self.last_v(particle) == 0):                         # when particle is stationary; static friction is present #
      if(mutual_force.magnitude > self._static_friction_):
        sf = mutual_force.unit_vecor.multiply(-self._static_friction_)
        mutual_force = mutual_force.add(sf)
        return mututal_force.add(sf)
      else:
        return Vector.zero_vector(self._dimensionality_) 
    
    else:
      return mutual_force.add(frictional_force(particle))    # when particle is moving; drag is present #
  
  def is_colliding(self, x, particle):
    for p in self._snapshots_.keys():
      if(len(self._snapshots_[p]) != 0 and p != particle):
        if(x == self.last_x(p)):
          return True
    return False
  
  def single_step(self):
    new_temp=[]
    for p in self._snapshots_.keys():
      new_v = Vector.zero_vector(self._dimensionality_)
      if( self.last_v(p).add(self.last_a(p).multiply(self._timestep_)).magnitude >= self._velocity_cutoff_):
        new_v =  self.last_v(p).add(self.last_a(p).multiply(self._timestep_))         # new_v = old_v + (old_a*delta(t)) #
      new_x = self.last_x(p).add(new_v.multiply(self._timestep_))                     # new_x = old_x + (old_v*delta(t)) #
      
      s = Snapshot(new_x, new_v, Vector.zero_vector(self._dimensionality_))
      new_temp.append(s)
    
    i=0
    for p in self._snapshots_.keys():
      self._snapshots_[p].append(new_temp[i])
      i+=1
    for p in self._snapshots_:  # update accelration; done after new_x and new_v have beencalculated for all the nodes #
      self._snapshots_[p][-1].set_a(self.acceleration(p))
   
  def simulate(self, n):
    for i in range(1,n):
      self.single_step()
    
  # dumps the x,v,a values into a CSV file
  def to_csv(self, filename):
    with open(filename, 'wb') as csvfile:
      writer = csv.writer(csvfile, delimiter=',')
      for p in self._snapshots_:
        x = [p] + [str(s.position) for s in self._snapshots_[p]]
        writer.writerow(x)
	v = [p] + [str(s.velocity) for s in self._snapshots_[p]]
        writer.writerow(v)
	a = [p] + [str(s.acceleration) for s in self._snapshots_[p]]
        writer.writerow(a)
	
def t1():
  v1 = Vector([1, 2])
  v2 = Vector([2, 3])
  print v1.magnitude
  print v2.unit_vector
  print v2.unit_vector.magnitude
  print v1.add(v2)
  print Vector.zero_vector(v1.dimensionality)

def t2():
  g = G.Graph.empty_graph()
  e1 = G.Edge("n1", 100, "n2")
  e2 = G.Edge("n3", 100, "n2")
  e3 = G.Edge("n1", 200, "n3")

  g.add_edge_list([e1, e2, e3])

  simulation = Simulation(g, 1)
  simulation.simulate(30)

def t3():
  g = G.Graph.empty_graph()
  edge_list = [
    G.Edge("qtytlkkk",1,"vgrovuli"),
    G.Edge("qtytlkkk",1,"vykazeau"),
    G.Edge("qtytlkkk",1,"mcpnjtsk"),
    G.Edge("qtytlkkk",1,"mtxueizs"),
    G.Edge("vgrovuli",1,"mtxueizs"),
    G.Edge("vgrovuli",1,"qtytlkkk"),
    G.Edge("vgrovuli",1,"mcpnjtsk"),
    G.Edge("vgrovuli",1,"vykazeau"),
    G.Edge("vgrovuli",1,"owowvwcr"),
    G.Edge("swnkkroj",1,"owowvwcr"),
    G.Edge("swnkkroj",1,"egaukrej"),
    G.Edge("swnkkroj",1,"xygugclk"),
    G.Edge("swnkkroj",1,"ifjsmbka"),
    G.Edge("swnkkroj",1,"ewolhnma"),
    G.Edge("swnkkroj",1,"jbckijuo"),
    G.Edge("swnkkroj",1,"xfinhuod"),
    G.Edge("swnkkroj",1,"jvflhyko"),
    G.Edge("swnkkroj",1,"uqrksipl"),
    G.Edge("uqrksipl",1,"ifjsmbka"),
    G.Edge("uqrksipl",1,"ewolhnma"),
    G.Edge("uqrksipl",1,"jvflhyko"),
    G.Edge("uqrksipl",1,"egaukrej"),
    G.Edge("uqrksipl",1,"xygugclk"),
    G.Edge("uqrksipl",1,"xfinhuod"),
    G.Edge("uqrksipl",1,"jbckijuo"),
    G.Edge("uqrksipl",1,"swnkkroj"),
    G.Edge("uqrksipl",1,"owowvwcr"),
    G.Edge("uqrksipl",1,"mcpnjtsk"),
    G.Edge("owowvwcr",1,"ewolhnma"),
    G.Edge("owowvwcr",1,"swnkkroj"),
    G.Edge("owowvwcr",1,"jvflhyko"),
    G.Edge("owowvwcr",1,"xygugclk"),
    G.Edge("owowvwcr",1,"egaukrej"),
    G.Edge("owowvwcr",1,"ifjsmbka"),
    G.Edge("owowvwcr",1,"xfinhuod"),
    G.Edge("owowvwcr",1,"uqrksipl"),
    G.Edge("owowvwcr",1,"jbckijuo"),
    G.Edge("egaukrej",1,"uqrksipl"),
    G.Edge("egaukrej",1,"owowvwcr"),
    G.Edge("egaukrej",1,"jbckijuo"),
    G.Edge("egaukrej",1,"swnkkroj"),
    G.Edge("egaukrej",1,"ifjsmbka"),
    G.Edge("egaukrej",1,"xfinhuod"),
    G.Edge("egaukrej",1,"ewolhnma"),
    G.Edge("egaukrej",1,"xygugclk"),
    G.Edge("egaukrej",1,"jvflhyko"),
    G.Edge("mtxueizs",1,"vykazeau"),
    G.Edge("mtxueizs",1,"vgrovuli"),
    G.Edge("mtxueizs",1,"mcpnjtsk"),
    G.Edge("mtxueizs",1,"qtytlkkk"),
    G.Edge("mcpnjtsk",1,"vgrovuli"),
    G.Edge("mcpnjtsk",1,"mtxueizs"),
    G.Edge("mcpnjtsk",1,"vykazeau"),
    G.Edge("mcpnjtsk",1,"qtytlkkk"),
    G.Edge("mcpnjtsk",1,"jbckijuo"),
    G.Edge("jbckijuo",1,"xygugclk"),
    G.Edge("jbckijuo",1,"uqrksipl"),
    G.Edge("jbckijuo",1,"ifjsmbka"),
    G.Edge("jbckijuo",1,"xfinhuod"),
    G.Edge("jbckijuo",1,"jvflhyko"),
    G.Edge("jbckijuo",1,"ewolhnma"),
    G.Edge("jbckijuo",1,"owowvwcr"),
    G.Edge("jbckijuo",1,"qtytlkkk"),
    G.Edge("ifjsmbka",1,"jbckijuo"),
    G.Edge("ifjsmbka",1,"jvflhyko"),
    G.Edge("ifjsmbka",1,"swnkkroj"),
    G.Edge("ifjsmbka",1,"uqrksipl"),
    G.Edge("ifjsmbka",1,"owowvwcr"),
    G.Edge("ifjsmbka",1,"xfinhuod"),
    G.Edge("ifjsmbka",1,"mtxueizs"),
    G.Edge("xfinhuod",1,"swnkkroj"),
    G.Edge("xfinhuod",1,"jbckijuo"),
    G.Edge("xfinhuod",1,"xygugclk"),
    G.Edge("xfinhuod",1,"ifjsmbka"),
    G.Edge("xfinhuod",1,"ewolhnma"),
    G.Edge("xfinhuod",1,"jvflhyko"),
    G.Edge("xfinhuod",1,"uqrksipl"),
    G.Edge("xfinhuod",1,"egaukrej"),
    G.Edge("xygugclk",1,"egaukrej"),
    G.Edge("xygugclk",1,"jbckijuo"),
    G.Edge("xygugclk",1,"xfinhuod"),
    G.Edge("xygugclk",1,"uqrksipl"),
    G.Edge("xygugclk",1,"ewolhnma"),
    G.Edge("xygugclk",1,"ifjsmbka"),
    G.Edge("xygugclk",1,"swnkkroj"),
    G.Edge("xygugclk",1,"mcpnjtsk"),
    G.Edge("xygugclk",1,"vykazeau"),
    G.Edge("ewolhnma",1,"xfinhuod"),
    G.Edge("ewolhnma",1,"uqrksipl"),
    G.Edge("ewolhnma",1,"jbckijuo"),
    G.Edge("ewolhnma",1,"egaukrej"),
    G.Edge("ewolhnma",1,"xygugclk"),
    G.Edge("ewolhnma",1,"ifjsmbka"),
    G.Edge("ewolhnma",1,"swnkkroj"),
    G.Edge("ewolhnma",1,"jvflhyko"),
    G.Edge("ewolhnma",1,"owowvwcr"),
    G.Edge("ewolhnma",1,"mtxueizs"),
    G.Edge("jvflhyko",1,"xfinhuod"),
    G.Edge("jvflhyko",1,"uqrksipl"),
    G.Edge("jvflhyko",1,"egaukrej"),
    G.Edge("jvflhyko",1,"ifjsmbka"),
    G.Edge("jvflhyko",1,"xygugclk"),
    G.Edge("jvflhyko",1,"swnkkroj"),
    G.Edge("jvflhyko",1,"ewolhnma"),
    G.Edge("jvflhyko",1,"jbckijuo"),
    G.Edge("jvflhyko",1,"owowvwcr"),
    G.Edge("jvflhyko",1,"qtytlkkk"),
    G.Edge("jvflhyko",1,"mcpnjtsk"),
    G.Edge("vykazeau",1,"vgrovuli"),
    G.Edge("vykazeau",1,"mcpnjtsk"),
    G.Edge("vykazeau",1,"qtytlkkk")
  ]

  g.add_edge_list(edge_list)

  simulation = Simulation(g, 1, 10)
  simulation.simulate(100)
  simulation.to_csv("output.csv")
 
def t4(dim,f,r,a,degree):
  g = G.Graph.empty_graph()
  edge_list = [
    G.Edge("n1", 1, "n2"),
    #G.Edge("n1", 1, "n3"),
    #G.Edge("n1", 1, "n4"),
    #G.Edge("n2", 1, "n3"),
    #G.Edge("n2", 1, "n4"),
    #G.Edge("n3", 1, "n4"),
    #G.Edge("n5", 1, "n6"),
    #G.Edge("n5", 1, "n7"),
    #G.Edge("n6", 1, "n7"),
    #G.Edge("n4", 1, "n6")
 ]
  #print str(f)+str(r)+str(a)
  g.add_edge_list(edge_list)

  simulation = Simulation(g, dim, 100, f, r, a, degree)
  simulation.simulate(6000)
  file1 = "simulate-csv/degree-"+str(degree)+"/dim-"+str(dim)+"/timestep-"+"0.1"+"/output-2/" + str(f)+"_"+str(r)+"_"+str(a)+".csv"
  simulation.to_csv(file1)
 
if __name__ == "__main__":
	degree = 2
	dim = 2
	for x in drange(1,11,1):
		for y in drange(0,11,1):
			for z in drange(y,11,1):
				f = float(x)
				r = float(y)
				a = float(z)
				print f,r,a  				
				t4(dim,f,r,a,degree)
	
	#t4(dim,0.0,0.0,10.0,degree)
