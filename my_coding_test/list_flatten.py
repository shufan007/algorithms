# -*- coding: utf-8 -*-
"""
Created on Wed Jan 16 19:10:53 2019

@author: Administrator
"""


def list_flatten(in_list, out_list=None):
    out_list = list(out_list) if isinstance(out_list, (list, tuple)) else []
    for item in in_list:
        if isinstance(item, (list, tuple)):
            out_list = list_flatten(item, out_list)
        else:
            out_list.append(item)
    return out_list

    
def ListFlatten(in_list):
    out_list = []
    for item in in_list:
        if isinstance(item, (list, tuple)):
            out_list.extend(list_flatten(item))
        else:
            out_list.append(item)
    return out_list
    
    
"""test"""    
list_ = [1, 2, [3, 4, [5, 6]], ["abc", "def"]] 
vec = [[1,2,3],[4,5,6],[7,8,9],[10,[11,12]]]   
"""
l2 = list_flatten(list_)
l3 = list_flatten(vec)
"""
l2 = ListFlatten(list_)
l3 = ListFlatten(vec)

print l2 ,l3



