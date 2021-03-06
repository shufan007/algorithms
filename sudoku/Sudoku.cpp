// Sudoku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <string>

using namespace std;

//====================================

//*********** Data Base Init **************
const int N = 9;  //line & column number
int Matrix[9][9]; //sudoku matrix
//int SudokuProbMatrix[9][9] = {0}; //sudoku puzzle matrix
int ValidList[81][9];    //
int ValidNum[9][9];
int RandList[81];
int x, y;   //9*9 matrix index
int Block_x, Block_y; //  3*3 Block index
int DeleteNum;
bool RecallFlag;

int FillNum ;
int fill_index;	
list<int> FillIndexList;	//record the index of the value should be fill

//bool SolveRecallFlag;
int ClueNum ;	//clue number of sudoku puzzle matrix
list<int> MissingList;
bool StayFlag;
bool SolveFlag;	//1 -- solved, 0 -- invalid sudoku puzzle

clock_t start, finish;  
double  duration;


//************ subfunctions ***************
// init the data base
void DbInit();

//-get a random list by the given list num
void GetRandomList (int BeginNum, int EndNum, int RandArrayLength);

/*-for each matrix element, get the valid list
    and random the list member by GetRandomList()  */
void GetValidList(int index_x, int index_y );

//-get the current valid value, set the relate status
void GetValidValue();

// get the next Coord
void GetNextCoord();

// get the recall Coord
void GetRecallCoord();

//get the valid 9*9 matrix

/* In GetValidMatix1() we serch the coord in order,
 the index of x and y increased gradually    */
void GetValidMatix1();

/*  In GetValidMatix2() we unify the algorithm of GetValidMatix() and  SudokuPuzzleSolve() 
search the coord use SearchFunc		*/
void GetValidMatix2();

//get the delete member coords according to the delete number
void GetDeleteMatix(int);

//print sudoku matrix
void SudokuMatrixPrint();

//get the sudoku puzzle matrix from a file
void GetSudokuPuzzleMatrix();

//Get the Smallest Non-zero Valid Number and its index
void GetNextValidCoord();

//when filled one value, reset the valid list that could be affect
void ResetValidList();

//search every empty coord and fill value
void SearchFunc(int SearchNum);

// get the solution of a sudoku puzzle 
void SudokuPuzzleSolve();
//================================
void DbInit()
{
	int i,j;
	for (i=0; i<N; i++ )
	{
		for(j=0;j<N;j++)
		{
			Matrix[i][j] = 0;
			ValidNum[i][j] = 0;
			RandList[i*N+j] = 0;
		}
	}

	for (i=0; i<N*N; i++ )
	{
		for(j=0;j<N;j++)
		{
			ValidList[i][j] = 0;
		}
	}
	//int SudokuProbMatrix[9][9] = {0}; //sudoku puzzle matrix
	int ValidList[81][9] = {0};    //

	FillNum = 0;
	ClueNum = 0;	//clue number of sudoku puzzle matrix
	SolveFlag = 1;	//1 -- solved, 0 -- invalid sudoku puzzle
}

void GetRandomList (int BeginNum, int EndNum, int RandArrayLength)
{	
	int space = EndNum -BeginNum +1;
	const int space0 = space; 	//save original space
	const int max = 81;

	int i, j ;
	for ( i = 0; i<RandArrayLength; i ++)
	{
		RandList[i] = max;
	}    

	int Numbers[max] ;
	for (i = 0; i<space; i ++)
	{
		Numbers[i] = i;
	}    

	int Index;
	int count;
	srand(time(0));
	
	for (i = 0; i<RandArrayLength; i ++)
	{    
		Index = rand()%space;	
		space --;
		
		count = 0;
		for (j =0; j<space0; j ++)
		{
			if (Numbers[j] != max)
			{
				count++;
			}
			
			if (count == Index+1 )
			{       
				RandList[i] = Numbers[j];				
				Numbers[j] = max;
				break;				
			}
		}		
	}
}


