#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
#----------------------------------------------------------------------

# Count multiple heads

import sys
import unicodedata

if len(sys.argv) < 2:
	print 'usage:', sys.argv[0], 'sysFile'
	sys.exit()

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
		self.children = []

	def __repr__(self):
		return '\t'.join([str(self.id), self.word, self.lemma, self.cpos, self.pos, self.mfeats, str(self.head), self.dep])

def isPunct(s):
	u = unicode(s, 'utf-8')
	return unicodedata.category(u[0]) == 'Po'

forests = 0
rootErrors = 0
punctCount = 0
def verify(sent):
	global forests, rootErrors, punctCount
	heads = 0
	for tok in sent.tokens:
		if tok.head == 0:
			heads += 1
			if isPunct(tok.word):
				punctCount += 1
	if heads > 1:
		forests += 1
		rootErrors += heads - 1
		print heads, 'in', sentCount, sent.tokens[0].word

sentCount = 0
tokenCount = 0
def analyze(file):
	global sentCount, tokenCount
	tokens = []
	sysFile = open(file)
	while line in sysFile:
		if line == '\n':
			sentCount += 1
			sent = Sentence(tokens)
			verify(sent)
			tokens = []
			continue
		tok = Token(line.split())
		tokens.append(tok)
		tokenCount += 1

analyze(sys.argv[1])
print forests, 'multiple heads in', sentCount, 'sentences (', 100.0*rootErrors/tokenCount , '%), in punct: ', punctCount, '/', rootErrors
