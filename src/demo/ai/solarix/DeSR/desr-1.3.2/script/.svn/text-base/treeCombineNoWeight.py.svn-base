#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
#	Copyright (c) 2008  Dell'Orletta Felice (dellorle@di.unipi.it).
#----------------------------------------------------------------------

# Combines in O(n) three parse trees.

import sys
import operator

if len(sys.argv) < 2:
	print 'usage:', sys.argv[0], 'file1 file2 ...'
	sys.exit()

# represents a sentence
class Sentence:

	def __init__(self, tokens):
		self.tokens = tokens
		self.root = tokens[0]
		for n in tokens:
			if n.head == 0:
				self.root = n
			else:
				tokens[n.head-1].children.append(n)

	def getRoots(self):
		" return all roots: can be more than one."
		roots = []
		for n in self.tokens:
			if n.head == 0:
				roots.append(n)
		return roots


	def __repr__(self):
		return '\n'.join([str(x) for x in self.tokens])

# represent a single token in a sentence.
class Token:
	def __init__(self, id, word, lemma, cpos, pos, mfeats, head, dep):
		self.id = int(id)
		self.word = word
		self.lemma = lemma
		self.cpos = cpos
		self.pos = pos
		self.mfeats = mfeats
		self.head = int(head)
		self.dep = dep
		self.weight = int(0)
		self.children = []

	def __init__(self, items):
		self.id = int(items[0])
		self.word = items[1]
		self.lemma = items[2]
		self.cpos = items[3]
		self.pos = items[4]
		self.mfeats = items[5]
		self.head = int(items[6])
		self.dep = items[7]
		self.phead = items[8]
		self.pdep = items[9]
		self.weight = int(0)
		self.children = []

	def __repr__(self):
		return '\t'.join([str(self.id), self.word, self.lemma, self.cpos, self.pos, self.mfeats, str(self.head), self.dep, self.phead, self.pdep])


# Adds arc to result tree
def add(arc, result):
	(id, head, dep) = arc
	for tokens in tokenLists:
		for tok in tokens:
			if tok.id == id and tok.head == head and tok.dep == dep:
				result[id-1] = tok # add to result
				return

def insert(arc, weight, dict):
# 	# FIXME: should contribute also to same link, different dep
# 	for el in dict:
# 		if arc[0] == el[0] and arc[1] == el[1]:
# 			dict[el] += .3
	if arc in dict:
		dict[arc] += weight
	else:
		dict[arc] = weight

# Linear
def expand(id, result, fringe):
	# collect the children of node
	idx = id-1
	weight = 0.9 + len(tokenLists) / 10.0
	for tokens in tokenLists:
		for tok in tokens[idx].children:
			if not (tok.id-1) in result:
				insert((tok.id, tok.head, tok.dep), weight, fringe)
		weight -= 0.1

def combineTrees(roots):
	result = {}
	# fringe represents the frontier, with number of votes
	fringe = {}
	
	# Give preference to first tree
	weight = 1.2
	for root in roots:
		arc = (root.id, root.head, root.dep)
		insert(arc, weight, fringe)
		weight -= .1

	while len(fringe):
		(best, weight) = max(fringe.iteritems(), key=operator.itemgetter(1))
		del fringe[best]
		tokid = best[0]
		if not tokid-1 in result:
			add(best, result)
			expand(tokid, result, fringe)
	return result

def readSentence(file):
	tokens = []
	for line in file:
		line = line.strip()
		if line:
			tokens.append(Token(line.split()))
		else:
			return tokens
	return None

def processFiles(files):
	global tokenLists
	for i in range(len(files)):
		files[i] = open(files[i])
	while True:
		# read one sentence from all files
		roots = []
		tokenLists = []
		for file in files:
			tokens = readSentence(file)
			if not tokens:
				return
			roots += Sentence(tokens).getRoots()
			tokenLists.append(tokens)
		# combine all trees
		result = combineTrees(roots)
		for tok in result.values():
			print tok
		print
		
processFiles(sys.argv[1:])
