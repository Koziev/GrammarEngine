#!/usr/bin/python

# Compare two/three CoNLL files

import sys;
import getopt

def showHelp():
	print 'usage:', sys.argv[0], '[-a] ref file2 [file3]'
	print '   -a    show all lines'
	sys.exit()

opts, args = getopt.getopt(sys.argv[1:], 'ah')

all = False			# show all lines

for opt, arg in opts:
	if opt == '-h':
            showHelp()
        elif opt == '-a':
		all = True
	else:
		showHelp()

if len(args) < 2:
	showHelp()

def compare(file1, file2):
 n = 0
 for line1 in file1:
	 line2 = file2.readline()
	 n += 1
	 if line1 == '\n':
		 if all: print
		 continue
	 val1 = line1.split()
	 val2 = line2.split()
	 if all:
		 diff6 = val1[6]
		 if diff6 != val2[6]:
			 diff6 += '(' + val2[6] + ')'
		 diff7 = val1[7]
		 if diff7 != val2[7]:
			 diff7 += '(' + val2[7] + ')'
		 print '%s\t%s\t%s\t%s\t%s' % (val1[0], val1[1], val1[4], diff6, diff7)
	 elif val1[6] != val2[6] or val1[7] != val2[7]:
	 #if val1[6] == val2[6] and val1[7] != val2[7]:
		 print '%d: %s\t%s\t%s' % (n, val1[0], val1[1], val1[6]),
		 if val1[6] != val2[6]:		# diff head
			 print '(%s)' % (val2[6]),
		 print '\t%s' % (val1[7]),
		 if val1[7] != val2[7]:	# diff dependency
			 print '(%s)' % (val2[7]),
		 print

def compare3(file1, file2, file3):
 n = 0
 for line1 in file1:
	 line2 = file2.readline()
	 line3 = file3.readline()
	 n += 1
	 if line1 == '\n':
		 if all: print
		 continue
	 val1 = line1.split()
	 val2 = line2.split()
	 val3 = line3.split()
	 if all:
		 diff6 = val1[6]
		 if val1[6] == val2[6]:
			 if val1[6] != val3[6]:
				 diff6 += '(-,' + val3[6] + ')'
		 elif val1[6] == val3[6]:
			 diff6 += '(' + val2[6] + ',-)'
		 else:
			 diff6 += '(' + val2[6] + ',' + val3[6] + ')'
		 diff7 = val1[7]
		 if val1[7] == val2[7]:
			 if val1[7] != val3[7]:
				 diff7 += '(-,' + val3[7] + ')'
		 elif val1[7] == val3[7]:
			 diff7 += '(' + val2[7] + ',-)'
		 else:
			 diff7 += '(' + val2[7] + ',' + val3[7] + ')'
		 print '%s\t%s\t%s\t%s\t%s' % (val1[0], val1[1], val1[4], diff6, diff7)
	 # show only different head errors
#	 if (val1[6] != val2[6] and val1[6] == val3[6]) or (val1[6] == val2[6] and val1[6] != val3[6]):
	 # show head errors from both
	 elif val1[6] != val2[6] or val1[6] != val3[6]:
		 print '%d: %s\t%s\t%s' % (n, val1[0], val1[1], val1[6]),
		 if val1[6] != val2[6] and val1[6] != val3[6]:
			 print '(%s %s)' % (val2[6], val3[6]),
		 elif val1[6] == val2[6]:
			 print '(- %s)' % (val3[6]),
		 else:
			 print '(%s -)' % (val2[6]),
		 print '\t%s' % (val1[7]),
		 print '(%s %s)' % (val2[7], val3[7]),
		 print

# Main program

file1 = open(args[0])
file2 = open(args[1])
if len(args) == 3:
	file3 = open(args[2])
	compare3(file1, file2, file3)
else:
	compare(file1, file2)
