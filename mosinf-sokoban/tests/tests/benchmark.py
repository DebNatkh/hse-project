#! /usr/bin/python3
import os
tests = os.listdir('converted')
tests.sort()
tests = tests


from multiprocessing.dummy import Pool as ThreadPool

def f(test):
    print(test)
    result = os.system("timeout 300 ../a.out converted/{} 16 2> /dev/null > answers/start_{}".format(test, test))
    result = os.system("timeout 300 ../a.out converted/{} 0 2> /dev/null > answers/end_{}".format(test, test))
    result = os.system("timeout 300 ../a.out converted/{} 8 2> /dev/null > answers/bal_{}".format(test, test))
    print(result >> 8) 
    return None


pool = ThreadPool(15)

results = pool.map(f, tests)

pool.close()
pool.join()

print(results)
