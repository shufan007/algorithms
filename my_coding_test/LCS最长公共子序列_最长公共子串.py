# -*- coding: utf-8 -*-
"""
Created on Sat Apr 25 17:59:46 2020

@author: Administrator
"""

"""
############## 最长公共子序列（LCS）################

最长公共子序列 VS 最长公共子串：
找两个字符串的最长公共子串，这个子串要求在原字符串中是连续的。而最长公共子序列则并不要求连续。

求解思路：

1.分析最优解的结构特征：
设Zk={z1,z2,z3,......zk}是Xm={x1,x2,x3,......xm}和Yn={y1,y2,y3,......yn}的最长公共子序列。
则可以得到：
若xm=yn=zk，那么Zk-1={z1,z2,z3,......zk-1}是Xm-1={x1,x2,x3,......xm-1}和Yn-1={y1,y2,y3,......yn-1}的最长公共子序列；
若xm≠yn，xm≠zk，则去除xm后，Zk={z1,z2,z3,......zk}仍然是Xm-1={x1,x2,x3,......xm-1}和Yn={y1,y2,y3,......yn}的最长公共子序列；
若xm≠yn，yn≠zk，则去除yn后，Zk={z1,z2,z3,......zk}仍然是Xm={x1,x2,x3,......xm}和Yn-1={y1,y2,y3,......yn-1}的最长公共子序列；

2.建立最优值的递归式
数据结构选择：
用c[i][j]表示Xi和Yj的最长公共子序列长度（这一步很关键，越到右下角，值会越来越大，我们最后只需要选取右下角的值就可以确定最长公共子序列的长度）
讨论：
若xi=yj=zk，那么c[i][j] = c[i-1][j-1] + 1；
若xi≠yj，xi≠zk，那么Xi需要进一步缩小一个长度进行匹配，即去除xi不影响整体的最长子序列变化，c[i][j] = c[i-1][j] ；
若xi≠yj，yj≠zk，那么Yj需要进一步缩小一个长度进行匹配，即去除yj不影响整体的最长子序列变化，c[i][j] = c[i][j-1] ；
结束条件，若i=0或者j=0，则c[i][j]=0。
所以，在xi≠yj的情况下，有两种情况，c[i][j]必等于两种情况下的最大值，即c[i][j] = max(c[i-1][j], c[i][j-1])

"""

def LCS(string1,string2):
    len1 = len(string1)
    len2 = len(string2)
    res = [[0 for i in range(len1+1)] for j in range(len2+1)]
    for i in range(1,len2+1):
        for j in range(1,len1+1):
            if string2[i-1] == string1[j-1]:
                res[i][j] = res[i-1][j-1]+1
            else:
                res[i][j] = max(res[i-1][j],res[i][j-1])
    return res[-1][-1]
print(LCS("helloworld","loop"))

 
"""
############## 最长公共子串 ################

和LCS问题唯一不同的地方在于当A[i] != B[j]时，res[i][j]就直接等于0了，因为子串必须连续，且res[i][j] 表示的是以A[i]，B[j]截尾的公共子串的长度。
这个和LCS问题还有一点不同的就是，需要设置一个res，每一步都更新得到最长公共子串的长度。
"""
def LCstring(string1,string2):
    len1 = len(string1)
    len2 = len(string2)
    res = [[0 for i in range(len1+1)] for j in range(len2+1)]
    result = 0
    for i in range(1,len2+1):
        for j in range(1,len1+1):
            if string2[i-1] == string1[j-1]:
                res[i][j] = res[i-1][j-1]+1
                result = max(result,res[i][j])  
    return result
print(LCstring("helloworld","loop"))
