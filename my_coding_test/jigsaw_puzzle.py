# -*- coding: utf-8 -*-
"""
Created on Sat Nov 23 10:47:15 2019

@author: Administrator
"""
import numpy as np

class JigsawPuzzle(object):
    def __init__(self,_matrix):
        self._matrix = np.array(_matrix)
        self.n=self._matrix.shape[0]
        self.points = self.__get_nonzero_points(_matrix)
        self.min_steps = np.inf
        self.curr_steps = 0
    
    def __get_nonzero_points(self,_matrix):
        points = []
        for i in range(self.n):
            for j in range(self.n):
                if _matrix[i,j]!=0:
                    points.append([i,j])
        return points
        
        
    def __manhattan_distance(self, point1, point2):
        return abs(point1[0]-point2[0]) + abs(point1[1]-point2[1])
        
    def __manhattan_move_path(self, point_s, point_d):
        d_row = point_d[0]-point_s[0]
        d_col = point_d[1]-point_s[1]
        row_start = point_d[0]
        col_start = point_d[1]
        move_path = [[row_start,col_start]]
        while d_row!=0 or d_col!=0:
            if d_row>0:
                if self._matrix[row_start+1,col_start]!=1:
                    self.curr_steps += 1
                    self._matrix[row_start,col_start]=0
                    row_start += 1
                    d_row -= 1
                    self._matrix[row_start,col_start]=1
                    move_path.append([row_start,col_start])
            elif d_row<0:
                if self._matrix[row_start-1,col_start]!=1:
                    self.curr_steps += 1
                    self._matrix[row_start,col_start]=0
                    row_start -= 1
                    d_row += 1
                    self._matrix[row_start,col_start]=1
                    move_path.append([row_start,col_start])        
        
            if d_col>0:
                if self._matrix[row_start,col_start+1]!=1:
                    self.curr_steps += 1
                    self._matrix[row_start,col_start]=0
                    col_start += 1
                    d_col -= 1
                    self._matrix[row_start,col_start]=1
                    move_path.append([row_start,col_start])
            elif d_col<0:
                if self._matrix[row_start,col_start-1]!=1:
                    self.curr_steps += 1
                    self._matrix[row_start,col_start]=0
                    col_start -= 1
                    d_col += 1
                    self._matrix[row_start,col_start]=1
                    move_path.append([row_start,col_start])  
                    
            if self.curr_steps>self.min_steps:
                return
            
        return move_path
    
    def point_to_line_dist(point,line_idx,line_type):
        # line_type: 0->row, 1->col
        if line_type==0:
            
            self.__manhattan_distance(point1, point2)
        
    
"""
test
"""  

def generate_init_matrix(n):
    _matrix = np.zeros((n,n))
    row_index=np.random.randint(0,n,n)
    col_index=np.random.randint(0,n,n)
    _matrix[row_index,col_index] = 1
    return _matrix
    
    
lobj = JigsawPuzzle()
count = lobj.loveNO('09')  
print(count)  

count = lobj.loveNO('12345')  
print(count)    

count = lobj.loveNO('18768146301')  
print(count)    

count = lobj.loveNO('13656640877')  
print(count)    