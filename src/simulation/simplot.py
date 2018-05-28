import csv
from matplotlib import pyplot as plt
import glob

for doc in glob.glob('simulate-csv/degree-2/dim-2/timestep-0.1/output-2/*.csv'): #"output_test.csv"):#
	data=[]
	print doc
	with open(doc, 'rb') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=' ')
		for row in spamreader:
			data.append([','.join(row)])
	#print data[0][0].split(',')
	nodes={}			# key=node; value=list(snapshots(x)) #
	for e in data:
		n = e[0].split(',')
		nodes[n[0]] = n[1:]
	#print nodes
	count=0
	for keys in nodes:
		x = []			# x co-ordinate #
		y = []			# y co-ordinate #
		node_label = keys
		colors = ['b','g','r','c','m','y','k']
		for e in nodes[keys]:
			x.append(float(e.split('/')[0]))
			y.append(float(e.split('/')[1]))
		plt.plot(x[0],y[0],'x',color=colors[count])		# start point #
		plt.plot(x[-1],y[-1],'D',color=colors[count])		# end point #
		plt.plot(x,y,':',color=colors[count],label=node_label)
		count=count+1	
	plt.xlabel('X-Position')
	plt.ylabel('Y-Position')
	plt.legend()
	
	f=doc.split('.csv')[0].split('/')[-1].split('_')[0]
	r=doc.split('.csv')[0].split('/')[-1].split('_')[1]
	a=doc.split('.csv')[0].split('/')[-1].split('_')[2]
	
	plt.title('f='+str(f)+' | r='+str(r)+' | a='+str(a))
	plt.savefig("simulate-png/degree-2/dim-2/timestep-0.1/output-2/"+str(f)+'_'+str(r)+'_'+str(a)+'.png', dpi=300)
	plt.close()
	print str(f)+'_'+str(r)+'_'+str(a)+'.png'
