/* ====================================================================
 Function: Find out all the numbers which no smaller than all the left numbers
			and no bigger than all the right numbers.
  =====================================================================  */

import java.io.*;  

/**************************************************************

****************************************************************/  
class FindDivideNumber
{
	public int index = 0;
	private int[] m_array;
	
	public FindDivideNumber(){}
	
	public FindDivideNumber(int [] inArray)
	{	
		this.m_array = new int[inArray.length];
		this.m_array = inArray.clone();
	}
	
	// Implementation by iteration
	public void FindTheFirstDivideNumber()
	{
		int currMax = m_array[0];
		index = 0;
		int flag = 0;
		for(int i=1; i< m_array.length; i++)
		{
			if(m_array[i]<currMax)
			{
				flag = 1;
			}
			else if (flag == 1)
			{
				currMax = m_array[i];
				index = i;
				flag = 0;				
			}
		}
		
		if (flag == 1) // search failure
		{
			index = m_array.length;
		}		
	}
}

public class FindDivideNumberTest
{
	//Java entry function 
	public static void main(String[] args)
	{
		int a[] = {0};
		
		System.out.println(" Input array 'a[]' divide with ',':\n ");
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String inputStr = null;

		try
		{
			inputStr = br.readLine();
			String[] posStrArr = inputStr.split(",");
			a = new int[posStrArr.length];
			for(int i = 0; i<posStrArr.length;i++)
			{
				a[i] = Integer.parseInt(posStrArr[i]);
			}
		}
		catch(IOException e)
		{
			System.out.println(" Input Exception:"+e);
		}		

		FindDivideNumber fdn = new FindDivideNumber(a);
		fdn.FindTheFirstDivideNumber();
		
		if (fdn.index < a.length)
		{
			System.out.println("\n the divide number is: a["+ fdn.index + "] = " + a[fdn.index] + "\n");
		}
		else
		{
			System.out.println("\n** No divide number find!\n");
		}
	}
}