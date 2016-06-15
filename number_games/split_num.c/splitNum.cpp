/* ====================================================================
 function: split a number 'm' into 'n' part, and return the number of kinds
	request: m >= n
  =====================================================================  */
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

#define CLOCK_PER_SEC (1000)
//----------------------------------------------------------------------
/**************************************************************
- The allocated rule: the child number should not smaller than the parent.
- The create process start from first level, if this allocate success, 
  it point to current node level, else it back to its parent level
****************************************************************/
int split_num(int m, int n) 
{
	vector<int> a(n,0);			// indicate the allocated number in each level of the tree
	vector<int> c_value(n-1,0);	// indicate the accumulate value of each level				
	int num = 0;		//the number of kinds
	
	/**************************************************************
	p: to indicate the point to be spread,  
		when p back to -1 means the allocate process complete
	****************************************************************/	
	int p = 0;	/* to indicate the point to be spread, it means the  
				   allocate process complete when p back to -1. */
	int p_sum = 0; // the sum value at p
 
	while (p > -1)						
	{								
		a[p] += 1;			//create new branch
		c_value[p] += 1;
		for (int i=p; i<n-1; i++)
		{
			if (m - c_value[i] >= a[i])			//current allocate is success
			{
				if (i == n-2)		// this allocate is success
				{
					a[n-1] = m - c_value[i];		
					num += 1;
					p = i;			// make p point the level i						
					PrintArray(a);
				}
				else				//this allocate not complete
				{					//update the node value and c_value of next level
					a[i+1]=a[i];	
					c_value[i+1] = c_value[i]+a[i]; 
				}
			}
			else					//this allocate not success, make p point its parent
				p -= 1;			
		}		
	}
	return num;	
}//----------------------------------------------------------------------------------

void PrintArray(vector<int> array)
{
	for (int i=0; i<array.length(); i++) 
		cout<<array[i]<<" ";
	cout<<endl;	
}


int main()
{
	int m,n,num,start;
	cout<<"m= ";	cin>>m;
	cout<<"n= ";	cin>>n;

	start = clock();
	num = split_num(m,n);
	cout<<endl<<"total number: "<<num<<endl;
	
	cout<<"duration: "<<(double)(clock()-start)/CLOCK_PER_SEC<<" seconds"<<endl;

	return 0;
}
