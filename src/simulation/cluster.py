import csv
import glob
import sys
import hdbscan
from matplotlib import pyplot as plt


csv.field_size_limit(sys.maxsize)

for doc in glob.glob('simulate-csv/degree-2/dim-2/timestep-0.1/output-10/3.0_4.0_5.0.csv'): #"output_test.csv"):#
	data=[]
	print doc
	with open(doc, 'rb') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=' ')
		for row in spamreader:
			data.append([','.join(row)])
	#print data[5]#[0].split(',')
	
	l = len(data)			# number of nodes #
	
	nodes_r={}			# key=node; value=list(snapshots(x)) :: tracks position #
	nodes_v={}			# key=node; value=list(snapshots(v)) :: tracks velocity #
	nodes_a={}			# key=node; value=list(snapshots(a)) :: tracks acceleration #

	for i in range(0,l,3):
		n = data[i][0].split(',')
		nodes_r[n[0]] = n[1:]
	
	for i in range(1,l,3):
		n = data[i][0].split(',')
		nodes_v[n[0]] = n[1:]
	
	for i in range(2,l,3):
		n = data[i][0].split(',')
		nodes_a[n[0]] = n[1:]
	
	points = []

	for keys in nodes_r:
		x=[]
		y=[]
		for e in nodes_r[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))		
					
		points.append([x,y])
	#print points[0][1][0]
	seperation_values = []
	cohesion_values = []
	for i in range(00,len(nodes_r['n1']),100):
		snapshot_points = []
		for j in range(0,len(points)):
			snapshot_points.append( [ points[j][0][i] , points[j][1][i] ] )
		
		clusterer = hdbscan.HDBSCAN(min_cluster_size=2)
		clusterer.fit(snapshot_points)
		
		print "Step Number : " + str(i)
		print clusterer.labels_
		#print snapshot_points
		# cluster seperation-cohesion calculations #
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
		seperation = 0	
		for i in range(0,len(centers)):
			for j in range(i+1,len(centers)):
				seperation = seperation + ( ((centers[i][0]-centers[j][0])**2) + ((centers[i][1]-centers[j][1])**2) )**0.5 
		seperation_values.append(seperation)
		print clusters
		
		cohesion = 0
		
		for cluster in clusters:
			if(cluster==-1):
				for i in range(0,len(clusters[cluster])):
						cohesion = cohesion + ( (clusters[cluster][i][0]**2) + (clusters[cluster][i][1]**2) )**0.5 
			else:
				for i in range(0,len(clusters[cluster])):
					for j in range(i+1,len(clusters[cluster])):
						cohesion = cohesion + ( ((clusters[cluster][i][0]-clusters[cluster][j][0])**2) + ((clusters[cluster][i][1]-clusters[cluster][j][1])**2) )**0.5 
		cohesion_values.append(cohesion)
		print cohesion_values[-1]
		print "\n"
		
	plt.subplot(2,1,1)	
	plt.plot(seperation_values,':')
	plt.subplot(2,1,2)
	plt.plot(cohesion_values,':')
	plt.show()	
	plt.close()
		
