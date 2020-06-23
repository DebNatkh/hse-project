#! /bin/bash
g++ ../files/gen.cpp -std=c++17 -o gen
./gen 1 > input_small.txt
./gen 2 > input_large.txt
rm gen