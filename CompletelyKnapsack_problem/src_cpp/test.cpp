/************************************************************************************
       Function:       Main of the LRC Resource Model Test set Generator
       Author:         Fan, Shuangxi (Nokia - CN/Hangzhou)
       Date:           2015-3-20
 ************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include "Knapsack.hpp"


/***************************************************
 Global Defination
***************************************************/

#define CLOCK_PER_SEC (1000)

#define TOP_LIST_SIZE    60     // set your TOP_LIST_SIZE

const char* topListFileName("top_list.txt");

FILE *            topList_fp = NULL;


/***************************************************/

const int  Values[] = {24, 24,  26,  26,  96, 96,  130,  130,  150,  173,  173,  193,  233,  233, 253, 293, 293, 323, 353, 383}; 
const int  Costs1[] = {24, 24,  26,  26,  96, 96,  130,  130,  150,  173,  173,  193,  233,  233, 253, 293, 293, 323, 353, 383}; 
const float Costs2[] = {2.4, 2.4, 5,   5,   10,  10,  19.2, 19.2, 19.2, 19.2,  32,   32,   32,    64,   64,   64,   96,  96,   96,  96 };
const int    limitCost1 = 1920;
const float limitCost2 = 192.0;  

int  caseNum;


/* ******************************************************************
    Function prototypes
    
******************************************************************** */
void KnapsackInit(Knapsack_T*);
void TopListInit(TopList_T* );
void DataInit(Knapsack_T*, TopList_T* );
void PrintCombinStat(const CombinStat_T* CombinStat);
void TopListPrint(TopList_T*);
void TestMainFlow();

/***********************************************************
Swap ResourceBaseStats
************************************************************/

void KnapsackInit(Knapsack_T* knapsack)
{
    knapsack->caseNum = caseNum;
    knapsack->caseKinds = sizeof(Values)/sizeof(int);
    knapsack->limitCost1 = limitCost1;
    knapsack->limitCost2 = limitCost2;
    
    int i;
    for (i=0; i<knapsack->caseKinds; i++)
    {
        knapsack->Values.push_back(Values[i]);
        knapsack->Costs1.push_back(Costs1[i]);
        knapsack->Costs2.push_back(Costs2[i]);
    }
}

void TopListInit(TopList_T*  topList)
{
    CombinStat_T combinStat;
    combinStat.value = 0;
    combinStat.cost1 = 0;
    combinStat.cost2 = 0;
    combinStat.combinId.assign(caseNum+1, 0);
    
    topList->size = TOP_LIST_SIZE;
    topList->List.assign(TOP_LIST_SIZE, combinStat);

}

/***************************************************************************
* GlobalDataStatInit: preprocess of the Resource data before put them into the Searching process
*  - Init Resource Base and MipsInfo
****************************************************************************/
void DataInit(Knapsack_T* knapsack, TopList_T*  topList)
{  
    KnapsackInit(knapsack);
    TopListInit(topList);    
}

void PrintCombinStat(const CombinStat_T* CombinStat)
{
    int i;

    fprintf(topList_fp, "[Value: %d, Cost1: %d; Cost2: %.1f; ] Combination sat Id  => ", 
        CombinStat->value, CombinStat->cost1, CombinStat->cost2);

    for( i=0; i< caseNum; i++)
    {
        fprintf(topList_fp, "%d; ",
        CombinStat->combinId[i]);
    }
    
    fprintf(topList_fp, "\n"); 
}


void TopListPrint(TopList_T* topList)
{
    
    CPriorityQueue priorityQueue(topList);
    while (topList->size > 0 && topList->List[0].value <= 0)
    {
        priorityQueue.HeapPop();
    }
    
    printf("    Get The Top %d List. \n\n", topList->size);
    fprintf(topList_fp, "\n[Top %d List ] [Total Resource -> limitCost1: %d, limitCost2: %.1f]\n", 
        topList->size,  limitCost1, limitCost2);     
    
    while (topList->size > 0 && topList->List[0].value >0)
    {
        PrintCombinStat(&topList->List[0]);        
        priorityQueue.HeapPop();
    } 
}

void UsageDisplay(char* exeFilePath)
{
    
    printf("\n----------------- Usage: ------------------\n"); 
    printf(" * Input:\n");
    printf("    [1] caseNum:\n");       
    printf(" * @Example: %s 20\n", exeFilePath);
    printf(" * Output: \n");
    printf("       A file named top_list.txt, the top list of the result combinations.\n");
    printf("-------------------------------------------\n");
}

void TestMainFlow()
{
    Knapsack_T   knapsackData;
    TopList_T      topList; 
    
    topList_fp = fopen(topListFileName, "w"); 
    assert( topList_fp != NULL);    

    DataInit(&knapsackData, &topList); 
    
    CKnapsack knapsack(&knapsackData, &topList);
    
    knapsack.KnapsackCombinationSearch();

    TopListPrint(&topList);
    
    fclose(topList_fp);
}

/* ******************************************************************
    Main Function of Test Set Generator
    
******************************************************************** */
int main(int argc, char* argv[])
{ 

    if(2 != argc)
    {
        UsageDisplay(argv[0]);
    }
    else
    {  
        caseNum =  atoi(argv[1]);      
        int start;
         
        start = clock();
        
        TestMainFlow();   
        
        printf(" * Take Time: %f seconds.\n", (double)(clock()-start)/CLOCK_PER_SEC);             
    }
    
    return 0;
}




