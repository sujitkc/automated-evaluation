import csv
import glob
import sys
import hdbscan

csv.field_size_limit(sys.maxsize)

for doc in glob.glob('simulate-csv/degree-2/dim-2/timestep-0.1/output-7/3.0_4.0_5.0.csv'): #"output_test.csv"):#
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
	for i in range(0,len(nodes_r['n1'])-1980,1):
		snapshot_points = []
		for j in range(0,len(points)):
			snapshot_points.append( [ points[j][0][i] , points[j][1][i] ] )
		
		clusterer = hdbscan.HDBSCAN(min_cluster_size=2)
		clusterer.fit(snapshot_points)
		
		print "Step Number : " + str(i)
		print clusterer.labels_
		
		# cluster seperation calculations #
		c_num = clusterer.labels_.max() + 1 	# no of clusters formed #
		n_num = 0				# no of outliers #
		for e in clusterer.labels_:
			if e==1:
				n_num=n_num+1

		cluster_points = {}			# contains positions of data points grouped as per cluster #
		for i in range(-1,c_num):
			cluster_points[i]=[]			
			j=0		
			for e in clusterer.labels_:
				if e==i:
					cluster_points[i].append(snapshot_points[j])
				j=j+1
		print cluster_points
		print "\n"
