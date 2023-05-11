// Nawras Rawas Qalaji, NID:413580
// COP3503C 00381, Fall 2021
// Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)
// Original code by Sean Szumlanski, edited by Nawras Rawas Qalaji

// =============================================================================
// POSTING THIS FILE ONLINE OR DISTRIBUTING IT IN ANY WAY, IN PART OR IN WHOLE,
// IS AN ACT OF ACADEMIC MISCONDUCT AND ALSO CONSTITUTES COPYRIGHT INFRINGEMENT.
// =============================================================================

// =============================================================================
// Overview:
// =============================================================================
//
// You should modify the methods in this file to implement your backtracking
// solution for this assignment. You'll want to transform the solveMaze()
// methods into the findPaths() methods required for this assignment.
//
// =============================================================================
// Disclaimer:
// =============================================================================
//
// As usual, the comments in this file are way overkill. They're intended to be
// educational (and to make this code easier for you to work with), and are not
// indicative of the kind of comments we'd use in the real world.
//
// =============================================================================
// Maze Format (2D char array):
// =============================================================================
//
// This program assumes there is exactly one person ('@') and one exit ('e') per
// maze. The initial positions of those characters may vary from maze to maze.
//
// This program assumes all mazes are rectangular (all rows have the same
// length). There are no guarantees regarding the number of walls in the maze
// or the locations of those walls. It's possible that the outer edges of the
// maze might not be made up entirely of walls (i.e., the outer edge might
// contain spaces).
//
// While there is guaranteed to be a single person ('@') and a single exit ('e')
// in a well-formed maze, there is no guarantee that there exists a path from
// the starting position of the '@' character to the exit.
//
// =============================================================================
// Example:
// =============================================================================
//
// #############
// #@# #   #   #
// #   # # # # #
// # ### # # # #
// #     #   # #
// # ##### #####
// #          e#
// #############
//
// =============================================================================
// Legend:
// =============================================================================
//
// '#' - wall (not walkable)
// '*' - virus (not walkable)
// '.' - breadcrumb (not walkable)
// '@' - person
// 'e' - exit
// ' ' - space (walkable)

import java.io.*;
import java.util.*;

public class Pathogen
{
	// Used to toggle "animated" output on and off (for debugging purposes).
	private static boolean animationEnabled = false;

	// "Animation" frame rate (frames per second).
	private static double frameRate = 4.0;

	// Setters. Note that for testing purposes you can call enableAnimation()
	// from your backtracking method's wrapper method (i.e., the first line of
	// your public findPaths() method) if you want to override the fact that the
	// test cases are disabling animation. Just don't forget to remove that
	// method call before submitting!
	public static void enableAnimation() { Pathogen.animationEnabled = true; }
	public static void disableAnimation() { Pathogen.animationEnabled = false; }
	public static void setFrameRate(double fps) { Pathogen.frameRate = fps; }

	// Maze constants.
	private static final char WALL       = '#';
	private static final char PERSON     = '@';
	private static final char EXIT       = 'e';
	private static final char VIRUS      = '*';
	private static final char BREADCRUMB = '.';  // visited
	private static final char SPACE      = ' ';  // unvisited

