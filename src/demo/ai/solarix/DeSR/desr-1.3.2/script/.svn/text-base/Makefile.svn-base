######################################################################
# This is the Makefile to train a parser in various configurations,
# including the tree revision version, as described in:
#   G. Attardi, F. Dell'Orletta. Reverse Revision and Linear Tree Combination for Dependency Parsing. Proc. of NAACL HLT 2009, 2009. 
#	http://www.di.unipi.it/~attardi/Paper/NAACL09.pdf
#
# Several runs can then be combined.
# The different runs can be chosen specifing different configuration files,
# named with variable CONF.
#
# Running the Reverse Revision, requires a variant of the basic configuration
# file, named by variable CONFGUIDE, where additional features are mentioned,
# that are extracted with the script extractGuides.py
# The additional features are named with the following conventions:
#  P stands for Predicted
#  H stands for Head
# so for example PHHLEMMA means the predicted head of head of lemma.
# Here is a configuration that we typically use:
#
# Features	PHLEMMA -1 0 1
# Features	PDEP -1 0 1
# Features	PHPOS -1 0 1
# Features	PLOC 0 1
# Features	PHDEP -1 0 1
# Features	PHHLEMMA 0 1

######################################################################
# Parameters
######################################################################

# Set these to the base names of the train and test set files (which should
# have the extension .conll)
TRAIN=train
TEST=test

ALG=MLP
# alternative value
#ALG=SVM

# Beam size
BEAM=

# Configuration file
CONF=english.conf
CONFGUIDE=englishGuided.conf

# Parsing mode
MODE=
# possible values
# '' normal: left to right
# -R reverse: right to left
# -rev Forward Revision
# -rev2 Reverse Revision

######################################################################
# Targets
######################################################################

all:
	$(MAKE) -s $(TEST).$(ALG)-eval
	$(MAKE) -s $(TEST).$(ALG)-R.eval MODE=-R
	$(MAKE) -s $(TEST).$(ALG)-rev.eval MODE=-rev
	$(MAKE) -s $(TEST).$(ALG)-rev2.eval MODE=-rev2

######################################################################
#### Parametric rules
######################################################################

# Must list separately since -rev2, -rev have specific rules
$(TRAIN).$(ALG) $(TRAIN).$(ALG)-R: $(TRAIN).conll
	desr -c $(CONF) -a$(ALG) $(BEAM) $(MODE) -t -m $@ $(TRAIN).conll 2> $(TRAIN).$(ALG)$(MODE).out

# Must list separately since -rev2, -rev have specific rules
$(TEST).$(ALG).conll $(TEST).$(ALG)-R.conll: $(TRAIN).$(ALG)$(MODE) $(TEST).conll
	desr -m $(TRAIN).$(ALG)$(MODE) $(TEST).conll > \
	$(TEST).$(ALG)$(MODE).conll

$(TEST).$(ALG)$(MODE).eval: $(TEST).conll $(TEST).$(ALG)$(MODE).conll
	eval07.pl -q -g $(TEST).conll -s $(TEST).$(ALG)$(MODE).conll > $@

######################################################################
# Revision Parsing
######################################################################

# Train poor parser

POOR=ME

$(TRAIN).$(POOR).conll: $(TRAIN).conll
	$(MAKE) -s ALG=$(POOR) VER=$(VER) MODE= BEAM=-b1 $(TRAIN).$(POOR)
	desr -m $(TRAIN).$(POOR) $(TRAIN).conll > $@

$(TRAIN).$(POOR)-R.conll: $(TRAIN).conll
	$(MAKE) -s ALG=$(POOR) VER=$(VER) MODE=-R BEAM=-b1 $(TRAIN).$(POOR)-R
	desr -m $(TRAIN).$(POOR)-R $(TRAIN).conll > $@

# Create guided file from parser output

%.$(ALG).conllXGuide: %.$(ALG).conll
	extractGuides.py $*.conll $< > $@

%.$(POOR).conllXGuide: %.$(POOR).conll
	extractGuides.py $*.conll $< > $@

%.$(ALG)-R.conllXGuide: %.$(ALG)-R.conll
	extractGuides.py $*.conll $< > $@

%.$(POOR)-R.conllXGuide: %.$(POOR)-R.conll
	extractGuides.py $*.conll $< > $@

# ======================================================================

# Train Forward Revision (rev) parser using guides from poor parser

$(TRAIN).$(ALG)-rev: $(TRAIN).$(POOR)-R.conllXGuide
	desr -c $(CONFGUIDE) -a$(ALG) -t -m $@ $(TRAIN).$(POOR)-R.conllXGuide 2> $@.out

# Parse dev/test set with Forward Revision parser
$(TEST).$(ALG)-rev.conll: $(TRAIN).$(ALG)-rev
#	1. parse in reverse
#	$(MAKE) -s MODE=-R $(TEST).$(ALG)-R.conll
#	2. add guides for stacked parser
	$(MAKE) -s MODE=-R $(TEST).$(ALG)-R.conllXGuide
#	3. parse with Rev model
	desr -m $(TRAIN).$(ALG)-rev $(TEST).$(ALG)-R.conllXGuide > $@

# ======================================================================

# Train Reverse Revision (rev2) parser using guides from poor parser

$(TRAIN).$(ALG)-rev2: $(TRAIN).$(POOR).conllXGuide
	desr -c $(CONFGUIDE) -a$(ALG) -R -t -m $@ $(TRAIN).$(POOR).conllXGuide 2> $@.out

# Parse dev/test set with Reverse Revision parser
$(TEST).$(ALG)-rev2.conll: $(TRAIN).$(ALG)-rev2
#	1. parse (invoke esplicitely with MODE=)
#	$(MAKE) -s MODE= $(TEST).$(ALG).conll
#	2. add guides for reverse parsing
	$(MAKE) -s MODE= $(TEST).$(ALG).conllXGuide
#	3. parse in reverse with Rev2
	desr -m $(TRAIN).$(ALG)-rev2 $(TEST).$(ALG).conllXGuide > $@


######################################################################
# Parser combination

# 3-way merge

# In this example we combine three versions:
#
#  $(TEST).MLP-rev.conll	obtained using MLP in reverse direction
#  $(TEST).SVM-rev2.conll	obtained using SVM in reverse revision
#  $(TEST).MLP-rev2.conll	obtained using MLP in reverse revision

$(TEST).MLP-rev+SVM-rev2+MLP-rev2.conll:
	$(MAKE) -s ALG=MLP REV=-rev $(TEST).MLP-rev.conll
	$(MAKE) -s ALG=SVM REV=-rev2 $(TEST).SVM-rev2.conll
	$(MAKE) -s ALG=MLP REV=-rev2 $(TEST).MLP-rev2.conll
	treeCombineNoWeight.py $(TEST).MLP-rev.conll $(TEST).SVM-rev2.conll $(TEST).MLP-rev2.conll > $@

$(TEST).MLP-rev+SVM-rev2+MLP-rev2.eval: $(TEST).MLP-rev+SVM-rev2+MLP-rev2.conll
	eval07.pl -q -g $(TEST).conll -s $< > $@
