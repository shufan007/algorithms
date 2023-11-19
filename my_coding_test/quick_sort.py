# -*- coding: utf-8 -*-
"""
Created on Wed Mar 21 21:28:33 2018

@author: Administrator
"""

class CQuick_sort():
    def __init__(self):
        self.in_list = None
        
    def __q_sort_partion(self, low, high):

        temp = self.in_list[low]
        while(low < high):
            while(low < high and self.in_list[high] >= temp):
                high -= 1
            self.in_list[low] = self.in_list[high]
                    
            while(low < high and self.in_list[low] <= temp):
                low += 1
            self.in_list[high] = self.in_list[low]

        self.in_list[low] = temp
        
        return low
        
                 
    def __q_sort(self, low, high):
        if(low < high):
            mid = self.__q_sort_partion(low, high)
            self.__q_sort(low, mid-1)
            self.__q_sort(mid+1, high)
            
    def quick_sort(self, in_list):
        self.in_list = in_list
        
        self.__q_sort(0, len(self.in_list)-1)
        return self.in_list
                   

"""
test code
""" 
__list = [2,4,1,5,3,8,7,9,10]   
__list=[3,-2,4,3,1,6,-5,9]
qsort_obj = CQuick_sort()
re_list = qsort_obj.quick_sort(__list)
print(re_list)