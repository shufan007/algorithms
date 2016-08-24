/************************************************************************************
       Function:       Searching Algorithm for Knapsack Combination Search
       Author:         Fan, Shuangxi (Nokia - CN/Hangzhou)
       History:
       
       0.8           (2015 -3 -20)   Implement the algorithm
       1.0           (2015 -5 -7 )    Reconsitution, 
 ************************************************************************************/
//#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Knapsack.hpp"

/***************************************************
 Global Definations
***************************************************/
//#define __DEBUE__

#define SEARCH_TRACE    "SearchingTrace"
#define MAX_SEARCH      1000000

#define GLO_TRUE       1
#define GLO_FALSE      0

#define  EPS                0.001     // used for judge the equality of float type
#define STR_LEN         50

/*  operators of tree struct, for heap process  */
#define PARENT(i) (((i+1)>>1)-1)
#define LEFT(i)      ((i<<1)+1)
#define RIGHT(i)   ((i<<1)+2)


int CKnapsack::m_count  = 0;

CKnapsack::CKnapsack(){}

CKnapsack::CKnapsack(const Knapsack_T* knapsack, TopList_T* topList):m_priorityQueue(topList)
{
	assert(knapsack != NULL);
	assert(topList != NULL);
		
	m_traceFp        = NULL;
	
	memcpy(&m_knapsack, knapsack, sizeof(Knapsack_T));

	AllocInfoInit();

#ifdef __DEBUE__
	TraceFileInit();    
#endif	
	
	m_topList = topList;

	m_count++; 
	
}

CKnapsack::~CKnapsack(void){}


void CKnapsack::KnapsackCombinationSearch() 
{

    /*************************************************
    *  main searching process
    m_allocInfo.depth: to indicate the point to be spread,  
    when depth back to -1 means the allocate process complete
    **************************************************/      
    while (m_allocInfo.depth >= 0)
    {
        AllocateProcess();

        if (m_allocInfo.depth == m_allocInfo.caseNum)
        {  
            TopListUpdate();
        }
            
#ifdef __DEBUE__
        SearchingLogTrace();
#endif 

        if (m_allocInfo.searchNum >= MAX_SEARCH)
        {
            printf(" *** Hit the max search number: %d !\n", MAX_SEARCH);
            break;
        }
      
        NextAllocationControlProcess();          
    }
    
    PrintSearchedStatisticsInfo();

}//----------------------------------------------------------------------------------


void CKnapsack::AllocInfoInit()
{
    memset(&m_allocInfo, 0, sizeof(AllocInfo_T));
    
    m_allocInfo.caseNum = m_knapsack.caseNum;

    memset(m_allocInfo.Combin.combinId, 0, sizeof(int)*(m_allocInfo.caseNum+1));   
    m_allocInfo.Combin.combinId[0] = m_knapsack.caseKinds -1; // init the first value 
}


void CKnapsack::TraceFileInit()
{
    char fileName[STR_LEN];
    
    sprintf(fileName, "%s_%d.txt", SEARCH_TRACE, m_count);
    
    m_traceFp  = fopen(fileName, "w");
    assert(m_traceFp != NULL);
    
    fprintf(m_traceFp, "\n case Kinds: %d\n case number: %d\n limitCost1: %d\n limitCost2: %d\n", 
        m_knapsack.caseKinds, m_knapsack.caseNum, m_knapsack.limitCost1, m_knapsack.limitCost2);
    fprintf(m_traceFp, " \"==>\": input topList\n");
    fprintf(m_traceFp, "------------------------------------\n");
}

void CKnapsack::PrintSearchedStatisticsInfo()
{    
    printf( "   Search: %d, Update: %d\n", m_allocInfo.searchNum, m_allocInfo.updateNum);
    
    if (NULL != m_traceFp)
    {
        fprintf(m_traceFp, "\n [ * Search: %d, Update: %d ]\n", m_allocInfo.searchNum, m_allocInfo.updateNum);
        fclose(m_traceFp);
    }    
}


