#!/usr/bin/python

import os

count = 0;
print "\nWelcome to the graph resources!! We currently have the following things available: \n"

for name in os.listdir("./"):
	if not os.path.isfile(name):
		count+=1
		print str(count) + ". " + name + " : ", 

		if name == "graphs":
			print "Contains commonly used sparse graphs in matrix market format downloaded from the University of Florida (UoF) Dataset."
	
		elif name ==  "connected_graphs":
			print "Contains the UoF sparse graphs in matrix market format which have been explicitly connected."
		
		elif name ==  "bridges":
			print "Contains the bridges for the graphs in directory 'graph' with the first line containing the count."
	
		elif name ==  "connected_bridges":
			print "Contains the bridges for the graphs in directory 'connected_graphs' with the first line containing the count."

		elif name == "big_graphs":
			print "Contains some very big graphs from the UoF collection which are rarely used."


		print ""

print "\n\n"

