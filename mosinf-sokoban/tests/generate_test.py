#! /usr/bin/python3
import os, sys

filename = sys.argv[1]
outfile = sys.argv[2]
print(filename)

def fmt(i):
    return "{:05d}".format(i)

f = open(outfile, "w")

import csv

tests = ["00643", "00529", "00600", "00547", "00460", "00598", "00224", "00234", "00189", "00668", "00596", "00118", "00239", "00464", "00595", "00357", "00178", "00245", "00594", "00512", "00078", "00139", "00578", "00160", "00537", "00018", "00462", "00208", "00458", "00454", "00455", "00528", "00275", "00527", "00285"]
# with open(filename, newline='') as csvfile:
#     spamreader = csv.reader(csvfile, delimiter=',')
#     for row in spamreader:
#         if (row[-1] != ""):
#             test = fmt(int(row[3]))
#             tests.append(test)
print(len(tests), file = f)
for i in tests:
    print("".join(open("converted/" + i, "r").readlines()).strip(), file = f)
f.close()