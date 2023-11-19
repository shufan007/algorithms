# -*- coding: utf-8 -*-
"""
Created on Wed May  8 22:25:40 2019

@author: Administrator

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。
"""
import copy
class Solution(object):
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        candidates = sorted(candidates)
        candidat_index_dic = dict(zip(candidates, list(range(len(candidates)))))        
        candidate_index = len(candidates)-1            
        output = list()
        allocate = list()        
        while candidates[candidate_index]>target:
            candidate_index -= 1
            if candidate_index<0:
                return output
            
        allocate_num=0
        while True:
            allocate.append(candidates[candidate_index])
            allocate_num += 1
            target -= candidates[candidate_index]
            if target <= 0:
                if target == 0:
                    output.append(copy.deepcopy(allocate))
                while True:
                    target += allocate[-1]
                    tail = allocate.pop()
                    allocate_num -= 1
                    candidate_index = candidat_index_dic[tail]-1
                    if candidate_index >= 0 or allocate_num==0:
                        break
            if candidate_index < 0:
                break
        return output  

"""
test
"""
obj = Solution()
   
candidates = [2,3,6,7]
target = 7

out = obj.combinationSum(candidates, target)
print(out)

candidates = [2,3,5,9,10]
candidates = [5,3,2,9,10]
target = 8

out = obj.combinationSum(candidates, target)
print(out)

candidates = [2]
target = 1

out = obj.combinationSum(candidates, target)
print(out)