/***********************************************************
Module Function: Allocate this branch
    *  if all conditions match, then this branch can be allocated successfully,
        else, it will keep track of the current records, then break
************************************************************/
void CKnapsack::AllocateProcess()
{
    int maxPermitValue;

    while ((m_allocInfo.Combin.combinId[m_allocInfo.depth] >= 0) && (m_allocInfo.depth < m_allocInfo.caseNum))
    {
        maxPermitValue = m_allocInfo.Combin.value + m_knapsack.Values[m_allocInfo.Combin.combinId[m_allocInfo.depth]]*(m_allocInfo.caseNum - m_allocInfo.depth);    

        if (maxPermitValue > m_allocInfo.currentMinValue)
        { 
            AllocDownStep();
        }
        else    /* If can't allocate anymore, save the current value to the index of caseNum, then break */
        {
            m_allocInfo.Combin.combinId[m_allocInfo.caseNum] = m_allocInfo.Combin.combinId[m_allocInfo.depth];            
            break;
        }
    }
    
    m_allocInfo.searchNum ++;
     
}


void CKnapsack::AllocDownStep()
{
    int     minPermitCost1;
    float  minPermitCost2;
    
    minPermitCost1 = m_allocInfo.Combin.cost1 + m_knapsack.Costs1[m_allocInfo.Combin.combinId[m_allocInfo.depth]] 
                             + m_knapsack.Costs1[0]*(m_allocInfo.caseNum - m_allocInfo.depth-1);
    minPermitCost2 = m_allocInfo.Combin.cost2 + m_knapsack.Costs2[m_allocInfo.Combin.combinId[m_allocInfo.depth]]
                             + m_knapsack.Costs2[0]*(m_allocInfo.caseNum - m_allocInfo.depth-1); 
    
    if((minPermitCost1 <= m_knapsack.limitCost1) && ((minPermitCost2 -m_knapsack.limitCost2) <= EPS)) 
    {
        m_allocInfo.Combin.value += m_knapsack.Values[m_allocInfo.Combin.combinId[m_allocInfo.depth]];            
        m_allocInfo.Combin.cost1 += m_knapsack.Costs1[m_allocInfo.Combin.combinId[m_allocInfo.depth]];
        m_allocInfo.Combin.cost2 += m_knapsack.Costs2[m_allocInfo.Combin.combinId[m_allocInfo.depth]];
        m_allocInfo.Combin.combinId[m_allocInfo.depth+1] = m_allocInfo.Combin.combinId[m_allocInfo.depth];
        m_allocInfo.depth ++;
    }
    else
    {
        m_allocInfo.Combin.combinId[m_allocInfo.depth] --;
    }
}


/*************************************************************
Module Function: check the value of this allocatation, update the Queue
    *  if this branch being successfully allocated, update the Queue if need, 
        and keep track of the current status
*************************************************************/
void CKnapsack::TopListUpdate()
{
    m_allocInfo.Combin.combinId[m_allocInfo.caseNum] = -1; // -1 is update flag    
    m_allocInfo.updateNum++;
    
    //update Top List
    m_priorityQueue.HeapUpdateTop(&m_allocInfo.Combin);    
    m_allocInfo.currentMinValue = m_topList->List[0].value; 
}


/*************************************************************
    Module Function: The main control process for next turn of allocation
    1. Track back: track back from last depth
        If last allocation update the Queue success, track back 1 step
    2. Then, we use"drop" to avoid the non valid value
        - For "drop", if not "drop", it means this allocation can't update last value,
           so, keep track back until drop != 0
**************************************************************/
void CKnapsack::NextAllocationControlProcess()
{    
    if (-1 == m_allocInfo.Combin.combinId[m_allocInfo.caseNum])
    {
        AllocRollbackOneStep();    
    }
    else    /* update m_allocInfo by BranchRoot */
    {
        AllocRollbackToBranchRoot();      
    }
        
    while(m_allocInfo.depth>=0)
    {                
        /* if the "drop" is true, go to next allocation, else roll back.
            (here, the value at caseNum saved the value of last allocate depth) */
        if(m_allocInfo.Combin.combinId[m_allocInfo.depth]> m_allocInfo.Combin.combinId[m_allocInfo.caseNum])
        {
            break;
        }
        
        AllocRollbackOneStep(); 
    } 
 
    //keep the records of current branch root
    m_allocInfo.BranchRoot.depth = m_allocInfo.depth;
    m_allocInfo.BranchRoot.value = m_allocInfo.Combin.value;
    m_allocInfo.BranchRoot.cost1 = m_allocInfo.Combin.cost1;
    m_allocInfo.BranchRoot.cost2 = m_allocInfo.Combin.cost2;

}

