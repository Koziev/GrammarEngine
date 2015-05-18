#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
#----------------------------------------------------------------------

# sample CoNLL reader

import sys;
import getopt
import codecs

def showHelp():
	print 'usage:', sys.argv[0], '[-h] file'
	sys.exit()

opts, args = getopt.getopt(sys.argv[1:], 'h')

if len(sys.argv) < 2:
	showHelp()

for opt, arg in opts:
	if opt == '-h':
            showHelp()
	else:
		showHelp()

if len(args) < 1:
	showHelp()

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

	def __repr__(self):
		return '\n'.join([str(x) for x in self.tokens])


# represent a single token in a sentence.
class Token:
	def __init__(self, items):
		l = len(items)
		# clean empty fields
		for i in range(2, l):
			if items[i] == '_':
				items[i] = ''
		self.id = int(items[0])
		self.form = items[1]
		self.lemma = items[2]
		self.cpos = items[3]
		self.pos = items[4]
		self.feats = items[5]
		if l > 6:
			self.head = int(items[6]) if items[6] else ''
			self.deprel = items[7]
		if l > 8:
			self.phead = int(items[8]) if items[8] else ''
			self.pdeprel = items[9]
		self.children = []

	def __repr__(self):
		serial = lambda x: '_' if x == '' else str(x)
		return '\t'.join([serial(self.id), serial(self.form),
				 serial(self.lemma), serial(self.cpos),
				 serial(self.pos), serial(self.feats),
				 serial(self.head), serial(self.deprel),
				 serial(self.phead), serial(self.pdeprel)])

lineno = 0

def read(file):
	global lineno
	tokens = []
	for line in codecs.open(file, 'r', 'utf-8'):
		lineno += 1
		if line == '\n':
			sent = Sentence(tokens)
			print sent
			print
			tokens = []
		else:
			tokens.append(Token(line.split()))
	if tokens:
		# left over
		sent = Sentence(tokens)
		print sent
		print

read(args[0])
