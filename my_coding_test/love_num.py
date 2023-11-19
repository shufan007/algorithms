# -*- coding: utf-8 -*-
"""
Created on Sat Nov 23 10:47:15 2019

@author: Administrator
"""
class CLoveNO(object):
    def __init__(self):
        pass 
    def __next(self, last, i):
        sum0 = last + self.num[i]
        next0 = sum0//2
        rest = sum0%2
        self.valid[i] = next0
        if i==self.n-1:
            s1 = ''.join([str(j) for j in self.valid])
            if s1 != self.num_s:
                self.count += 1
            if rest:
                if s1[:-1]+str(next0+1) != self.num_s:
                    self.count += 1
        else:
            self.__next(next0, i+1)
            if rest:
                self.valid[i] = next0+1
                self.__next(next0+1, i+1)                                
    def loveNO(self,num_s): 
        self.num_s = num_s
        self.num = [int(i) for i in num_s]
        self.count = 0
        self.n = len(num_s)
        self.valid = [0]*self.n
        for i in range(10):
            self.valid[0] = i
            self.__next(i, 1)
        return self.count
        

"""
test
"""  
lobj = CLoveNO()
count = lobj.loveNO('09')  
print(count)  

count = lobj.loveNO('12345')  
print(count)    

count = lobj.loveNO('18768146301')  
print(count)    

count = lobj.loveNO('13656640877')  
print(count)    