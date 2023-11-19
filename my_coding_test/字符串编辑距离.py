# -*- coding: utf-8 -*-
"""
求两个字符串的编辑距离：

当 min(i, j) \ne 0 的时候，lev_{a,b}(|a|, |b|) 为如下三种情况的最小值：
1.lev_{a,b}(i-1, j) + 1 表示 删除 a_i
2.lev_{a,b}(i, j-1) + 1 表示 插入 b_j
3.lev_{a,b}(i-1, j-1)+1_{(a_i \ne b_j)} 表示 替换 b_j
"""

"""
递归法
"""
def Levenshtein_Distance_Recursive(str1, str2):

    if len(str1) == 0:
        return len(str2)
    elif len(str2) == 0:
        return len(str1)
    elif str1 == str2:
        return 0

    if str1[len(str1)-1] == str2[len(str2)-1]:
        d = 0
    else:
        d = 1
    
    return min(Levenshtein_Distance_Recursive(str1, str2[:-1]) + 1,
                Levenshtein_Distance_Recursive(str1[:-1], str2) + 1,
                Levenshtein_Distance_Recursive(str1[:-1], str2[:-1]) + d)

print(Levenshtein_Distance_Recursive("abc", "bd"))


"""
动态规划法
"""
def Levenshtein_Distance(str1, str2):
    """
    计算字符串 str1 和 str2 的编辑距离
    :param str1
    :param str2
    :return:
    """
    matrix = [[ i + j for j in range(len(str2) + 1)] for i in range(len(str1) + 1)]

    for i in range(1, len(str1)+1):
        for j in range(1, len(str2)+1):
            if(str1[i-1] == str2[j-1]):
                d = 0
            else:
                d = 1
            
            matrix[i][j] = min(matrix[i-1][j]+1, matrix[i][j-1]+1, matrix[i-1][j-1]+d)

    return matrix[len(str1)][len(str2)]


print(Levenshtein_Distance("abc", "bd"))