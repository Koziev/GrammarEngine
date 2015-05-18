#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
#----------------------------------------------------------------------

# Count projectivity errors
# Use following criterion:
# i -> j is projective iff forall i < k < j or j < k < i, i ->* k
# which reduces to:
# i -> j is non-projective iff
#  exists    i < k < j, l -> k, l < i or j < l
#  or exists j < k < i, l -> k, l < j or i < l

import sys;
import getopt

def showHelp():
	print 'usage:', sys.argv[0], '[-hs] goldFile sysFile'
	print '   -s    show errors'
	sys.exit()

projTot = 0
projErr = 0
lineno = 0
show = False			# show errors

opts, args = getopt.getopt(sys.argv[1:], 'hs')

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], '[-hs] goldFile sysFile'
	sys.exit()

for opt, arg in opts:
	if opt == '-h':
            showHelp()
        elif opt == '-s':
		show = True
	else:
		showHelp()

if len(args) < 2:
	showHelp()

# represents a sentence
class Sentence:

	def __init__(self, tokens):
		self.tokens = tokens
		self.root = tokens[0]
		for n in tokens:
			if n.id == 0:
				self.root = n
			if n.head != 0:
				tokens[n.head-1].children.append(n)

	def __repr__(self):
		return '\n'.join([str(x) for x in self.tokens])

	def compare(self, sent2):
		global projTot, projErr, lineno
		# sent2 is incorrect
		for t in self.tokens:	
			if t.id < t.head:
                                a = t.id
                                c = t.head
                        else:
                                a = t.head
                                c = t.id
			# check whether Exists b: a < b < c, with b.head < a or c < b.head
			for b in self.tokens[a:c-1]:
				if b.head < a or c < b.head:
					# non projective link
					projTot += 1
					wrong = t.head != sent2.tokens[t.id-1].head
					if wrong:
						projErr += 1
					if show:
						start = lineno - len(self.tokens)
						print start + b.id - 1, b.form, "crosses", start + t.id - 1, t.form, wrong
					break

# represent a single token in a sentence.
class Token:
	def __init__(self, id, form, lemma, cpos, pos, mfeats, head, dep):
		self.id = int(id)
		self.form = form
		self.lemma = lemma
		self.cpos = cpos
		self.pos = pos
		self.mfeats = mfeats
		self.head = int(head)
		self.dep = dep
		self.children = []

	def __init__(self, items):
		self.id = int(items[0])
		self.form = items[1]
		self.lemma = items[2]
		self.cpos = items[3]
		self.pos = items[4]
		self.mfeats = items[5]
		self.head = int(items[6])
		self.dep = items[7]
		self.children = []

	def __repr__(self):
		return '\t'.join([str(self.id), self.form, self.lemma, self.cpos, self.pos, self.mfeats, str(self.head), self.dep])

def analyze(file1, file2):
	global lineno
	tokens1 = []
	tokens2 = []
	goldFile = open(file1)
	sysFile = open(file2)
	while True:
		line1 = goldFile.readline()
		line2 = sysFile.readline()
		if line1 == '' and line2 == '':
			break
		lineno += 1
		if line1 == '\n' and line2 == '\n':
			sent1 = Sentence(tokens1)
			sent2 = Sentence(tokens2)
			sent1.compare(sent2)
			tokens1 = []
			tokens2 = []
			continue
		tok1 = Token(line1.split())
		tok2 = Token(line2.split())
		tokens1.append(tok1)
		tokens2.append(tok2)
	if len(tokens1) > 0:
		sent1 = Sentence(tokens1)
		sent2 = Sentence(tokens2)
		sent1.compare(sent2)

analyze(args[0], args[1])
correct = projTot - projErr
if projTot == 0:
	print 'No non-projective links'
else:
	print 'Accuracy: %d (%d/%d)' % ((correct * 100.0)/projTot, correct, projTot)