void GetValidList(int index_x, int index_y )
{
	ValidNum[index_x][index_y] = 0;
	int List[9] = {1,2,3,4,5,6,7,8,9};
	int CurrentList[9];
	int i, j ;
	for (i = 0; i<N; i ++)      //search line and column
	{
		if (Matrix[index_x][i] != 0)
		{
			List[Matrix[index_x][i]-1] = 0;
		}

		if (Matrix[i][index_y] != 0)
		{
			List[Matrix[i][index_y]-1] = 0;
		}        
	}

	//serch small 3*3 cell 
	Block_x = (index_x/3)*3;
	Block_y = (index_y/3)*3;
	for (i = Block_x; i<Block_x+3; i ++)
	{
		for (j = Block_y; j<Block_y+3; j ++)
		{
			if (Matrix[i][j] != 0)
			{
				List[Matrix[i][j]-1] = 0;
			}           
		}
	}
	
//collect non 0 value (valid value)
	for (i =0; i<N; i++)
	{
		if (List[i] !=0)
		{
			CurrentList[ValidNum[index_x][index_y]] = List[i];
			ValidNum[index_x][index_y] ++ ;

		}        
	}
	if (ValidNum[index_x][index_y]>0)
	{
		if (ValidNum[index_x][index_y]>1)
		{
			GetRandomList(0, ValidNum[index_x][index_y]-1, ValidNum[index_x][index_y]); 

			for (i = 0; i<ValidNum[index_x][index_y]; i ++)    //random the list member
			{
				ValidList[index_x*N+index_y][RandList[i]] = CurrentList[i]; 
			}
		}
		else    //only one valid value, not need to random
		{
			ValidList[index_x*N+index_y][0] = CurrentList[0];
		}   
	}    
}

//get value from the end of the valid list, then reset the valid number
void GetValidValue()
{
	Matrix[x][y] = ValidList[x*N+y][ValidNum[x][y]-1];
	ValidNum[x][y] --;
}


void GetNextCoord()
{
	if ( y<N-1)
	{
		y += 1;
	}
	else if(x<N-1)
	{
		x += 1;
		y = 0;        
	}
}


/* when this coord is not at the beginning of the line, recall to the previous coord
    else when this coord is just at the beginning of the line and the cell, recall to the beginning previous line
    else go to the third coord of the previous line
    after that, we should clear the value of the current coord as well as behind it
*/
void GetRecallCoord()
{
	int i ;
	if (y != 0) 
	{
		y -= 1;
		Matrix[x][y] = 0;
	}
	else 	//y==0, at the beginning of the line
	{ 
		if (x%3 == 0)
		{
			x -= 1;
			for (i = 0; i<N; i ++)
			{
				Matrix[x][i] = 0;
			}			
		}
		else
		{
			x -= 1;
			y += 2;
			
			for (i = y; i<N; i ++)
			{
				Matrix[x][i] = 0;
			}
		}
	}
}

/*  *************************************************
 Here, in GetValidMatix1() we search the coord in order,
 the index of x and y increased gradually
  ************************************************    */
void GetValidMatix1()
{
	//coord init
	 x = 0; 
	 y = 0;
	int i, j;
	for(i=0; i<N; i ++)
	{
		for(j =0; j<N; j ++)
		{
			Matrix[i][j] = 0; //sudoku matrix
			ValidNum[i][j] = 0;
		}
	}
	 
    RecallFlag = 0;
	 
	while (true)
	{
		if (RecallFlag == 0)
		{
			GetValidList(x,y);
		}

		if (ValidNum[x][y]>0)
		{
			GetValidValue();
			if (x == N-1 && y == N-1)   //reach the end of the matrix
			{
				break;
			}
			else
			{
				RecallFlag = 0;
				GetNextCoord();     //keep going to the next one
			}		    
		}
		else
		{
			RecallFlag = 1;
			GetRecallCoord();
		}	   
	}  
}


