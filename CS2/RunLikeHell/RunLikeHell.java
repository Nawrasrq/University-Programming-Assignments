// Nawras Rawas Qalaji, NID:413580
// COP3503C 00381, Fall 2021
// Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)
import java.util.*;
import java.awt.*;
import java.io.*;

public class RunLikeHell
{
	public static int maxGain(int [] blocks)
	{	
		// check special cases
		if (blocks == null || blocks.length == 0)
		{
			return 0;
		}
		else if (blocks.length == 1)
		{
			return blocks[0];
		}
		else if (blocks.length == 2)
		{
			if (blocks[0] > blocks[1])
			{
				return blocks[0];
			}
			else
			{
				return blocks[1];
			}
		}
		
		// create array with minimum space required
		int size = blocks.length;
		int [] DynamicProgramming = new int[size + 1];
		
		// fill base cases
		DynamicProgramming[0] = blocks[0];
		DynamicProgramming[1] = blocks[1];

		// case for starting at first index
		DynamicProgramming[2] = blocks[0] + blocks[2];
		
		// fill rest of array dynamically
		for (int i = 3; i < size; i++)
		{
			if (DynamicProgramming[i - 2] > DynamicProgramming[i - 3])
			{
				DynamicProgramming[i] += DynamicProgramming[i - 2] + blocks[i];
			}
			else
			{
				DynamicProgramming[i] += DynamicProgramming[i - 3] + blocks[i];
			}
			
		}
		
		// return total depending on if we started at the 1st or 2nd index
		if (DynamicProgramming[size - 1] > DynamicProgramming[size - 2])
		{
			return DynamicProgramming[size - 1];
		}
		else
		{
			return DynamicProgramming[size - 2];
		}

	}
	
	public static double difficultyRating()
	{
		return 2.0;
	}

	public static double hoursSpent()
	{
		return 8.0;
	}

}

