# -*- coding: utf-8 -*-
"""
Created on Thu May  7 21:29:44 2020

@author: Administrator
"""

def Partition(S, start, end):
    temp = S[start]
    while start < end:
        while (start< end) and (S[end]>=temp):
            end-=1
        S[start]=S[end]        
        while (start< end) and (S[start]<=temp):
            start+=1 
        S[end]=S[start]

    S[start] = temp
    
    return S,start
    
def qSort(S, start,end):
    if(start<end):
        S,mid = Partition(S, start, end)
        S = qSort(S,start, mid-1)
        S = qSort(S, mid+1,end)
    return S
    
          
def quckSort(S):
    S = qSort(S, 0,len(S)-1)
    return S

#test
S=[3,-2,4,3,1,6,-5,9]
print(quckSort(S))