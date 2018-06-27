#!/usr/bin/python

import sys
sys.path.append("../graph")
import graph as G
import math
import random
import csv
import hdbscan
import numpy as np
from matplotlib import pyplot as plt

#input_pos=[[5,0],[-5,0]]
#input_pos=[[5,0],[-2.5,4.33],[-2.5,-4.33]]
#input_pos=[[5,0],[0,5],[-5,0],[0,-5]]
input_pos=[[4.29583523987,3.83683406432],[4.92562756335,4.86005461296],[3.21439070921,4.236325461],[0.127014150292,-4.89076061297],[3.22026991339,1.47522298923],[2.16286082227,1.25997103708],[4.32061587194,3.38473137874],[0.0811084308883,2.76575195045],[0.280914008349,2.06911478313],[2.14989768887,3.05996808334]]


################ GENERATOR ######################
def drange(start, stop, step):
	r = start
	while r < stop:
		yield r
		r += step






################ CLASS VECTOR ###################

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






############### CLASS SNAPSHOT ################

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









################ CLASS SIMULATION ######################

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
      #new_x = Vector.random_vector(self._dimensionality_, self._boundary_) #
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
    for i in range(1,n+1):
      self.single_step()
      if i%5 == 0:
        check(self,i)		# calls to check whether the simulation needs to be stopped #
    
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








################# SAMPLE GRAPHS ###################
	
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
    G.Edge("n1", 1, "n3"),
    G.Edge("n1", 1, "n4"),
    G.Edge("n2", 1, "n3"),
    G.Edge("n2", 1, "n4"),
    G.Edge("n3", 1, "n4"),
    G.Edge("n5", 1, "n6"),
    G.Edge("n5", 1, "n7"),
    G.Edge("n6", 1, "n7"),
    G.Edge("n8", 1, "n9"),
    G.Edge("n8", 1, "n10"),
    G.Edge("n9", 1, "n10")
    ]
  #print str(f)+str(r)+str(a)
  g.add_edge_list(edge_list)
  #print g.nodes
  initialisation(g)
  simulation = Simulation(g, dim, 5, f, r, a, degree)
  simulation.simulate(2000)
  file1 = "simulate-csv/degree-"+str(degree)+"/dim-"+str(dim)+"/timestep-"+"0.1"+"/output-10/" + str(f)+"_"+str(r)+"_"+str(a)+".csv"
  #simulation.to_csv(file1)











################## STOPPING ALGORITHM ####################

# DICTIONARY TO TRACK ALL THE SNAPSHOTS OF ALL THE NODES #
nodes_r={}			# key=node; value=list(snapshots(x)) :: tracks position #
nodes_v={}			# key=node; value=list(snapshots(v)) :: tracks velocity #
nodes_a={}			# key=node; value=list(snapshots(a)) :: tracks acceleration #

separation_values = []		# tracks cluster separation value at each check step #
cohesion_values = []		# tracks cluster cohesion value at each check step #
check_points = []		# tracks step value at which checks were performed #
variance = []			# tracks variance values at each step #
F1 = []				# tracks flag_s values at each step #
F2 = []				# tracks flag_c values at each step #

# when F1[index] and F2[index] = True we can then safely stop the simulation #
	
def initialisation(g):			#initialising empty lists of r,v,a for each node in the position,velocity and acceleration dictionary #
	for n in g.nodes.keys():
      		nodes_r[n] = []			
		nodes_v[n] = []
		nodes_a[n] = []
	
