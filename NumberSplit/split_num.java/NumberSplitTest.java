/* ====================================================================
 function: split a number 'm' into 'n' part, and return the number of kinds
	request: m >= n
  =====================================================================  */

import java.io.*;  

/**************************************************************
- The allocated rule: the child number should not smaller than the parent.
- The create process start from first level, if this allocate success, 
  it point to current node level, else it back to its parent level
****************************************************************/  
class NumberSplit
{
	public int totalNum = 0;
	private int[] allocateList;
	private int N;
	
	public NumberSplit(){}
	
	public NumberSplit(int n)
	{	
		this.N = n;
		this.allocateList = new int[n+1];
		this.allocateList[0] = 1;
	}
	
	// Implementation by iteration
	public void splitNumberIteration(int m, int n)
	{
		if (n==1)
		{			
			if (m >= allocateList[N-1])
			{
				allocateList[N] = m;
				totalNum += 1;	
				this.printArray(allocateList, 1, allocateList.length);
			}
			else
				return;
		}
		else if (m >= n)
		{			
			for (int i= allocateList[N-n]; i*n<= m; i++)
			{	
				allocateList[N-n+1] = i;
				splitNumberIteration(m-i, n-1);
			}
		}
	}
	
	
	// Implementation by non-iteration
	public int splitNumber(int m, int n)
	{
		int totalNum = 0;
		// array initialized by all 0 
		int[] allocateList = new int[n];
		int currSumValue = 0;				
		int depthPtr = 0;		
		while (depthPtr >= 0)
		{
			if (n==1)
			{
				System.out.print(m+" \n");
				return 1;
			}
			allocateList[depthPtr] += 1;
			currSumValue += 1;	
			if (allocateList[depthPtr]*(n-depthPtr-1) > (m-currSumValue))
			{
				currSumValue -= allocateList[depthPtr];
				depthPtr -= 1;				
				continue;
			}			
			
			for (int i = depthPtr; i<= n-3; i++)
			{
				allocateList[i+1] = allocateList[i];
				currSumValue += allocateList[i+1];												
			}
			allocateList[n-1] = m - currSumValue;
			depthPtr = n-2;
			totalNum += 1;
			
			this.printArray(allocateList, 0, allocateList.length);								
		}
		return totalNum;
	}
	

	//print array
	public void printArray(int[] Array, int start, int end)
	{
		for (int i= start; i< end; i++)
			System.out.print(Array[i]+" ");
		System.out.println("");		
	}
}

public class NumberSplitTest
{
	//Java entry function 
	public static void main(String[] args)
	{
		int m = 6, n = 3;
				
		System.out.println(" Input m, n:");
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String inputStr = null;

		try
		{
			inputStr = br.readLine();
			String[] posStrArr = inputStr.split(",");
			m = Integer.parseInt(posStrArr[0]);
			n = Integer.parseInt(posStrArr[1]);
		}
		catch(IOException e)
		{
			System.out.println(" Input Exception:"+e);
		}
		
		
		if (n>0 && m > n)
		{
			int num;
	
			NumberSplit ns1 = new NumberSplit(n);
			System.out.println("\n * Split by iteration:\n");			
			ns1.splitNumberIteration( m, n);			
			System.out.println("total number: " + ns1.totalNum);
			
			NumberSplit ns2 = new NumberSplit();
			System.out.println("\n * Split by non-iteration:\n");				
			num = ns2.splitNumber( m, n);			
			System.out.println("total number: " + num + "\n");				
		}
			
	}
}