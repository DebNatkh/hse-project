#! /usr/bin/python3


def sizeof_fmt(num, suffix='B'):
    for unit in ['','Ki','Mi','Gi','Ti','Pi','Ei','Zi']:
        if abs(num) < 1024.0:
            return "%3.1f%s%s" % (num, unit, suffix)
        num /= 1024.0
    return "%.1f%s%s" % (num, 'Yi', suffix)


import os
tests = os.listdir('converted')
tests.sort()

# {time, answer}

def virt(command):
    tmp_id = "tmp" + str(os.getpid())
    ans = 0
    try:
        os.system("/usr/bin/time -v {} 2>&1 | tail -n 14 | head -n 1 > {}".format(command, tmp_id))
        ans = open(tmp_id, "r").readline().strip().split()[-1]
    except Exception as e:
        return 10*2**30
    return int(ans) * 1024

def info(filename):
    try:
        lines = [l.strip() for l in open(filename, "r").readlines() if len(l.strip())]
    except Exception as e:
        return (1e9, 0)
    if (len(lines) < 2):
        return (1e9, 0)
    else:
        return (float(lines[-1]), int(lines[0]))

from multiprocessing.dummy import Pool as ThreadPool


def f(test):
    result_bal = info("answers/bal_{}".format(test))
    mem_bal = 10*2**30
    if (result_bal[0] < 1e9):
        mem_bal = (virt("../a.out converted/{} 8".format(test)))

    result_end = info("answers/end_{}".format(test))
    mem_end = 10*2**30
    if (result_end[0] < 1e9):
        mem_end = (virt("../a.out converted/{} 0".format(test)))

    result_start = info("answers/start_{}".format(test))
    mem_start = 10*2**30
    if (result_start[0] < 1e9):
        mem_start = (virt("../a.out converted/{} 16".format(test)))


    print(*result_bal, mem_bal, *result_start, mem_start, *result_end, mem_end, test, sep = ",") 


pool = ThreadPool(14)
results = pool.map(f, tests)
