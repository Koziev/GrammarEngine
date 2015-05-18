#!/usr/bin/python

# split a CoNLL file into a train and test set either by lines or by sentences.
# If splitting by lines, sentences are chosen throughout the inFile,
# otherwise they are taken from them beginning.

import sys
import getopt

lineLen = 5000
sentLen = 0
fromStart = False

def showHelp():
	print 'usage:', sys.argv[0], '[-l l] [-s s] inFile firstFile secondFile'
	print '   -l lines    	no of lines'
	print '   -s senteneces no of sentences'
	sys.exit()

opts, args = getopt.getopt(sys.argv[1:], 'hl:s:')

for opt, arg in opts:
	if opt == '-h':
            showHelp()
        elif opt == '-l':
		lineLen = int(arg)
        elif opt == '-s':
		sentLen = int(arg)
		fromStart = True
	else:
		showHelp()

if len(args) != 3:
	showHelp()

inFile = file(args[0])
firstFile = file(args[1], 'wa')
secondFile = file(args[2], 'wa')

if sentLen == 0:
	# Count lines and sentences
	lines = 0
	sentTot = 0
	for line in inFile:
		lines += 1
		if line == '\n':
			sentTot += 1
	inFile.seek(0)
	sentLen = int(sentTot / (lineLen / avgSentLen)) - 1
	avgSentLen = float(lines) / sentTot

sent = 1
outFile = firstFile
for line in inFile:
    outFile.write(line)
    if line == '\n':
	if fromStart:    
		if sent >= sentLen:
			outFile = secondFile
        elif sent % sentLen:
            outFile = firstFile
	else:
            outFile = secondFile
	sent += 1
inFile.close()
firstFile.close()
secondFile.close()
