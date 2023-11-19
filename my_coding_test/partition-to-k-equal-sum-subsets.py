# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 20:09:08 2019

@author: Administrator
"""
from random import shuffle

class Solution(object):
        
    def canPartitionKSubsets(self, nums, k):
        total_sum = sum(nums)
        self.single_sum = int(total_sum/k)
        if total_sum % self.single_sum != 0:
            return False      
        try_num=5
        while try_num>0:
            ret=self.partitionKSubsets(nums, k)
            try_num-=1
            if ret==True:
                return ret
            else:
                shuffle(nums)
        return ret

    def partitionKSubsets(self, nums, k):
        if k>1:
            max_v, rest_list = self.pack01(nums, self.single_sum) 
            print(max_v,rest_list)
            if max_v != self.single_sum:
                return False
            else:
                return self.partitionKSubsets(rest_list, k-1)
        else:
            if sum(nums) != self.single_sum:
                return False
            else:
                return True
            
    """
    C: cost,value
    V: volume
    """
    def pack01(self,C,V):
        F = [0]*(V+1)
        loc=[None]*(V+1)
        for i in range(0,len(C)):
            for v in range(V, C[i]-1, -1):
                if F[v-C[i]]+C[i]>F[v]:
                    loc[v] = i                
                F[v] = max(F[v], F[v-C[i]]+C[i])
                
        """
        get pick_list
        """
        #print("F",F)
        #print("loc:",loc)
        #pick_list = []
        rest_list = C[:]
        rest = V
        while True:
            pos = loc[rest]
            #print("pos: ",pos)
            if pos==None:
                break
            #pick_list.append(C[pos])
            if C[pos] in rest_list:
                rest_list.remove(C[pos])
                rest -= C[pos]
            else:
                break
            
        #pick_list = pick_list[::-1]
        return F[-1], rest_list
    
"""
test
"""
nums=[2,3,5,7,10,2]

nums=[1, 5, 11, 5]
k=2
#nums=[1, 2, 3, 5]
nums = [4, 3, 2, 3, 5, 2, 1]
k=8
"""
nums =[10,10,10,7,7,7,7,7,7,6,6,6]
k=3
"""

"""
nums=[5,3,1]
k=3
"""

nums =[4403,961,620,436,1762,6018,2382,1370,951,3312]
k=3
obj = Solution()
ret = obj.canPartitionKSubsets(nums,k)

print("ret: ", ret)
