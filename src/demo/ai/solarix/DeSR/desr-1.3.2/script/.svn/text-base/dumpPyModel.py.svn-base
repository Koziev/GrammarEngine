#!/usr/bin/env python

# Creates MLP model by from Neural Network model, parameter file (.yaml)
# and prototype header file.

import re
import sys
import cPickle
import array

if len(sys.argv) != 4:
    arg = sys.argv[1]
    if arg == '-h':
        print 'usage:', sys.argv[0], 'modelFile paramFile headerFile'
        sys.exit(0)

modelFile = sys.argv[1]
paramFile = sys.argv[2]
headerFile = sys.argv[3]

# use binary mode to avoid adding \r
if sys.platform == "win32":
        import os, msvcrt
        msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

# extract parameters from paramFile
for line in open(paramFile):
    m = re.search(r"hidden dimensions: (\d+)", line)
    if m:
        MlpHidden = m.group(1)
    m = re.search(r"hidden layers: (\d+)", line)
    if m:
        MlpLayers = m.group(1)

# copy the headerFile with these parameters
for line in open(headerFile):
    if re.search("MlpHidden", line):
        print "MlpHidden	%s" % MlpHidden
    elif re.search("MlpLayers", line):
        print "MlpLayers	%s" % MlpLayers
    else:
        print line,

import common.featuremap
labelmap = common.featuremap.get(name="labels")
featuremap = common.featuremap.get(name="features")
labelmap.readonly = True
featuremap.readonly = True

l = len(labelmap.map)
print l
for i in range(l):
    print labelmap.str(i)

l = len(featuremap.map)
print l
for i in range(l):
    print featuremap.str(i)

model = cPickle.load(open(modelFile))
(w1, b1, w2, b2) = model
numFeats = w1.shape[0]
numHidden = w1.shape[1]
numOutcomes = len(b2)

print numHidden
print numFeats * numHidden
for i in range(numFeats):
    array.array('d', w1[i]).tofile(sys.stdout)

print numHidden
array.array('d', b1).tofile(sys.stdout)

print numHidden * numOutcomes
for i in range(numHidden):
    array.array('d', w2[i]).tofile(sys.stdout)

print numOutcomes
array.array('d', b2).tofile(sys.stdout)

# no entities:
print 0
print 0
