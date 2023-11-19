# -*- coding: utf-8 -*-
"""
Created on Sat Apr 25 18:54:47 2020

@author: Administrator
"""

def LIS(arr):
    lis = [0]*len(arr)
    for i in range(len(arr)):
        lis[i]=1
        for j in range(i):
            if arr[i]>arr[j] and lis[j]+1>lis[i]:
                lis[i] = lis[j]+1
    return max(lis)

arr=[1,-1,2,-3,4,-5,6,-7]
print(LIS(arr))