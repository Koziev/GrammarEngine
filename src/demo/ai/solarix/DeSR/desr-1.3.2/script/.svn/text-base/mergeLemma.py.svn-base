#!/usr/bin/python

# Merge lemma from one CoNLL file into another

import sys;

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'noLemma withLemma'
	sys.exit()
	
noLemma = open(sys.argv[1])
withLemma = open(sys.argv[2])

while 1:
	 line1 = noLemma.readline()
	 line2 = withLemma.readline()
	 if line1 == '':
		 break
	 if line1 == '\n':
		 print
		 continue
	 val1 = line1.split()
	 val2 = line2.split()
	 while val1[1] != val2[1]:
		 line2 = withLemma.readline()
		 if line2 == '':
			 break
		 if line2 == '\n':
			 continue
		 val2 = line2.split()
	 if line2 == '':
		 break
	 val1[2] = val2[2]
	 print '\t'.join(val1)
