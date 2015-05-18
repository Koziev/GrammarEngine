#!/usr/bin/python

# Restore value of <num> into MST parse from original CoNLL file

import sys;

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'mst orig'
	sys.exit()

mst = open(sys.argv[1])
orig = open(sys.argv[2])

while 1:
	 line1 = mst.readline()
	 line2 = orig.readline()
	 if line1 == '':
		 break
	 if line1 == '\n':
		 print
		 continue
	 val1 = line1.split()
	 val2 = line2.split()
	 if val1[1] == '<num>':
		 val1[1] = val2[1]
	 if val1[2] == '<num>':
		 val1[2] = val2[2]
	 print '\t'.join(val1)
