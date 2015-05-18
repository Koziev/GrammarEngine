#!/usr/bin/python

# Merge POS from one file into a CoNLL file

import sys;

# use binary mode to avoid adding \r
if sys.platform == "win32":
	import os, msvcrt
	msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'noPos posFile'
	sys.exit()
	
noPos = open(sys.argv[1])
posFile = open(sys.argv[2])

while 1:
	 line1 = noPos.readline()
	 if line1 == '':
		 break
	 if line1 == '\n':
		 print
		 continue
	 line2 = posFile.readline()
	 val1 = line1.split()
	 val2 = line2.split()
	 val1[4] = val2[1]
	 print '\t'.join(val1)
