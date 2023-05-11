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
		int total = 0;
		int size = blocks.length - 1;
		HashMap<Integer, Integer> memo = new HashMap<Integer, Integer>();
		total = maxGainRecursion(blocks, total, size, memo);
		//System.out.println(total);
		return total;
		
	}
	
	public static int maxGainRecursion(int [] blocks, int total, int size, HashMap<Integer, Integer> memo)
	{	
		//System.out.println(memo);
		// either reached last block or outside of array so return 0 instead
		if (size < 0)
		{
			return 0;
		}
		else if (size == 0)
		{
			total += blocks[size];
			return total;
		}

		Integer blockMemo = memo.get(size);
		
		if (blockMemo != null){
			return blockMemo;
		}
		
		int block1 = blocks[size - 1] + maxGainRecursion(blocks, total, size - 3, memo);
		int block2 = blocks[size] + maxGainRecursion(blocks, total, size - 2, memo);
		
		if(block1 > block2){
			total += block1;
			memo.put(size, total);
			return total;
		}
		else{
			total += block2;
			memo.put(size, total);
			return total;
		}
		
	}
	
	public static double difficultyRating()
	{
		return 3.0;
	}

	public static double hoursSpent()
	{
		return 12.0;
	}

}


