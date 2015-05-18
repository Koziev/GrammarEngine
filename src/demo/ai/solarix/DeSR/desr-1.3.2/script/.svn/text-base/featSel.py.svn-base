#!/usr/bin/python

# Generate all possible configuration variants by removing a single feature

import sys;
import os;
import commands;

if len(sys.argv) < 3:
	print 'usage:', sys.argv[0], 'basename results [alg]'
	sys.exit()

alg = "ME"
if len(sys.argv) == 4:
	alg = sys.argv[3]

basename = sys.argv[1]
inFile = open(basename + ".max")
results = open(sys.argv[2], "wa")

baseconf = '''
UseChildPunct	true
StackSize	true
InputSize	false
VerbCount	true
PastActions	1
WordDistance	false
PunctCount	false
UseFinePOS	true

SecondOrder	false
FeatPairs	true
MEiter		30
ApIterations	5
PaIterations	5
'''

featCount = 0
options = {}
while True:
    line = inFile.readline()
    if line == '':
        break
    params = line.split()
    name = params[0]
    feats = params[1:]
    featCount += len(feats)
    options[name] = feats

for variant in range(0, featCount):
    count = 0
    config = basename + str(variant) + ".conf"
    outFile = open(config, "w")
    for name, feats in options.items():
        print >> outFile, name,
        for f in feats:
            if variant != count:
                print >> outFile, f,
            count += 1
        print >> outFile
    print >> outFile, baseconf
    outFile.close()
    model = basename + "." + alg
    if os.path.exists(model):
	    os.remove(model)
    os.system("make ALG=" + alg + " CONF=" + config + " " + basename + "-" + alg)
    print >> results, config
    print >> results, commands.getoutput("grep attachment " + basename + "-"+ alg + ".eval")
    results.flush()
results.close()
