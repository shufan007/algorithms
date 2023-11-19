# -*- coding: utf-8 -*-
"""
Created on Sun Apr  7 16:52:51 2019

@author: Administrator
"""

"""
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 
返回你可以获得的最大乘积。
"""
import math
class Solution(object):
    def integerBreak(self, n):
        """
        :type n: int
        :rtype: int
        """   
        sqrt_n = math.sqrt(n)
        s0 = int(sqrt_n)
        m = int(n/s0)
        rest = n%s0
        s0_num = m-rest
        ret = s0**s0_num*(s0+1)**rest
        
        s1=s0
        ret1 = ret
        if sqrt_n > s0:
            s1 = s0+1 
        if s1!=s0:
            m=int(n/s1)
            rest = n%s1
            if m>1 or rest>0:
                if rest > 0:
                    ret1 = s1**m*rest
                else:
                    ret1 = s1**m
        if ret1>ret:
            ret = ret1
            
        return ret
        

"""
test
"""
n=2
obj = Solution()
out = obj.integerBreak(n)
print(out)

n=3
obj = Solution()
out = obj.integerBreak(n)
print(out)

n=6
obj = Solution()
out = obj.integerBreak(n)
print(out)

n=10
obj = Solution()
out = obj.integerBreak(n)
print(out)

n=11
obj = Solution()
out = obj.integerBreak(n)
print(out)

n=58
obj = Solution()
out = obj.integerBreak(n)
print(out)
