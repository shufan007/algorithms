# -*- coding: utf-8 -*-
"""
Created on Sun Apr 21 22:06:55 2019

@author: Administrator
"""

class Solution(object):
    def canPartition(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        if sum(nums) %2 == 1:
            return False
        
        V=int(sum(nums)/2)
        #print("V: ",V)
        max_v = self.pack01(nums,V)  
        if max_v == V:
            return True
        
    """
    C: cost,value
    V: volume
    """
    def pack01(self,C,V):
        F = [0]*(V+1)
        for i in range(0,len(C)):
            for v in range(V, C[i]-1, -1):
                F[v] = max(F[v], F[v-C[i]]+C[i])

        return F[-1]


"""
test
"""
nums=[2,3,5,7,10,2]

nums=[1, 5, 11, 5]
#nums=[1, 2, 3, 5]


obj = Solution()
ret = obj.canPartition(nums)

print("ret: ", ret)