/*  ************************************************
Here, in GetValidMatix2() we unify the algorithm of GetValidMatix() and  SudokuPuzzleSolve() 
search the coord use SearchFunc
  ************************************************    */
  
void GetValidMatix2()
{
	int i, j ;
	
	for(i=0; i<N; i ++)
	{
		for(j =0; j<N; j ++)
		{
			Matrix[i][j] = 0; 
			ValidNum[i][j] = 0;
		}
	}	
	
	// random the list of all the 81 indexes, we get the value according to the given list
	GetRandomList (0, 80, 81);
	
	if ( ~ MissingList.empty())
	{
		MissingList.clear();
	}

	if ( ~ FillIndexList.empty())
	{
		FillIndexList.clear();
	}		

	for ( i = 0; i<81; i ++)
	{
		MissingList.push_back(RandList[i]);	
	}

	for (i = 0; i<N; i ++)
	{
		for (j = 0; j<N; j ++)
		{				
			GetValidList(i, j );
		}
	}

	SearchFunc(81);

}

void GetDeleteMatix(int DeleteNum)
{

	GetRandomList(0,80,DeleteNum); 
	
	//reset the Matrix
	for (int i = 0; i<DeleteNum; i ++)
	{
		Matrix[RandList[i]/N][RandList[i]%N] = 0;
	}
}

void SudokuMatrixPrint()
{
	printf("\n ");
	
	int i, j ,k;	
	for (i = 0; i<N; i ++)
	{
		if (i%3 == 0)
		{
			printf(" |");
			for (k=0; k<2*N+5; k++)
			{
				if (i>0 && (k+1)%8 == 0 && k != 23)
				{
					printf("+");
				}
				else
				{
					printf("-");
				}				
			}
			printf("|\n ");		
		}

		for (j =0; j<N; j ++)
		{
			if (j%3 ==0)
			{
				printf(" |");
			}
			if (Matrix[i][j]>0)
			{
				printf(" %d",Matrix[i][j]);
			}
			else
			{
				printf("  ");
			}				
		}
		printf(" |\n ");	
	}

	printf(" |");
	for (k=0; k<2*N+5; k++)
	{
		printf("-");
	}
	printf("|\n ");	
}


//get the sudoku puzzle matrix from a file
void GetSudokuPuzzleMatrix()
{
	ifstream InFile;		//get the file of the Sudoku puzzle
	InFile.open("SudokuPuzzle.txt");

    if (InFile)
    {
        string s;  
	int i, j ;		
	for (i = 0; getline(InFile, s);  i ++)
	{
		istringstream sin(s);
		for (int ia, j = 0; sin>>ia; j ++)
		{
			Matrix[i][j] = ia;

			if (ia !=0)
			{
				ClueNum ++ ;
			}			
		}
	}
	
	InFile.close();
    }
    else
    {
    	cout<<"Sudoku puzzle File open error!\n"; 
    }
	
}

//Get the Smallest Non-zero Valid Number and its index
void GetNextValidCoord()
{
	list<int>::iterator iter, iterCurrent;
	int temp_i = MissingList.back()/ N;
	int temp_j  = MissingList.back()% N;
	int SmallestNum = N;
	int i, j ;
	for ( iter = MissingList.begin(); iter != MissingList.end(); iter ++)
	{
		i = (*iter) / N;
		j = (*iter) % N;		
		if (ValidNum[i][j] < SmallestNum)
		{
			SmallestNum = ValidNum[i][j];
			temp_i = i;
			temp_j = j;			
			iterCurrent = iter;
		}
	}

	StayFlag = 1;
	if (SmallestNum >0)	//if SmallestNum >0, should put forward and set the new x,y ,else keep the old x,y
	{
		StayFlag = 0;		
		x = temp_i;
		y = temp_j;
	}		//else  SmallestNum ==0,   StayFlag = 1	
}

