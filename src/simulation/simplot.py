import csv
from matplotlib import pyplot as plt
import glob
import sys

csv.field_size_limit(sys.maxsize)

for doc in glob.glob('simulate-csv/degree-2/dim-2/timestep-0.1/output-3/*.csv'): #"output_test.csv"):#
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
	
	# 2-D MAP #
	count=0
	plt.subplot2grid( (l/3 +1,2),(0,0), colspan=2)
	for keys in nodes_r:
		x = []			# x co-ordinate #
		y = []			# y co-ordinate #
		node_label = keys
		colors = ['b','g','r','c','m','y','k']
		for e in nodes_r[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))
		plt.plot(x[0],y[0],'x',markersize=3,color=colors[count])		# start point #
		plt.plot(x[-1],y[-1],'D',markersize=3,color=colors[count])		# end point #
		#plt.plot(x,y,':',color=colors[count],label=node_label)
		#axes = plt.gca()
		#axes.set_xlim([-10.0,10.0])
		count=count+1	
	#plt.xlabel('X-Position')
	#plt.ylabel('Y-Position')
	plt.legend()
	
	# POSITION vs TIME #
	count=0
	for keys in nodes_r:
		x = []			# x co-ordinate #
		y = []			# y co-ordinate #
		mag = []		# magnitude #
		node_label = keys
		colors = ['b','g','r','c','m','y','k']
		for e in nodes_r[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))
		
		plt.subplot2grid( (l/3 +1,2),(count+1,0), colspan=1)	# x vector #		
		plt.plot(x,'-',color=colors[count],label=node_label)
		#plt.legend()
		
		plt.subplot2grid( (l/3 +1,2),(count+1,1), colspan=1)	# y vector #		
		plt.plot(y,'-',color=colors[count],label=node_label)
		#plt.legend()
		#axes = plt.gca()
		#axes.set_ylim([-2,2])
		count=count+1	
		#plt.ylabel('Position')
		#plt.xlabel('Datapoint #')		
		
	'''
	# VELOCITY MAGNITUDE #
	count=0
	plt.subplot(3,1,2)
	for keys in nodes_v:
		x = []			# x co-ordinate #
		y = []			# y co-ordinate #
		mag = []		# magnitude #
		node_label = keys
		colors = ['b','g','r','c','m','y','k']
		for e in nodes_v[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))
			mag.append( ( (x[-1])**2 + (y[-1])**2 ) ** 0.5 )
		#plt.plot(x[0],y[0],'x',markersize=3,color=colors[count])		# start point #
		#plt.plot(x[-1],y[-1],'D',markersize=3,color=colors[count])		# end point #
		plt.plot(mag,'-',color=colors[count],label=node_label)
		count=count+1	
	plt.ylabel('Velocity')
	plt.legend()
		
	# ACCELARTION MAGNITUDE #
	count=0
	plt.subplot(3,1,3)
	for keys in nodes_a:
		x = []			# x co-ordinate #
		y = []			# y co-ordinate #
		mag = []		# magnitude #
		node_label = keys
		colors = ['b','g','r','c','m','y','k']
		for e in nodes_a[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))
			mag.append( ( (x[-1])**2 + (y[-1])**2 ) ** 0.5 )
		#plt.plot(x[0],y[0],'x',markersize=3,color=colors[count])		# start point #
		#plt.plot(x[-1],y[-1],'D',markersize=3,color=colors[count])		# end point #
		plt.plot(mag,'-',color=colors[count],label=node_label)
		count=count+1	
	plt.ylabel('Aceleration')
	plt.legend()
	'''		
	plt.tight_layout()	
	#plt.show()
	
	f=doc.split('.csv')[0].split('/')[-1].split('_')[0]
	r=doc.split('.csv')[0].split('/')[-1].split('_')[1]
	a=doc.split('.csv')[0].split('/')[-1].split('_')[2]
	
	#plt.title('f='+str(f)+' | r='+str(r)+' | a='+str(a))
	
	fig = plt.gcf()
	fig.set_size_inches((16, 9), forward=False)
	plt.savefig("simulate-png/degree-2/dim-2/timestep-0.1/output-3/"+str(f)+'_'+str(r)+'_'+str(a)+'.png', dpi=300)
	
	plt.close()
	print str(f)+'_'+str(r)+'_'+str(a)+'.png'

