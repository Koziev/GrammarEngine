#!/usr/bin/python

# Script for adding stemmed word in LEMMA field of CoNLL-X format.
# The script uses the Snowball stemmer (http://snowball.tartarus.org/).
# Assign to the variable stemwords the location where the program is installed.
#
# Usage:
#
# stem.py language inFile
#
# The result is output to standard output.
#
# Language should be one of these:
# de, deutsch, german
# da, danish
# nl, dut, dutch
# en, english
# es, spanish
# fi, finnish
# fr, french
# it, italian
# no, norwegian
# pt, portuguese
# sv, swedish

stemwords = '/project/piqasso/QA/Parser/libstemmer_c/stemwords'

import os
import sys

if len(sys.argv) != 3:
	print 'usage:', sys.argv[0], 'language inFile'
	sys.exit()

# use binary mode to avoid adding \r
if sys.platform == "win32":
	import os, msvcrt
	msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

lang = sys.argv[1]
inFile = file(sys.argv[2])
tmpFileName = os.tmpnam()
stemFileName = os.tmpnam()
tmpFile = file(tmpFileName, 'wa')

while 1:
    line = inFile.readline()
    if line == '':
        break
    if line == '\n':
	print >> tmpFile
	continue
    items = line.split();
    print >> tmpFile, items[1]
tmpFile.close()

os.system(stemwords + ' -l ' + lang + ' -i ' + tmpFileName + ' -o ' + stemFileName)

stemFile = file(stemFileName)
inFile.seek(0)
while 1:
    line = inFile.readline()
    stem = stemFile.readline()
    if line == '':
        break
    if line == '\n':
	print
	continue
    items = line.split();
    print "%s\t%s\t%s\t" % (items[0], items[1], stem.strip()),
    print '\t'.join(items[3:])

inFile.close()
os.remove(tmpFileName)
os.remove(stemFileName)
