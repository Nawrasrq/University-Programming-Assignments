//Nawras Rawas Qalaji, NID:413580
//COP3503C_CMB-21 00381, Fall 2021
//Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)
import java.util.ArrayList; 
import java.lang.Math;

public class SneakyQueens
{	
	public static ArrayList<Integer> convertCoordinates(String coordinates)
	{	
		ArrayList<Integer> coor = new ArrayList<Integer>();
		coor.add(0);
		coor.add(0);
		
		// j tracks the reverse position for the row, ex: in abc52, a = 2, lastChar = 1, c = 0 
		int j = 0; 
		
		// lastChar tracks whether we are on the last char for rows, ex: lastChar = 1 when on c of abc52 and 0 otherwise
		int lastChar = 1; 
		int col = 0;
		
		// loops through the coordinates in reverse
		for (int i = coordinates.length() - 1; i >= 0; i--)
		{	
			// if its a digit find a substring where the first index is the first number in the coordinates
			if (Character.isDigit(coordinates.charAt(i)))
			{
				coor.set(1,Integer.parseInt(coordinates.substring(i)));
			}
			else
			{	
				// converts the character's ascii value into base 26
				int convert = (int)coordinates.charAt(i) - 96; 
				
				// uses the formula 26^j*convert+convert to change to base 26, lastChar is used to not add the last digit more than once
				col += (int)((Math.pow(26,j) - lastChar) * convert) + convert * lastChar; 
				coor.set(0,col);
				
				j += 1;
				lastChar = 0;
			}
		}
		return coor;
	}

	public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		//amount of coordinate pairs
		int size = coordinateStrings.size();
		
		// arraylists to track which cols, rows, and diagonals are filled
		boolean[] cols = new boolean[boardSize];
		boolean[] rows = new boolean[boardSize];
		boolean[] leftdiagonals = new boolean[2*boardSize];
		boolean[] rightdiagonals = new boolean[2*boardSize];
		
		//loop through all the coordinate pairs
		for (int i = 0; i < size; i++)
		{	
			ArrayList<Integer> coord = convertCoordinates(coordinateStrings.get(i));
			
			// check if col is taken, if not then mark it as such
			if (cols[coord.get(0) - 1] != true)
			{
				cols[coord.get(0) - 1] = true;
			}
			else 
			{
				return false;
			}
			
			// check if row is taken, if not then mark it as such
			if (rows[coord.get(1) - 1] != true)
			{
				rows[coord.get(1) - 1] = true;
			}
			else 
			{
				return false;
			}
			
			// a coordinates left diagonal can be found by col+ row
			int leftdiagonal = coord.get(0) + coord.get(1);
			
			// a coordinates right diagonal can be found by col - row + total cols/rows - 1
			int rightdiagonal = coord.get(0) - coord.get(1) + (boardSize - 1);
			
			// check if leftdiagonal is taken, if not then mark it as such
			if (leftdiagonals[leftdiagonal] != true)
			{
				leftdiagonals[leftdiagonal] = true;
			}
			else 
			{
				return false;
			}
			
			// check if rightdiagonal is taken, if not then mark it as such
			if(rightdiagonals[rightdiagonal] != true)
			{
				rightdiagonals[rightdiagonal] = true;
			}
			else 
			{
				return false;
			}			
		}
		return true;
	}

	public static double difficultyRating()
	{
		return 3.0;
	}

	public static double hoursSpent()
	{
		return 14.0;
	}

}

