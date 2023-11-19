#评测题目：S=[-1,0,1,5,2,-4,4,-5,3,2]，求两个数相加和为target=0，[[-1,1],[-4,4],[-5,5]]

def findsum0pairs(S, target):
	S= quckSort(S)
    start = 0
    end = len(S)-1
    validPair = []
      
    while (start < end):
		if S[start]+S[end] == target:
			validPair.append([S[start], S[end]])
			
			# 注：python 不支持do ... while
			do:
				start += 1
			while (S[start]==S[start+1])
						
			do:
				end -=1
			while (S[end]==S[end-1])
				
		elif S[start]+S[end] < target:
			start += 1
		else:
			end -=1

	return validPair              


def Partition(S, start, end):
    temp = S[start]
    while start < end:
        while (start< end) and (S[end]>=temp):
            end-=1
        S[start]=S[end]        
        while (start< end) and (S[start]<=temp):
            start+=1 
        S[end]=S[start]

    S[start] = temp
    
    return S,start
    
def qSort(S, start,end):
    if(start<end):
        S,mid = Partition(S, start, end)
        S = qSort(S,start, mid-1)
        S = qSort(S, mid+1,end)
    return S
    
          
def quckSort(S):
    S = qSort(S, 0,len(S)-1)
    return S

#test
S=[3,-2,4,3,1,6,-5,9]
print(quckSort(S))
	
string a = "hello world!"
string b = a;
@classmethod
@staticmethod
@property
              
    
    
        
		