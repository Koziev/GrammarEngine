#!/usr/bin/python

# =============================================================================
#  Version: 1.1 (Nov 21, 2009)
#  Authors: Stefano Dei Rossi (deirossi@di.unipi.it), University of Pisa
#  	    Giuseppe Attardi (attardi@di.unipi.it), University of Pisa
# =============================================================================

# =============================================================================
#  This file is part of Tanl.
#
#  Tanl is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License, version 3,
#  as published by the Free Software Foundation.
#
#  Tanl is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
# =============================================================================

"""Model converter:
Converts DeSR model files from version 1.1.2 to the newer version 1.1.3.

The converter reads from stdin a model file created with DeSR version 1.1.2
and generates on standard output a model compatible with DeSR version 1.2.0.

Usage:
  convertModel.py < old-model-file > new-model-file
"""

import sys
import re
import getopt

# RegExp for numbers and symbols
rxp = re.compile('[0-9-+\\\/]*')

# Flag to identify the beginning of the feature list
inHeader = True

conversion = { 'D' : 'A',
               'B' : 'D',
               'E' : 'F',
               'H' : 'B'
}

# Read from stdin
for line in sys.stdin:
    line = line.strip()

    # Inside feature list
    if inHeader:
        # Find the beginning of the feature list
        if line == "</desr>":
            inHeader = False
    elif line.startsWith('A0'):
        line = 'a0' + line[2:]
    else:
        m = rxp.match(line)
        # Convert feature code chars
        if m:
            codeChar = m.end()
            line = line[0:codeChar] + conversion[line[codeChar]] + line[codeChar+1:]

    # Print to stdout
    print line
 
