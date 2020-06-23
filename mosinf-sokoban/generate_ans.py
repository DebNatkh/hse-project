import os

for i in range(15):
    print(i)
    os.system("./a.out tests/small_test.txt {} 8 2> /dev/null >> tests/small_ans.txt".format(i)) 

# for i in range(35):
#     print(i)
#     os.system("./a.out tests/big_test.txt {} 8 2> /dev/null >> tests/big_ans.txt".format(i)) 