def check(obj_simulation,index):
  	check_points.append(index)
	for p in obj_simulation._snapshots_:
		nodes_r[p].append(obj_simulation.last_x(p).X)
		nodes_v[p].append(obj_simulation.last_v(p).X)
		nodes_a[p].append(obj_simulation.last_a(p).X)
	
	# pulling out points for the clustering algorithm #
	snapshot_points = []
	for p in nodes_r:
		snapshot_points.append(nodes_r[p][-1])
	
	clusterer = hdbscan.HDBSCAN(min_cluster_size=2)		# HDBSCAN USED FOR CLUSTERING #
	clusterer.fit(snapshot_points)
	print "Step Number : " + str(index)
	print clusterer.labels_
	
	# cluster separation & cohesion calculations #
	c_num = clusterer.labels_.max() + 1 	# no of clusters formed #
	n_num = 0				# no of outliers #
	for e in clusterer.labels_:
			if e==-1:
				n_num=n_num+1
	
	clusters = {}				# contains positions of data points grouped by cluster label#
	centers = [0]*(c_num+n_num)		# contains poistions of cluster centers and outlier positions #
	k = 0					# controls index of 'centers' #
	for i in range(-1,c_num):
		clusters[i]=[]
		if i != -1:			# finds cluster centers #		
			j=0
			center_x=[]
			center_y=[]
			for e in clusterer.labels_:
				if e==i:
					center_x.append(snapshot_points[j][0])
					center_y.append(snapshot_points[j][1])
					clusters[i].append( [snapshot_points[j][0],snapshot_points[j][1]] )
				j=j+1
			centers[k] = [ (sum(center_x)/float(len(center_x))) , (sum(center_y)/float(len(center_y))) ]
			k=k+1
		else:				# adds outliers as it is #
			j=0				
			for e in clusterer.labels_:
				if e==i:
					centers[k] = [ snapshot_points[j][0] , snapshot_points[j][1] ]
					clusters[i].append( [snapshot_points[j][0],snapshot_points[j][1]] )
					k=k+1						
				j=j+1
	
	
	separation = 0				# calculate cluster separation #
	for i in range(0,len(centers)):
		for j in range(i+1,len(centers)):
			separation = separation + ( ((centers[i][0]-centers[j][0])**2) + ((centers[i][1]-centers[j][1])**2) )**0.5 
	separation_values.append(separation)
	
	cohesion = 0				# calculate cluster cohesion #
	for cluster in clusters:	
		if(cluster==-1):
			for i in range(0,len(clusters[cluster])):
					cohesion = cohesion + ( (clusters[cluster][i][0]**2) + (clusters[cluster][i][1]**2) )**0.5 
		else:
			'''			
			for i in range(0,len(clusters[cluster])):
				for j in range(i+1,len(clusters[cluster])):
					cohesion = cohesion + ( ((clusters[cluster][i][0]-clusters[cluster][j][0])**2) + ((clusters[cluster][i][1]-clusters[cluster][j][1])**2) )**0.5 
			'''
			for i in range(i,len(clusters[cluster])):
				cohesion = cohesion + ( ((clusters[cluster][i][0]-centers[n_num+cluster][0])**2) + ((clusters[cluster][i][1]-centers[n_num+cluster][1])**2) )**0.5 
				
	cohesion_values.append(cohesion)
			
	# CHECKS TO SEE IF WE HAVE REACHED THE STOPPING POINT #
	if len(separation_values) >= 50 :		# taking 50 check points for stablitiy consideration(250 in total); smaller points considered then faster is the stopping algo #
		f=np.array(separation_values[-50:],dtype=float)
		flag1 = all(f[i]<=f[i+1] for i in range(len(f)-1))
		gradient = np.gradient(f,5)		# difference between 2 consecutive check points = 5 units #
		flag2 = all(gradient[i]>=gradient[i+1] for i in range(len(gradient)-1))
		flag_s = flag1 and flag2
		F1.append(flag_s)			
	else:
		F1.append(False)


	if len(cohesion_values) >= 50 :
		f=np.array(cohesion_values[-50:],dtype=float)
		var = np.var(f)	
		variance.append(var)		
		flag_c = all(e<0.5 for e in variance[-100:])
		F2.append(flag_c) 
	else:
		variance.append(1)
		F2.append(False)	
	print "\n"

	
if __name__ == "__main__":
	degree = 2
	dim = 2
	'''	
	for x in drange(1,11,1):
		for y in drange(0,11,1):
			for z in drange(y,11,1):
				f = float(x)
				r = float(y)
				a = float(z)
				print f,r,a  				
				t4(dim,f,r,a,degree)
	'''
	t4(dim,3.0,4.0,5.0,degree)
	plt.subplot(3,1,1)	
	plt.plot(check_points,separation_values,'.')
	plt.plot(check_points,separation_values)
	plt.subplot(3,1,2)
	plt.plot(check_points,cohesion_values,'.')
	plt.plot(check_points,cohesion_values)
	plt.subplot(3,1,3)	
	#plt.plot(check_points,F1,'.')
	plt.plot(check_points,F1)	
	#plt.plot(check_points,F2,'.')
	plt.plot(check_points,F2)
		
	plt.show()	
	plt.close()
	#t4(dim,0.0,0.0,10.0,degree)