//when filled one value, reset the valid list that could be affect
// should judged by RecallFlag, if RecallFlag==0 (should forward), remove the value from the related valid list
//	if RecallFlag==1 (should backward), return the value to the related valid list
void ResetValidList()
{
	int i, j, k ;
	if (RecallFlag  == 1)
	{
		list<int>::iterator iter;
	
		for ( iter = MissingList.begin(); iter != MissingList.end(); iter ++)
		{
			i = (*iter) / N;
			j = (*iter) % N;

			GetValidList(i, j );			
		}			
	}
	else		//RecallFlag  == 0
	{	
		int FindFlag;
		if (StayFlag == 0)		//should forward
		{
			for (j = 0; j<N ; j ++)      //search line and column
			{				
				if (Matrix[x][j] == 0  &&  j != y)
				{
					FindFlag =0;
					for (k =0; k<ValidNum[x][j]; k++)
					{
						if (FindFlag ==0 && ValidList[x*N+j][k] == Matrix[x][y])
						{
							FindFlag =1;
							ValidNum[x][j] --;
						}
						
						if (FindFlag == 1 && k<ValidNum[x][j])
						{
							ValidList[x*N+j][k]=ValidList[x*N+j][k+1];
						}	
					}										
				}		     
			}
			
			for (i = 0; i<N ;  i ++)      //search line and column
			{				
				if (Matrix[i][y] == 0 && i != x)
				{
					FindFlag =0;
					for (k =0; k<ValidNum[i][y]; k++)
					{
						if (FindFlag ==0 && ValidList[i*N+y][k] == Matrix[x][y])
						{
							FindFlag =1;
							ValidNum[i][y] --;
						}
						
						if (FindFlag == 1 && k<ValidNum[i][y])
						{
							ValidList[i*N+y][k]=ValidList[i*N+y][k+1];
						}	
					}										
				}			    
			}

			//search small 3*3 cell 
			
			Block_x = (x/3)*3;
			Block_y = (y/3)*3;
			for (i = Block_x;   i<Block_x+3;  i ++)
			{
				for (j = Block_y;  j<Block_y+3; j ++)
				{					
					if (Matrix[i][j] == 0 &&  i != x &&  j !=y)
					{
						FindFlag =0;
						for (k =0; k<ValidNum[i][j]; k++)
						{					
							if (FindFlag ==0 && ValidList[i*N+j][k] == Matrix[x][y])
							{
								FindFlag =1;
								ValidNum[i][j] --;
							}
							
							if (FindFlag == 1 && k<ValidNum[i][j])
							{
								ValidList[i*N+j][k]=ValidList[i*N+j][k+1];
							}
						}												
					}        
				}
			}
		}
		else		//StayFlag == 1, should backward or stay here
		{
		//----------- clear  ----------------

		//-----------Get Valid List -----------------------
			for (j = 0; j<N; j ++)      //search line and column
			{
				if (Matrix[x][j] == 0  &&  j != y)
				{
					GetValidList(x, j );
				}		     
			}

			for (i = 0; i<N ; i ++)      //search line and column
			{
				if (Matrix[i][y] == 0 &&  i != x)
				{
					GetValidList(i, y);			
				}			    
			}

			//search small 3*3 Block 
			Block_x = (x/3)*3;
			Block_y = (y/3)*3;
			for (i = Block_x;  i<Block_x+3;  i ++)
			{
				for (j = Block_y;   j<Block_y+3; j ++)
				{
					if ( Matrix[i][j] == 0  && i != x && j !=y)
					{
						GetValidList(i, j );												
					}        
				}
			}			
		}
	}
}

