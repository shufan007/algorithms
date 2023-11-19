# -*- coding: utf-8 -*-
"""
Created on Wed Jan 16 19:10:53 2019

@author: Administrator
"""

"""
C: cost
W: value
V: volume
"""
def pack01(C,W,V):
    F = [0]*(V+1)
    loc=[None]*(V+1)
    for i in range(0,len(W)):
        for v in range(V, C[i]-1, -1):
            if F[v-C[i]]+W[i]>F[v]:
                loc[v] = i
            F[v] = max(F[v], F[v-C[i]]+W[i])
    """
    get pick_list
    """
    print("loc:",loc)
    pick_list = []
    rest = V
    while True:
        pos = loc[rest]
        if pos==None:
            break
        
        pick_list.append(C[pos])
        rest -= C[pos]
        
    pick_list = pick_list[::-1]
    print("F:", F)
    #print("pick_list:", pick_list)
    return F[-1], pick_list


"""
test
"""
W=[2,3,5,7,10,2]

C=W
V=int(sum(W)/2)
print("V: ",V)
max_v, pick_list = pack01(C,W,V)

print("max_v: ", max_v)
print("pick_list: ", pick_list)