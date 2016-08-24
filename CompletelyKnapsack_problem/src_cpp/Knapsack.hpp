/************************************************************************************
       [Header File:] Header File
       Function:       Common definations for Knapsack Combination Search
       Author:          Fan, Shuangxi (Nokia - CN/Hangzhou)
       Date:            2016-8-18

 ************************************************************************************/

#ifndef _KNAPSACK_HPP
#define _KNAPSACK_HPP

#include <string>

/***************************************************
 Constant definitions
***************************************************/
#define TOP_LIST_SIZE    60     // set your TOP_LIST_SIZE

#define MaxCaseKinds      100   // set your MaxCaseKinds
#define MaxCaseNum       100   // set your MaxCaseNum

/***************************************************/

//struct of Combination Status
typedef struct {
   int    value; 
   int    cost1;  
   float cost2;  
   int    combinId[MaxCaseNum+1]; 
}CombinStat_T;

typedef struct {
   int size;
   CombinStat_T List[TOP_LIST_SIZE]; 
}TopList_T; 

        
typedef struct{
    int    caseNum;  
    int    caseKinds;    
    int    Values[MaxCaseKinds]; 
    int    Costs1[MaxCaseKinds]; 
    float Costs2[MaxCaseKinds];
    int    limitCost1;
    float  limitCost2;    
}Knapsack_T;


/* *******************************************
    Custom structure definitions 
    ******************************************** */
typedef struct{
    int     depth;
    int     value;
    int     cost1;
    float  cost2;
}BranchRoot_T; 


typedef struct{
    int     caseNum;
    int     depth;
    int     currentMinValue;
    int     searchNum;
    int     updateNum;    
    BranchRoot_T BranchRoot;    
    CombinStat_T Combin;
}AllocInfo_T; 


class CPriorityQueue
{
public:
	
	CPriorityQueue();
	CPriorityQueue(TopList_T*);
	~CPriorityQueue(void);

	void HeapPop();
	void HeapUpdateTop(CombinStat_T*);

private:
	
	TopList_T      * m_topList;
	
	void MinHeapify( int);
	void HeapPush(CombinStat_T*);
	void SwapCombinStats(CombinStat_T* , CombinStat_T*);
	
};


/******************************************************************************
 * @brief CKnapsack
 *
 * The is main class for Knapsack Process.
 [Problem Description:]
 - Combinatorial optimization problem --> resource allocation model
    *  Properties of Knapsack_T: 
        caseNum:         number of cases
        caseKinds:        kind number of cases
        Values: {v_j }   value of the cases
        Costs1: {c1_j}  cost1 of the cases
        Costs2: {c2_j}  cost2 of the cases
        limitOfTotalCost1:  limit value of total cost1
        limitOfTotalCost2:  limit value of total cost2
        x_i:                 resource consumption of user  i
        (Here,  caseNum and caseKinds indicate the input size of the problem.)

    * Constraint Equation:
        object:  max(Sum(v_i)) (i = 1 ,2,......, caseNum)
            s.t
        Sum(c1_i)<= limitOfTotalCost1  (for c1_i in Costs1)
        Sum(c2_i)<= limitOfTotalCost2  (for c2_i in Costs2)
        (The object can also be the top K list)
        
[Algorithm Description:]
* Technical points:
    1. Tree structure is used in the searching process;
    2. Arrange combinations in order;
    3. Greedy search;
    4. Backtracking;
    5. Effcient control process.
* Allocate process:
    * Growth Rules:
        - down:  child <= parent 
        - right: right child < left child
         * this 2 attribute can Make sure the combinations in order in the allocation process.
        - up (backtracking): current value cant't update the top list
         * discard the right branch, back to choose the next valid branch.
        * Greedy Rules: Always choose the biggest valid value.
         * searching always near the optimum combination.

- The allocated rule: the value of the child should no big than the parent's.
- The create process start from first level, if this allocate success, 
  it point to current node level, else it back to its parent level
*  Combinatorial Search: greedy allocate, search near the optimum value.
* If the priority_queue is full and this allocate can't update the priority_queue, then call back.
 - DOWN: New node value allocate only between the parent value and the biggest value;
 - UP(recall): (Trying) Change the parent value to the value of the next index,then go to downward.

[Attributes:] 
    * Fast
    * Not sensitive to the input size
    
* Input: knapsackPtr
* Output: topList        
 *******************************************************************************/
class CKnapsack
{
public:

	CKnapsack();
	CKnapsack(const Knapsack_T*, TopList_T*);
	~CKnapsack(void);


	 /**
	****************************************************************************
	*
	* @brief    KnapsackCombinationSearch
	*
	*  --> resource allocation model
	*
	* @param    -
	*
	***************************************************************************/	
	void KnapsackCombinationSearch();


private:
	FILE             * m_traceFp;
	TopList_T      * m_topList;
	static int         m_count;
	Knapsack_T     m_knapsack;
	AllocInfo_T      m_allocInfo;
	CPriorityQueue m_priorityQueue;
	
	void AllocInfoInit();
	void TraceFileInit();
	void PrintSearchedStatisticsInfo();
	void AllocateProcess();
	void AllocDownStep();
	void NextAllocationControlProcess();
	void AllocRollbackOneStep();
	void AllocRollbackToBranchRoot();
	void TopListUpdate();
	void SearchingLogTrace();
	void PrintArrayToTraceFile( int*, int);

};

#endif /* _KNAPSACK_HPP */


