#!/usr/bin/python
# $Id: wordfreq.python,v 1.9 2001/05/11 17:44:00 doug Exp $
# http://www.bagley.org/~doug/shootout/
#
# adapted from Bill Lear's original python word frequency counter
#
# Joel Rosdahl suggested using translate table to speed up
# word splitting.  That change alone sped this program up by
# at least a factor of 3.
#
# with further speedups from Mark Baker

import sys

def main():
    count = {}
    i_r = map(chr, range(256))

    trans = [' '] * 256
    o_a, o_z = ord('a'), (ord('z')+1)
    trans[ord('A'):(ord('Z')+1)] = i_r[o_a:o_z]
    trans[o_a:o_z] = i_r[o_a:o_z]
    trans = ''.join(trans)

    rl = sys.stdin.readlines

    lines = rl(4095)
    while lines:
        for line in lines:
            for word in line.translate(trans).split():
                try:
                    count[word] += 1
                except KeyError:
                    count[word] = 1
        lines = rl(4095)

    l = zip(count.values(), count.keys())
    l.sort()
    l.reverse()

    print '\n'.join(["%7s\t%s" % (count, word) for (count, word) in l])

main()
