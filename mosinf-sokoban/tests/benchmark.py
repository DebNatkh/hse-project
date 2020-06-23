import os
tests = os.listdir('converted')
tests.sort()
tests = tests


from multiprocessing.dummy import Pool as ThreadPool

def f(test):
    print(test)
    result = os.system("timeout 30 ../a.out converted/{} 16 2> /dev/null > answers/{}".format(test, test))
    print(result >> 8) 
    return None


pool = ThreadPool(14)

results = pool.map(f, tests)

pool.close()
pool.join()

print(results)
