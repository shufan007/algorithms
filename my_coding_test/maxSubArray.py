# -*- coding: utf-8 -*-
"""
Created on Sun May 19 22:09:14 2019

@author: Administrator
"""

class Solution(object):
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_ = nums[0]
        L_S = nums[0]
        for num_i in nums[1:]:
            if L_S > 0:
                L_S += num_i
            else:
                L_S = num_i
            if L_S > max_:
                max_ = L_S
        return max_

"""
test
"""
nums = [-2,1,-3,4,-1,2,1,-5,4]
obj = Solution()
out = obj.maxSubArray(nums)
print(out)

nums = [-2]
obj = Solution()
out = obj.maxSubArray(nums)
print(out)          