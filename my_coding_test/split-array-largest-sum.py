# -*- coding: utf-8 -*-
"""
Created on Sun Apr  7 16:52:51 2019

@author: Administrator
"""

"""
给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。
设计一个算法使得这 m 个子数组各自和的最大值最小

split an array by m parts, get sum of each parts sum_k,
then make max{sum_k} is the smalleast
"""

def splitArray(nums, m):
    n=len(nums)
    segment_sum = [[0]*n for i in range(n)]
    for i in range(n):
        for j in range(i, n):
            segment_sum[i][j] = sum(nums[i:j+1])
            
    max_segment_sum = [[0]*n for i in range(m)]
    max_segment_sum[0][:] = segment_sum[0][:]
    for k in range(1, m):
        for i in range(k,n):
            min_sum_temp = float('inf')
            for j in range(k-1, i):
                curr_max_sum = max(max_segment_sum[k-1][j], segment_sum[j+1][i])
                if(curr_max_sum < min_sum_temp):
                    min_sum_temp = curr_max_sum
            max_segment_sum[k][i] = min_sum_temp

    #print(max_segment_sum)
    return max_segment_sum[m-1][n-1]


def splitArray01(nums, m):
    n=len(nums)
    segment_sum = [[0]*n for i in range(n)]
    for i in range(n):
        for j in range(i, n):
            segment_sum[i][j] = sum(nums[i:j+1])
            
    max_segment_sum = [0 for i in range(n)]
    max_segment_sum = segment_sum[0][:]
    for k in range(1, m):
        for i in range(n-1,k-1,-1):
            min_sum_temp = float('inf')
            for j in range(i-1,k-2,-1):
                curr_max_sum = max(max_segment_sum[j], segment_sum[j+1][i])
                if(curr_max_sum < min_sum_temp):
                    min_sum_temp = curr_max_sum
            max_segment_sum[i] = min_sum_temp

    print(max_segment_sum)
    return max_segment_sum[n-1]


"""
test
"""
nums = [3,5,7,2,10]
#l1 = [3,5,7,10,2]
m=4
min_sum = splitArray(nums, m)
print(min_sum)

nums = [7,2,5,10,8]
m=2
min_sum = splitArray(nums, m)
print(min_sum)