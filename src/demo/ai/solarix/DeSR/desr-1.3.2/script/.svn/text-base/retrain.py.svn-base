#!/usr/bin/python
#----------------------------------------------------------------------
#	Copyright (c) 2006  Giuseppe Attardi (attardi@di.unipi.it).
#----------------------------------------------------------------------

# Generate retrain data for parser

import sys;

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'goldFile sysFile [outFile]'
	sys.exit()

outFile = sys.stdout
if len(sys.argv) == 4:
	outFile = open(sys.argv[3], "wa")
elif sys.platform == "win32":
	# use binary mode to avoid adding \r
	import os, msvcrt
	msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

# whether to make fixes incrementally, so previous fixes influence others.
# For instance, in:
#   that figure is derived after including debt , and subtracting
# if we fix ',' to link to 'including', then both 'and' and 'subtracting'
# can be redirected to it just by going one level up.
# Unfortunately, we get loop in:
#   says the line, which clients do n't know about , received
# as 'says' goes back to 'received'
# We should fix parser not to link 'received' to 'about'
incremental = False

errtot = 0
errsent = 0
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
		# sent2 is incorrect
		l = len(self.tokens)
		err = 0
		for i in range(l):
			tok1 = self.tokens[i]
			tok2 = sent2.tokens[i]
			# standard version
			if tok1.head == tok2.head:
				print 'OK',
			else:
				print sent2.computeAction(i+1, tok1.head),
				err += 1
			# version with depedencies