	// Takes a 2D char maze and returns true if it can find a path from the
	// starting position to the exit. Assumes the maze is well-formed according
	// to the restrictions above.
	public static HashSet<String> findPaths(char [][] maze)
	{
		int height = maze.length;
		int width = maze[0].length;
		
		HashSet<String> allPaths = new HashSet<String>();
		StringBuilder path = new StringBuilder();
		
		// The visited array keeps track of visited positions. It also keeps
		// track of the exit, since the exit will be overwritten when the '@'
		// symbol covers it up in the maze[][] variable. Each cell contains one
		// of three values:
		//
		//   '.' -- visited
		//   ' ' -- unvisited
		//   'e' -- exit
		
		char [][] visited = new char[height][width];
		
		for (int i = 0; i < height; i++)
			Arrays.fill(visited[i], SPACE);

		// Find starting position (location of the '@' character).
		int startRow = -1;
		int startCol = -1;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (maze[i][j] == PERSON)
				{
					startRow = i;
					startCol = j;
				}
			}
		}
		
		// Let's gooooooooo!!
		allPaths = findPaths(maze, visited, startRow, startCol, height, width, allPaths, path);
		
		return allPaths;
		
	}

	private static HashSet<String> findPaths(char [][] maze, char [][] visited,
	                                 int currentRow, int currentCol,
	                                 int height, int width,
									 HashSet<String> allPaths,
									 StringBuilder path)
	{
		// This conditional block prints the maze when a new move is made.
		if (Pathogen.animationEnabled)
			printAndWait(maze, height, width, "Searching...", Pathogen.frameRate);

		// Hoorayyy!
		if (visited[currentRow][currentCol] == 'e')
		{
			if (Pathogen.animationEnabled)
			{
				char [] widgets = {'|', '/', '-', '\\', '|', '/', '-', '\\',
				                   '|', '/', '-', '\\', '|', '/', '-', '\\', '|'};

				for (int i = 0; i < widgets.length; i++)
				{
					maze[currentRow][currentCol] = widgets[i];
					printAndWait(maze, height, width, "Hooray!", 12.0);
				}

				maze[currentRow][currentCol] = PERSON;
				printAndWait(maze, height, width, "Hooray!", Pathogen.frameRate);
			}
			
			// remove and add back trailing space to follow formatting when adding to hashset
			path.deleteCharAt(path.length() - 1);
			allPaths.add(path.toString());
			path.append(" ");
			
			return allPaths;
		}

		// Moves: left, right, up, down
		int [][] moves = new int[][] {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
		String [] letterMoves = new String[] {"l ", "r ", "u ", "d "};
		
		for (int i = 0; i < moves.length; i++)
		{
			int newRow = currentRow + moves[i][0];
			int newCol = currentCol + moves[i][1];
			
			// Check move is in bounds & not a wall/virus/visited
			if (!isLegalMove(maze, visited, newRow, newCol, height, width))
			{
				continue;
			}
			
			path.append(letterMoves[i]);
			
			// if exit found, save in visited
			if (maze[newRow][newCol] == EXIT)
			{
				visited[newRow][newCol] = EXIT;
			}
			
			// put down breadcrumb trail
			maze[currentRow][currentCol] = BREADCRUMB;
			visited[currentRow][currentCol] = BREADCRUMB;
			maze[newRow][newCol] = PERSON;
			
			// Perform recursive descent.
			allPaths = findPaths(maze, visited, newRow, newCol, height, width, allPaths, path);
			
			// Backtrack
			if (visited[newRow][newCol] == EXIT)
			{
				maze[newRow][newCol] = EXIT;
			}
			else
			{
				maze[newRow][newCol] = SPACE;
				visited[newRow][newCol] = SPACE;
			}
			
			maze[currentRow][currentCol] = PERSON;
			
			// backtrack the path, deleting last two chars (letter and space)
			path.deleteCharAt(path.length() - 1);
			path.deleteCharAt(path.length() - 1);
			
			// This conditional block prints the maze when a move gets undone
			// (which is effectively another kind of move).
			if (Pathogen.animationEnabled)
				printAndWait(maze, height, width, "Backtracking...", frameRate);

		}
		
		return allPaths;
	}
	
	

	// Returns true if moving to row and col is legal 
	private static boolean isLegalMove(char [][] maze, char [][] visited,
	                                   int row, int col, int height, int width)
	{
		if (maze[row][col] == WALL || visited[row][col] == BREADCRUMB || maze[row][col] == VIRUS)
			return false;
		else if ((row >= maze.length - 1) || col >= (maze[0].length - 1) || col <= 0 || row <= 0)
			return false;
		return true;
	}

	// This effectively pauses the program for waitTimeInSeconds seconds.
	private static void wait(double waitTimeInSeconds)
	{
		long startTime = System.nanoTime();
		long endTime = startTime + (long)(waitTimeInSeconds * 1e9);

		while (System.nanoTime() < endTime)
			;
	}

	// Prints maze and waits. frameRate is given in frames per second.
	private static void printAndWait(char [][] maze, int height, int width,
	                                 String header, double frameRate)
	{
		if (header != null && !header.equals(""))
			System.out.println(header);

		if (height < 1 || width < 1)
			return;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				System.out.print(maze[i][j]);
			}

			System.out.println();
		}

		System.out.println();
		wait(1.0 / frameRate);
	}

	// Read maze from file. This function dangerously assumes the input file
	// exists and is well formatted according to the specification above.
	private static char [][] readMaze(String filename) throws IOException
	{
		Scanner in = new Scanner(new File(filename));

		int height = in.nextInt();
		int width = in.nextInt();

		char [][] maze = new char[height][];

		// After reading the integers, there's still a new line character we
		// need to do away with before we can continue.

		in.nextLine();

		for (int i = 0; i < height; i++)
		{
			// Explode out each line from the input file into a char array.
			maze[i] = in.nextLine().toCharArray();
		}

		return maze;
	}
	
	public static double difficultyRating()
	{
		return 2.0;
	}

	public static double hoursSpent()
	{
		return 4.0;
	}

}