void CKnapsack::AllocRollbackOneStep()
{
    m_allocInfo.depth --;

    if (m_allocInfo.depth >=0)
    {
        m_allocInfo.Combin.value -= m_knapsack.Values[m_allocInfo.Combin.combinId[m_allocInfo.depth]];
        m_allocInfo.Combin.cost1 -= m_knapsack.Costs1[m_allocInfo.Combin.combinId[m_allocInfo.depth]];
        m_allocInfo.Combin.cost2 -= m_knapsack.Costs2[m_allocInfo.Combin.combinId[m_allocInfo.depth]]; 
                   
        m_allocInfo.Combin.combinId[m_allocInfo.depth] --; 
    } 
}

void CKnapsack::AllocRollbackToBranchRoot()
{
    m_allocInfo.depth            = m_allocInfo.BranchRoot.depth;
    m_allocInfo.Combin.value = m_allocInfo.BranchRoot.value;
    m_allocInfo.Combin.cost1 = m_allocInfo.BranchRoot.cost1;
    m_allocInfo.Combin.cost2 = m_allocInfo.BranchRoot.cost2;
          
    m_allocInfo.Combin.combinId[m_allocInfo.depth] --;        
}


void CKnapsack::SearchingLogTrace()
{
    int printNum;
    
    if ( -1 == m_allocInfo.Combin.combinId[m_allocInfo.caseNum])
    {
        printNum = m_allocInfo.caseNum;
        fprintf(m_traceFp, "\n ==>");     
    }
    else
    {
        printNum = m_allocInfo.depth+1;
        fprintf(m_traceFp, "\n    "); 
    }    
    fprintf(m_traceFp, " [value:%d; cost1:%d; cost2:%.1f] ", m_allocInfo.Combin.value, m_allocInfo.Combin.cost1, m_allocInfo.Combin.cost2);  
    PrintArrayToTraceFile(m_allocInfo.Combin.combinId, printNum);
}

void CKnapsack::PrintArrayToTraceFile(int array[], int printLen)
{
    int i;
    for ( i=0; i<printLen; i++) 
    {
        fprintf(m_traceFp, "%d ", array[i]);
    }    
    //fprintf(m_traceFp, "\n");
}



CPriorityQueue::CPriorityQueue(){}
CPriorityQueue::CPriorityQueue(TopList_T* topList)
{
	m_topList = topList;
}

CPriorityQueue::~CPriorityQueue(){}

void CPriorityQueue::HeapUpdateTop( CombinStat_T* Obj)
{
    memcpy(&m_topList->List[0], Obj, sizeof(CombinStat_T));
    MinHeapify(0);
}

/***********************************************************
Realize smallest priority queue with the element type is CombinStat_T
************************************************************/
void CPriorityQueue::MinHeapify( int current)
{
    int LeftChild;
    int RightChild;
    int smallest = current;

    LeftChild = LEFT(current);
    RightChild = RIGHT(current);

    if ((LeftChild < m_topList->size) && (m_topList->List[current].value > m_topList->List[LeftChild].value))
    {
        smallest = LeftChild;
    }

    if ((RightChild < m_topList->size) && (m_topList->List[smallest].value > m_topList->List[RightChild].value))
    {
        smallest = RightChild;
    }

    if(current != smallest)
    {
        SwapCombinStats(&m_topList->List[current], &m_topList->List[smallest]);

        MinHeapify(smallest);
    }
}


void CPriorityQueue::HeapPop()
{
    memcpy(&m_topList->List[0], &m_topList->List[m_topList->size-1], sizeof(CombinStat_T));
    m_topList->size --;
    MinHeapify(0);
}

void CPriorityQueue::HeapPush(CombinStat_T* Obj)
{
    int current;
    int parent;
    memcpy(&m_topList->List[m_topList->size], Obj, sizeof(CombinStat_T));
    m_topList->size ++;

    current = m_topList->size -1;
    while(current >= 1)
    {
        parent = PARENT(current);
        if (m_topList->List[current].value < m_topList->List[parent].value)
        {
            SwapCombinStats(&m_topList->List[current], &m_topList->List[parent]);
            current = parent;
        }
        else
        {
            break;
        }
    }
}

/***********************************************************
Swap combinId Status
************************************************************/
void CPriorityQueue::SwapCombinStats(CombinStat_T* obj1, CombinStat_T* obj2)
{
    CombinStat_T Temp;
    memcpy(&Temp, obj1, sizeof(CombinStat_T));
    memcpy(obj1, obj2, sizeof(CombinStat_T));
    memcpy(obj2, &Temp, sizeof(CombinStat_T));
}




