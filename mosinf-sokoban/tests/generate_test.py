#! /usr/bin/python3
import os, sys
outfile = sys.argv[1]


# Small group of tests

tests = ["00162", "00563", "00042", "00094", "00019", "00009", "00043", "00484", "00399", "00093", "00343", "00643", "00308", "00466", "00001"]
f = open("small_" + outfile, "w")
print(len(tests), file = f)
for i in tests:
    print("".join(open("converted/" + i, "r").readlines()).strip(), file = f)
f.close()

# Big group of tests

tests = ["00643", "00529", "00600", "00547", "00460", "00598", "00224", "00234", "00189", "00668", "00596", "00118", "00239", "00464", "00595", "00357", "00178", "00245", "00594", "00512", "00078", "00139", "00578", "00160", "00537", "00018", "00462", "00208", "00458", "00454", "00455", "00528", "00275", "00527", "00285"]
f = open("big_" + outfile, "w")
print(len(tests), file = f)
for i in tests:
    print("".join(open("converted/" + i, "r").readlines()).strip(), file = f)
f.close()