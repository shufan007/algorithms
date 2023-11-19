# -*- coding: utf-8 -*-
"""
将数字转为字符串，26进制
题目：写一个正整数转字符串函数，语言（python，java，c/c++），转换规则如下：
# 1-A
# 2-B
# ...
# 26-Z
# 27-AA
# 28-AB
# ...
# 52-AZ
# 53-BA
# 54-BB
# ...
# 702-ZZ
# 703-AAA
# ...
"""

def num_to_str(num):
    car_list = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
    num_list = list(range(1,26+1))
    num_c_dic = dict(zip(num_list,car_list))
    base = 26
    str_list = []
    while num>=1:
        res = num%(base)
        if res !=0:
            str_list.insert(0,num_c_dic[res])
        else:
            str_list.insert(0,car_list[-1])
            res=base
        num = int((num-res)/base)
     
    return ''.join(str_list)

"""
test cases
"""
print(num_to_str(1))
print(num_to_str(2))
print(num_to_str(26))

print(num_to_str(27))
print(num_to_str(28))

print(num_to_str(52))
print(num_to_str(53))
print(num_to_str(54))

print(num_to_str(702))
print(num_to_str(703))