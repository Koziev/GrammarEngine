#!/usr/bin/python

# Select sentences whose parses match from two CoNLL files

import sys;

if len(sys.argv) < 2:
	print 'usage:', sys.argv[0], 'file1 file2'
	sys.exit()

def match(file1, file2):
 sent1 = []
 sent2 = []
 skip = False
 while True:
	 line1 = file1.readline()
	 line2 = file2.readline()
	 if line1 == '':
		 break
	 if line1 == '\n':
		 if not skip:
			 i = 0
			 for tok1 in sent1:
				 tok2 = sent2[i]
				 #print '\t'.join(tok1[0:8]) + '\t' + tok2[7]
				 print '\t'.join(tok1)
				 i += 1
			 print
		 sent1 = []
		 sent2 = []
		 skip = False
		 continue
	 val1 = line1.split()
	 val2 = line2.split()
	 if val1[6] == val2[6] or val1[3] == 'F' or val1[4] == 'cc':
		 sent1.append(val1)
		 sent2.append(val2)
	 else:
		 skip = True

# Main program

file1 = open(sys.argv[1])
file2 = open(sys.argv[2])
match(file1, file2)
