#!/usr/bin/python

# Merge dependencies from one CoNLL file into another

import sys;

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'noDep withDep'
	sys.exit()
	
noDep = open(sys.argv[1])
withDep = open(sys.argv[2])

while 1:
	 line1 = noDep.readline()
	 line2 = withDep.readline()
	 if line1 == '':
		 break
	 if line1 == '\n':
		 print
		 continue
	 items1 = line1.split()
	 items2 = line2.split()
	 for i in range(10 - len(items1)):
		 items1.append('_')
	 items1[6] = items2[6]
	 items1[7] = items2[7]
	 print '\t'.join(items1)
