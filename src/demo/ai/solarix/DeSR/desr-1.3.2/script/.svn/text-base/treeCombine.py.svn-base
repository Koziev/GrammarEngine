#!/usr/bin/env python
#----------------------------------------------------------------------
#	Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
#	Copyright (c) 2008  Felice Dell'Orletta (dellorle@di.unipi.it).
#----------------------------------------------------------------------

#  Combines three parse trees (maximum spanning tree).

import sys
import re

# use binary mode to avoid adding \r
if sys.platform == "win32":
	import os, msvcrt
	msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

debug = False #True

if len(sys.argv) < 7:
	print 'usage:', sys.argv[0], ' file1 file2 file3 eval1 eval1 eval3'
	print '   file1 file2 file3 are the output of three parsers'
	print '   eval1 eval2 eval3 are their evaluations produced by eval07.pl'
	print '   ORDER files by LAS.'
	sys.exit()

class Sentence:
	"represents a sentence"

	def __init__(self, tokens):
		self.tokens = tokens
		self.roots = []
		for n in tokens:
			if n.head == 0:
				self.roots.append(n)
			if n.head != 0:
				tokens[n.head-1].children.append(n)

	def __repr__(self):
		return '\n'.join([str(x) for x in self.tokens])

class Token:
	"represent a single token in a sentence"
	def __init__(self, id, word, lemma, cpos, pos, mfeats, head, dep, weight):
		self.id = int(id)
		self.word = word
		self.lemma = lemma
		self.cpos = cpos
		self.pos = pos
		self.mfeats = mfeats
		self.head = int(head)
		self.dep = dep
		self.weight = weight
		self.children = []

	def __init__(self, items, weights):
		self.id = int(items[0])
		self.word = items[1]
		self.lemma = items[2]
		self.cpos = items[3]
		self.pos = items[4]
		self.mfeats = items[5]
		self.head = int(items[6])
		self.dep = items[7]
		self.weight = weights.get(self.cpos, 0)
		self.children = []

	def __repr__(self):
		return '\t'.join([str(self.id), self.word, self.lemma, self.cpos, self.pos, self.mfeats, str(self.head), self.dep, str(self.weight)])

class ArcInfo:
	"arc stored in fringe"

	def __init__(self, weight, tok):
		self.weight = weight
		self.tok = tok

	def __repr__(self):
		return str(self.weight)

weight1 = {}
weight2 = {}
weight3 = {}

rel = re.compile(r'(\S+).*\s(\d+)%', re.I)

def loadScores(eval1, eval2, eval3):
	"create weight maps from eval07 files"
	file1 = open(eval1)
	file2 = open(eval2)
	file3 = open(eval3)
	# skip initial part of files
	for n in range(0, 22):
		line1 = file1.readline()
		line2 = file2.readline()
		line3 = file3.readline()
	more1 = rel.search(line1)
	more2 = rel.search(line2)
	more3 = rel.search(line3)
	while more1 or more2 or more3:
		if more1:
			weight1[more1.group(1)] = int(more1.group(2))
			line1 = file1.readline()
			more1 = rel.search(line1)
		if more2:
			weight2[more2.group(1)] = int(more2.group(2))
			line2 = file2.readline()
			more2 = rel.search(line2)
		if more3:
			weight3[more3.group(1)] = int(more3.group(2))
			line3 = file3.readline()
			more3 = rel.search(line3)
	file1.close()
	file2.close()
	file3.close()

def removeBest(fringe):
	"remove the arc in fringe with the highest weight and return it"
	max = -1
	# questo for puo' essere eliminato utilizzando una struttura dati
	# ordinata sui pesi (per ora e' ok, ma non lo calcoliamo nel costo
	# computazionale (diventera' log_n) )
	for arc in fringe:
		arcInfo = fringe[arc]
		if max < arcInfo.weight:
			max = arcInfo.weight
			tok = arcInfo.tok
			best = arc
	del fringe[best]
	return tok

def aggiungi(fringe, tok, tree):
	tree[tok.id-1] = tok
	# questo for puo' essere eliminato utilizzando un altro hashmap
	# solo di chiavi  (per ora e' ok, ma non lo calcoliamo nel
	# costo compuatazionale.. diventera' costante)
	for k in fringe.keys():
		token = fringe[k].tok
		if token.id == tok.id and token != tok:
			del fringe[k]

def expand(fringe, tok, tree):
	"add arcs starting from tok"
	children = tokens1[tok.id-1].children + tokens2[tok.id-1].children + tokens3[tok.id-1].children    
	for child in children:
		if not (child.id-1) in tree:
			arc = (child.id, child.head, child.dep)
			if arc in fringe:
				fringe[arc].weight += child.weight
			else:
				fringe[arc] = ArcInfo(child.weight, child)

def combineTrees(roots):
	tree = {}			# the combined tree
	# fringe of the tree being built, contains arcs <id, head, dep>
	# with associated weight
	fringe = {}
	for root in roots:
		arc = (root.id, root.head, root.dep)
		if arc in fringe:
			fringe[arc].weight += root.weight
		else:
			fringe[arc] = ArcInfo(root.weight, root)
	while len(fringe) != 0:
		if debug:
			print fringe
		tok = removeBest(fringe)
		#tree[tok.id-1] = tok	# add to tree
		aggiungi(fringe, tok, tree)
		expand(fringe, tok, tree)
	return tree

def combineFiles(file1, file2, file3):
	global tokens1, tokens2, tokens3
	tokens1 = []
	tokens2 = []
	tokens3 = []
	sysFile1 = open(file1)
	sysFile2 = open(file2)
	sysFile3 = open(file3)
	while True:
		line1 = sysFile1.readline()
		line2 = sysFile2.readline()
		line3 = sysFile3.readline()
		if line1 == '':
			break
		if line1 == '\n':
			sent1 = Sentence(tokens1)
			sent2 = Sentence(tokens2)
			sent3 = Sentence(tokens3)
			roots = sent1.roots + sent2.roots + sent3.roots
			sentence = combineTrees(roots)      
			for k in range(0, len(sentence)):
 				print sentence[k]
			print
			tokens1 = []
			tokens2 = []
			tokens3 = []
			continue
		tokens1.append(Token(line1.split(), weight1))
		tokens2.append(Token(line2.split(), weight2))
		tokens3.append(Token(line3.split(), weight3))
		
loadScores(sys.argv[4], sys.argv[5], sys.argv[6])
combineFiles(sys.argv[1], sys.argv[2], sys.argv[3])