# 			if tok1.head == tok2.head:
# 				print 'OK\t-',
# 			else:
# 				print '%s\t%s' % (sent2.computeAction(i+1, tok1.head), tok1.dep),
			# show context
			parent = self.parent(tok2)
			grandParent = self.parent(parent)
			ggParent = self.parent(grandParent)
			print 'L%s P%s D%s' % (tok2.lemma, tok2.pos, tok2.dep), # which word
			if i > 0:
				tok2p = sent2.tokens[i-1]
				print '-1L%s -1P%s -1D%s' % (tok2p.lemma, tok2p.pos, tok2p.dep), # previous word
			if i < l-1:
				tok2n = sent2.tokens[i+1]
				print '+1L%s +1P%s +1D%s' % (tok2n.lemma, tok2n.pos, tok2n.dep), # next word
			sent2.childFeatures(tok2, "")
			if grandParent != None:
				print "GL%s GP%s GD%s" % (grandParent.lemma, grandParent.pos, grandParent.dep),
			if ggParent != None:
				print "GGL%s GGP%s GGD%s" % (ggParent.lemma, ggParent.pos, ggParent.dep),
			if parent != None:
				sent2.childFeatures(parent, "u")
				for sibl in sent2.tokens:
					if sibl.head == parent.id:
						sent2.childFeatures(sibl, "uudd")
			if grandParent != None:
				sent2.childFeatures(grandParent, "uu")
			print
		if err > 0:
			global errtot, errsent
			errtot += err
			errsent += l

	def childFeatures(self, parent, tag):
		for tok in self.tokens:
			if tok.head == parent.id:
				if tok.id < parent.id:
					print "L%s<%s" % (tag, tok.lemma),
					print "P%s<%s" % (tag, tok.pos),
					print "D%s<%s" % (tag, tok.dep),
				else:
					print "L%s>%s" % (tag, tok.lemma),
					print "P%s>%s" % (tag, tok.pos),
					print "D%s>%s" % (tag, tok.dep),


	def computeAction(self, nodeId, headId):
		"Determine action to correct node with ID=nodeId to have headId as its head"
		node = self.tokens[nodeId-1]
		parent = self.parent(node)
		gParent = self.parent(parent)
		ggParent = self.parent(gParent)
		if headId == 0:
			return "r"	# root
		else:
			head = self.tokens[headId-1]
		headParent = self.parent(head)
		headGParent = self.parent(headParent)
		headSon = self.whichSon(head) # how to reach head from its parent
		if incremental:
			node.head = headId
		# find path to correct head
		# to immediately previous token
		if nodeId > 1 and self.tokens[nodeId-2] == head:
			return "-1"	# left
		# to immediately next token
		if nodeId < len(self.tokens) and self.tokens[nodeId] == head:
			return "+1"	# right
		# up or down
		if nodeId == head.head:
			return headSon # down
		if gParent == head:
			return "uu"	# up up
		# relative to immediately previous token
		if nodeId > 1 and self.parent(self.tokens[nodeId-2]) == head:
			return "-1u"	# left up
		# relative to immediately next token
		if nodeId < len(self.tokens) and self.parent(self.tokens[nodeId]) == head:
			return "+1u"	# right up
		# to the preceding token
		lmd = node.leftmostDescendant()
		if headId == lmd - 1:
			return "<"	# previous
		if lmd > 1 and head == self.parent(self.tokens[lmd - 2]):
			return "<u"	# previous up
		# to the following token
		rmd = node.rightmostDescendant()
		if headId == rmd + 1:
			return ">"	# next
		if rmd < len(self.tokens) and head == self.parent(self.tokens[rmd]):
			return ">u"	# next up
		# more up
		if ggParent == head:
			return "uuu"	# up up up
		if self.parent(ggParent) == head:
			return "uuuu"	# up up up up
		# to the previous head
		lmd = node.leftmostDescendant()
		rmd = head.rightmostDescendant()
		if rmd == lmd - 1:
			return "["	# previous head
		# to the next head
		lmd = head.leftmostDescendant()
		rmd = node.rightmostDescendant()
		if rmd == lmd - 1:
			return "]"	# previous head
		# rules with down
		if parent == headParent and headParent != None:
			return "u" + headSon # up down
		headSibling = self.whichSon(headParent)
		if node == headGParent and headSibling != None:
			return headSibling + headSon	# down down
		if headParent != None and parent != None:
			if parent == headGParent:
				return "u" + headSibling + headSon	# up down down
			if gParent == headParent:
				return "uu" + headSon	# up up down
			if ggParent == headParent:
				return "uuu" + headSon	# up up up down
			if self.parent(ggParent) == headParent:
				return "uuuu" + headSon	# up up up up down
			if gParent != None and gParent == headGParent:
				return "uu" + headSibling + headSon	# up up down down
			if ggParent != None and ggParent == headGParent:
				return "uuu" + headSibling + headSon	# up up up down down
			if headGParent != None and self.parent(ggParent) == headGParent:
				return "uuuu" + headSibling + headSon	# up up up up down down
			if nodeId > 1 and self.parent(self.tokens[nodeId-2]) == headParent:
				return "-1u" + headSon	# left up down
			if nodeId < len(self.tokens) and self.parent(self.tokens[nodeId]) == headParent:
					return "+1u" + headSon	# right up down
		# rules relative to VERB (these are fuzzy)
		if head.cpos == 'V':
			if self.ancestor(head, node):
				return "v"	# verb-up
			if self.ancestor(head, parent):
				return "uv"	# up verb-up
			if self.ancestor(node, head):
				return "V"	# up verb-down
			if self.ancestor(parent, head):
				return "uV"	# up verb-down
			if self.ancestor(gParent, head):
				return "uuV"	# up up verb-down
			if self.ancestor(ggParent, head):
				return "uuuV"	# up up up verb-down
		return "-"

	def whichSon(self, node):
		"Return relative position of node among its siblings relative to parent: -1 means first to its left, -2 last to its left, +1 first to its right, +2 last to its right, -P left with POS P, +P right with POS P"
		if node == None:
			return None
		id = node.id
		parId = node.head
		left = 0		# sons to the left of parId
		right = 0		# sons to the right of parId
		childNo = 0
		leftSamePos = 0
		rightSamePos = 0
		for n in self.tokens:
			if n.id == id:
				childNo = left + right
			if n.head == parId:
				if n.id < parId:
					left += 1
					if n.cpos == node.cpos:
						leftSamePos += 1
				else:
					right += 1
					if n.cpos == node.cpos:
						rightSamePos += 1

		if childNo < left:
			if childNo == left - 1: # closest is the last
				return "d-1"
			elif childNo == 0: # farthest is first
				return "d--"
			else:
				# use cpos ony when unique among children
				if leftSamePos == 1:
					return "d-" + node.cpos
				else:
					return "d-" + str(left - childNo) # reverse numbering since left children in tree are in reverse order
		else:
			if childNo == left: # closest is first
				return "d+1"
			elif childNo == left + right - 1: # farthest is the last
				return "d++"
			else:
				# use cpos ony when unique among children
				if rightSamePos == 1:
					return "d+" + node.cpos
				else:
					return "d+" + str(childNo - left + 1)

	def parent(self, node):
		if node == None:
			return None
		elif node.head == 0:
			return None
		else:
			return self.tokens[node.head-1]

	def ancestor(self, ancestor, descendant):
		if descendant == None:
			return False
		if ancestor == descendant:
			return True
		elif descendant.head == 0:
			return False
		else:
			return self.ancestor(ancestor, self.parent(descendant))

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

	def leftmostDescendant(self):
		# functional version
		# return reduce(min, [c.leftmostDescendant() for c in children], self.id)
		r = self.id
		for c in self.children: r = min(r, c.leftmostDescendant())
		return r

	def rightmostDescendant(self):
		r = self.id
		for c in self.children: r = max(r, c.rightmostDescendant())
		return r

def analyze(file1, file2):
	tokens1 = []
	tokens2 = []
	goldFile = open(file1)
	sysFile = open(file2)
	while True:
		line1 = goldFile.readline()
		line2 = sysFile.readline()
		if line1 == '' and line2 == '':
			break
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

analyze(sys.argv[1], sys.argv[2])
print >> sys.stderr, float(errtot)/errsent, errtot, errsent
