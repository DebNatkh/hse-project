#! /usr/bin/python3
import os
import sys

def mex(arr):
    s = {int(i) for i in arr}
    for i in range(len(arr) + 1):
        if (i not in s):
            return i

def fmt(i):
    return "{:05d}".format(i)

def freeNum():
    return mex(os.listdir('./converted'))

def generateLevel(lines):
    lines = [i.rstrip() for i in lines if i.strip() != ""]
    n = len(lines)
    m = max(len(l) for l in lines)
    lines = [(len(l) - len(l.lstrip())) * "#" + l.lstrip() + "#" * (m - len(l)) for l in lines]
    lines = [list(l) for l in lines]

    crates = set()
    targets = set()
    start = (-1, -1)

    for i in range(n):
        for j in range(m):
            if (lines[i][j] == ' '):
                lines[i][j] = '.'
            elif (lines[i][j] == '$'):
                lines[i][j] = '.'
                crates.add((i + 1, j + 1))
            elif (lines[i][j] == '.'):
                lines[i][j] = '.'
                targets.add((i + 1, j + 1))
            elif (lines[i][j] == '*'):
                lines[i][j] = '.'
                targets.add((i + 1, j + 1))
                crates.add((i + 1, j + 1))
            elif (lines[i][j] == '@'):
                lines[i][j] = '.'
                start = (i + 1, j + 1)
            elif (lines[i][j] == '+'):
                lines[i][j] = '.'
                targets.add((i + 1, j + 1))
                start = (i + 1, j + 1)


    lines = ["".join(l) for l in lines]

    filename = "converted/" + fmt(freeNum())
    print(filename)
    fd = open(filename, "w")
    print(n, m, file = fd)
    print("\n".join(lines), file = fd)
    print(*start, file = fd)
    print(len(crates), file = fd)
    for i in crates:
        print(*i, file = fd)        
    for i in targets:
        print(*i, file = fd)
    fd.close()



if (len(sys.argv) < 2):
    print("Usage: converter.py filename.txt")
    exit(0)
filename = sys.argv[1]
buf = []
for line in open(filename, "r").readlines():
    if (line.startswith(";")):
        generateLevel(buf)
        buf = []
    else:
        buf.append(line)