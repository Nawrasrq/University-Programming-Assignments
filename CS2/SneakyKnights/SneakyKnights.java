// Nawras Rawas Qalaji, NID:413580
// COP3503C 00381, Fall 2021
// Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)
import java.util.ArrayList;
import java.util.HashSet; 
import java.lang.Math;
import java.awt.*;

public class SneakyKnights
{	
	public static ArrayList<Integer> convertCoordinates(String coordinates)
	{	
		ArrayList<Integer> coor = new ArrayList<Integer>();
		coor.add(0);
		coor.add(0);
		
		// j tracks the reverse position for the row
		int j = 0; 
		
		// lastChar tracks whether we are on the last char for rows
		int lastChar = 1; 
		int col = 0;
		
		// loops through the coordinates in reverse
		for (int i = coordinates.length() - 1; i >= 0; i--)
		{	
			// if its a digit find a substring where the first index is the first number in the coordinates
			if (Character.isDigit(coordinates.charAt(i)))
			{
				coor.set(1 ,Integer.parseInt(coordinates.substring(i)));
			}
			else
			{	
				// converts the character's ascii value into base 26
				int convert = (int)coordinates.charAt(i) - 96; 
				
				// formula 26^j*convert+convert changes to base 26, lastChar prevents additional last digit 
				col += (int)((Math.pow(26,j) - lastChar) * convert) + convert * lastChar; 
				coor.set(0,col);
				
				j += 1;
				lastChar = 0;
			}
		}
		return coor;
	}

	public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		// amount of coordinate pairs
		int size = coordinateStrings.size();
		
		// hashsets to track knights
		HashSet<Point> points = new HashSet<Point>();		
		
		// loop through all the coordinate pairs
		for (int i = 0; i < size; i++)
		{	
			ArrayList<Integer> coord = convertCoordinates(coordinateStrings.get(i));

			Point knight = new Point(coord.get(0), coord.get(1));

			// Points for sideways L moves flipped on x & y axis
			Point sidewaysDR = new Point(coord.get(0) - 1, coord.get(1) + 2);
			Point sidewaysDL = new Point(coord.get(0) - 1, coord.get(1) - 2);

			Point sidewaysUR = new Point(coord.get(0) + 1, coord.get(1) + 2);
			Point sidewaysUL = new Point(coord.get(0) + 1, coord.get(1) - 2);

			// Points for upright L moves flipped on x & y axis
			Point uprightDR = new Point(coord.get(0) - 2, coord.get(1) + 1);
			Point uprightDL = new Point(coord.get(0) - 2, coord.get(1) - 1);

			Point uprightUR = new Point(coord.get(0) + 2, coord.get(1) + 1);
			Point uprightUL = new Point(coord.get(0) + 2, coord.get(1) - 1);
			  
			points.add(knight);
			
			// check sideways L move going down
			if (points.contains(sidewaysDR))
			{
				return false;
			}
			else if (points.contains(sidewaysDL))
			{
				return false;
			}
			
			// check L move going down
			else if (points.contains(uprightDR))
			{
				return false;
			}
			else if (points.contains(uprightDL))
			{
				return false;
			}
			
			// check sideways L move going up
			else if (points.contains(sidewaysUR))
			{
				return false;
			}
			else if (points.contains(sidewaysUL))
			{
				return false;
			}
			
			// check L move going up
			else if (points.contains(uprightUR))
			{
				return false;
			}
			else if (points.contains(uprightUL))
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

