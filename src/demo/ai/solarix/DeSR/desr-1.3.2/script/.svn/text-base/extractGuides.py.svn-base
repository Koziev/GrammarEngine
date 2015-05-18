#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
#	Copyright (c) 2007  Dell'Orletta Felice (dellorle@di.unipi.it).
#----------------------------------------------------------------------

#  Estracts features to guide a parser on the output of a previous parser.
#  It can be used in two modes:
#  1. train mode: accepts a gold file and a parsed file and creates a variant
#     of gold with additional features corresponding to the parsed output.
#  2. parse mode: given as both argument a parser output, adds to it features
#     for guiding a stacked parser.

import sys
import codecs

# use binary mode to avoid adding \r
if sys.platform == "win32":
	import os, msvcrt
	msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

if len(sys.argv) < 2 or 3 < len(sys.argv):
	print 'usage:', sys.argv[0], 'gold parsed'
	sys.exit()

# represents a sentence
class Sentence:

	def __init__(self, tokens):
		self.tokens = tokens
		self.root = tokens[0]
		for n in tokens:
			if n.head == 0:
				self.root = n
			if n.head != 0:
				tokens[n.head-1].children.append(n)

	def __repr__(self):
		return '\n'.join([str(x) for x in self.tokens])

# represent a single token in a sentence.
class Token:
	def __init__(self, id, word, lemma, cpos, pos, mfeats, head, dep, phead, pdep):
		self.id = int(id)
		self.word = word
		self.lemma = lemma
		self.cpos = cpos
		self.pos = pos
		self.mfeats = mfeats
		if self.head == '_': # blind test
			self.head = head
		else:
			self.head = int(head)
		self.dep = dep
		self.phead = phead
		self.pdep = pdep
		self.children = []

	def __init__(self, items):
		self.id = int(items[0])
		self.word = items[1]
		self.lemma = items[2]
		self.cpos = items[3]
		self.pos = items[4]
		self.mfeats = items[5]
		self.head = items[6]
		if self.head != '_': # not blind test
			self.head = int(self.head)
		self.dep = items[7]
		self.phead = items[8]
		self.pdep = items[9]
		self.children = []

	def __repr__(self):
		return '\t'.join([str(self.id), self.word, self.lemma, self.cpos, self.pos, self.mfeats, str(self.head), self.dep. self.phead, self.pdep])
	
def extractGuides(fileG, fileP):
	sentenceG = []
	sentenceP = []
	sysFileG = codecs.open(fileG, 'r', 'utf-8')
        sysFileP = codecs.open(fileP, 'r', 'utf-8')
	for lineG in sysFileG:
		lineP = sysFileP.readline()
		if lineG == '\n':
			for tok in sentenceP:
				if tok.head == 0:
					Posizione = '0'
					Dep = tok.dep
					HeadLemma = 'rOOt'
					HeadPos = 'r'
					HeadHeadLemma = 'RooT'
					HeadDep = 'rOOt'
				else:
					posizione = tok.id - tok.head
					if posizione > 0:
						Posizione = 'post'
					else:
						Posizione = 'pre'
					Dep = tok.dep
					head = sentenceP[tok.head - 1]
					if head.lemma == '_':
						HeadLemma = head.word
					else:
						HeadLemma = head.lemma
					HeadPos = head.pos
					if head.head == 0:
						HeadHeadLemma = 'rOOt'
						HeadDep = 'r'
					else:
						hhead = sentenceP[head.head - 1]
						if hhead.lemma == '_':
							HeadHeadLemma = hhead.word
						else:
							HeadHeadLemma = hhead.lemma
						HeadDep = head.dep
				token = sentenceG[tok.id - 1]
				print '\t'.join([str(token.id), token.word, token.lemma, token.cpos, token.pos, token.mfeats, str(token.head), token.dep, token.phead, token.pdep, HeadLemma, Dep, HeadPos, Posizione, HeadDep, HeadHeadLemma]).encode('utf-8')
			print
			sentenceG = []
			sentenceP = []
			continue
		sentenceG.append(Token(lineG.strip().split('\t')))
		sentenceP.append(Token(lineP.strip().split('\t')))

fileGold = sys.argv[1]
if len(sys.argv) == 2:
	fileParsed = sys.argv[1]
else:
	fileParsed = sys.argv[2]

extractGuides(fileGold, fileParsed)