void SearchFunc(int SearchNum)
{
	StayFlag =0;

	while (true)
	{		
		RecallFlag = 0;
		
		if (FillNum != SearchNum)
		{								
			GetNextValidCoord();	
			if (StayFlag == 1)
			{
				while (ValidNum[x][y] == 0)	//if ValidNum[x][y] == 0, the index still the last one, should recall back
				{
					if (FillNum>0)	
					{				
						RecallFlag =1;
						FillIndexList.pop_back();
						FillNum --;
						Matrix[x][y] = 0;		//clear 
						MissingList.push_back(fill_index);
						fill_index = FillIndexList.back();				
						x = fill_index / N;
						y = fill_index % N;	
					}
					else
					{
						SolveFlag = 0;
						SearchNum = 0;			//return
						break;						
					}					
				}
				GetValidValue();	//must get value  first
				ResetValidList();						
			}
			else//   if StayFlag == 0 ,go  forward, else  stay here
			{	
				FillNum ++;		
				fill_index =  x*9+y;
				FillIndexList.push_back(fill_index);
				MissingList.remove(fill_index);	
				
				GetValidValue();	//must get value  first	
				ResetValidList();	
			}
		}
		else
		{
			break;
		}	
	}
}


// get the solution of a sudoku puzzle 
void SudokuPuzzleSolve()
{
	if ( ~ MissingList.empty())
	{
		MissingList.clear();
	}
	
	if ( ~ FillIndexList.empty())
	{
		FillIndexList.clear();
	}	
	
	int i, j ;	
	for (i = 0; i<N; i ++)
	{
		for (j = 0; j<N; j ++)
		{
			if (Matrix[i][j] == 0)
			{
				MissingList.push_back(i*9+j);				
				GetValidList(i, j );
			}
		}
	}
	//SolveFlag = 1;
	SearchFunc(81-ClueNum);	
		
}

//==========================================



int main()
{

	printf( "\n Please choose what you want the function do: \n" );
	printf( "\n [1] generate a sudoku matrix \n" );
	printf( "\n [2] generate a sudoku puzzle \n" );
	printf( "\n [3] solve a sudoku puzzle \n" );
	printf( "\n Note: if you want to solve a sudoku puzzle,");
	printf( "\n	you should put the puzzle in 'SudokuPuzzle.txt'.\n" );
	printf( "\n Input the number for your choice: " );

	int choice;
	scanf("%d",&choice);

	while (choice)
	{
		switch (choice)
		{
			case 1 :	//---- creat a valid matrix -----
			{
				start = clock();  
				DbInit();
				GetValidMatix2();
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				printf("\n The valid Sudoku Matrix: \n");

				SudokuMatrixPrint();	
				printf( "\n It takes  %f  seconds CPU time \n", duration ); 
				break;
			}
			case 2 :	// get a sudoku puzzle matrix with some values missing 
			{
				start = clock(); 
				DbInit();
				GetValidMatix2();
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				printf("\n The valid Sudoku Matrix: \n");

				SudokuMatrixPrint();	
	
				printf("\nPlease input the delete number: ");
				scanf("%d",&DeleteNum);
				printf("\n The  Sudoku Matrix with %d members delete: \n", DeleteNum);
				GetDeleteMatix(DeleteNum);
				SudokuMatrixPrint();

				printf( "\n It takes  %f  seconds CPU time \n", duration ); 
				break;
			}	

			case 3:	 // figure out a sudoku puzzle
			{
				DbInit();
				GetSudokuPuzzleMatrix();	
				printf("\n The  Sudoku puzzle with %d clue numbers : \n", ClueNum);		
				SudokuMatrixPrint();
				start = clock(); 

				SudokuPuzzleSolve();
	
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
	
				if (SolveFlag == 1)
				{
					printf("\n\n The  Sudoku puzzle has solved:  \n");			
					SudokuMatrixPrint();	
				}
				else
				{
					printf("\n ******* This is not a valid sudoku puzzle!  ******* \n");	
				}

			   printf( "\n It takes  %f  seconds CPU time \n", duration ); 	
			   break;
			}
			default:
				printf( "\n Invalid input! " );
		}
		printf( "\n  input '1','2'or '3' for continue, '0' to exit:  " );
		scanf("%d",&choise);
	}

	return 0;
}

