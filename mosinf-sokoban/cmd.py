#! /usr/bin/python3 
n = int(input())
s = ("sleep 1 && " + " && ".join(["sleep 0.1 && xdotool key " + str(input().strip()) for i in range(n)]))
import os

os.system(s)
print(s)