// Nawras Rawas Qalaji, NID: na413580
// COP 3503, Fall 2021
// Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)

import java.io.*;
import java.util.*;

class Node<AnyType>
{
	AnyType data;
	int height;
	
	// list that holds pointers to next nodes
	ArrayList<Node<AnyType>> next = new ArrayList<Node<AnyType>>();
	
	Node(int height)
	{
		this.height = height;
		
		// initialize next with nodes
		for (int i = 0; i < height; i++) 
		{
			Node<AnyType> n = null;
			next.add(i, n);
		}
	}
	
	Node(AnyType data, int height)
	{
		this.data = data;
		this.height = height;
		
		for (int i = 0; i < height; i++) 
		{
			Node<AnyType> n = null;
			next.add(i, n);
		}
	}
	
	public AnyType value()
	{
		try
		{
			return data;
		}
		catch (NullPointerException error) 
		{
			return null;
		}
	}
	
	public int height()
	{
		try
		{
			return height;
		}
		catch (NullPointerException error) 
		{
			return 0;
		}
	}
	
	public Node<AnyType> next(int level)
	{
		if (level < 0 || level > height - 1)
		{
			return null;
		}
		
		return next.get(level);
	}
	
	public void grow()
	{
		Node<AnyType> n = null;
		next.add(n);
		height += 1;
	}
	
	public void trim(int height)
	{
		for (int i = 0; i < height; i++)
		{
			next.remove(next.size() - 1);
			this.height -= 1;
		}
	}
}

public class SkipList<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> head;
	private Node<AnyType> current;
	int height;
	
	// number of nodes
	int count = 0;
	
	SkipList()
	{
		height = 1;
		head = new Node<AnyType>(1);
		current = head;
	}
	
	SkipList(int height)
	{
		if (height > 0)
		{
			this.height = height;	
			
			// first head node keeps track of height
			head = new Node<AnyType>(height);
		}
		
		current = head;
	}
	
	public int size()
	{
		return count;
	}
	
	public int height()
	{
		return height;
	}
	
	public Node<AnyType> head()
	{
		return head;
	}
	
	// returns max height based on amount of nodes vs current height
	public int getMaxHeight()
	{
		int log = (int) Math.ceil(Math.log(count) / Math.log(2));
		int maxHeight = (height() > log) ? height() : log;
		
		return maxHeight;
	}
	
	// 1/(2^k) % chance of returning height k
	public int generateRandomHeight(int count)
	{
		int newHeight = 1;
		
		for (int i = 0; i < getMaxHeight() - 1; i++)
		{
			if (1 == (int) (Math.random() * 2))
			{
				newHeight += 1;
			}
			else
			{
				break;
			}
		}
		
		return newHeight;
	}
	
	public void growSkipList(ArrayList<Node<AnyType>> nodePath, Node<AnyType> node)
	{
		int maxHeight = getMaxHeight();
		
		// check if new node is higher than current max height
		maxHeight = (node.height() > maxHeight) ? node.height() : maxHeight;
		
		int secondHeighest = current.height() - 3;
		int random;
		
		// move off of root
		current = head.next(secondHeighest);
		
		// grow head to match proper height while tracking nodepath
		for (int i = head.height; i < maxHeight; i++)
		{
			head.grow();
			this.height += 1;
			nodePath.add(i, head);
		}
		
		// parse through the second heighest nodes in the skiplist
		while (current != null) 
		{	
			// 50% chance to grow if nodes were maxed out
			random = (int) (Math.random() * 2);
			if (random == 1)
			{
				current.grow();
			}
			
			current = current.next(secondHeighest);
		}
		
		// 50% chance to grow new node if it was maxed out
		random = (int)(Math.random() * 2);
		if (random == 1 && node.height() == secondHeighest)
		{
			node.grow();
		}
	}
	
	// insert node with randomized height
	public void insert(AnyType data)
	{
		current = head;
		ArrayList<Node<AnyType>> nodePath = new ArrayList<Node<AnyType>>();
		
		// initialize nodepath
		for (int i = 0; i < height(); i++)
		{
			Node<AnyType> n = new Node<AnyType>(i);
			nodePath.add(i, n);
		}
		
		// search for node while updating nodepath
		for (int i = height() - 1; i >= 0; i--)
		{
			// keep moving forward until null or next data is to big
			while (current.next(i) != null && data.compareTo(current.next(i).data) > 0)
			{
				current = current.next(i);
			}
			
			// track level then go down by 1
			nodePath.set(i, current);			
		}
		
		// create node to add
		count += 1;
		Node<AnyType> node = new Node<AnyType>(data, generateRandomHeight(count));
		
		// if height must be increased, adjust height 
		if (node.height() > head.height() || getMaxHeight() > head.height())
		{	
			growSkipList(nodePath, node);
		}
		
		// adjust pointers
		for (int i = 0; i < node.height(); i++)
		{
			// new node now points to what previous node pointed too
			node.next.set(i, nodePath.get(i).next(i));
			
			// previous node now points to new node
			nodePath.get(i).next.set(i, node);
		}		
	}
	
	// insert node with specific height
	public void insert(AnyType data, int height)
	{
		current = head;
		ArrayList<Node<AnyType>> nodePath = new ArrayList<Node<AnyType>>();
		
		// initialize nodepath
		for (int i = 0; i < height(); i++)
		{
			Node<AnyType> n = new Node<AnyType>(i);
			nodePath.add(i, n);
		}
		
		// search for node while updating nodepath
		for (int i = height() - 1; i >= 0; i--)
		{
			// keep moving forward until null or next data is to big
			while (current.next(i) != null && data.compareTo(current.next(i).data) > 0)
			{
				current = current.next(i);
			}
			
			// track level then go down by 1 
			nodePath.set(i, current);			
		}
		
		// create node to add
		count += 1;
		Node<AnyType> node = new Node<AnyType>(data, height);
			
		// if height must be increased, adjust height 
		if (node.height() > head.height() || getMaxHeight() > head.height())
		{	
			growSkipList(nodePath, node);
		}
		
		// adjust pointers
		for (int i = 0; i < node.height(); i++)
		{
			// new node now points to what previous node pointed too
			node.next.set(i, nodePath.get(i).next(i));
			
			// previous node now points to new node
			nodePath.get(i).next.set(i, node);
		}
	}
	
	// trims the skiplist while updating the nodepath
	public void trimSkipList(ArrayList<Node<AnyType>> nodePath, Node<AnyType> target)
	{
		int log = (int) Math.ceil(Math.log(count) / Math.log(2));
		log = (log <= 0) ? 1 : log;
		
		int maxHeight = (height() > log) ? log : height();
		
		current = head.next(target.height());
		
		//  trim all heights above max
		while (current != null)
		{
			current.trim(current.height() - maxHeight);
			current = current.next(target.height());
		}
		
		// adjust head to match proper height while tracking nodepath			
		if (height() > maxHeight && maxHeight > 0)
		{
			head.trim(height() - maxHeight);
			this.height -= (height() - maxHeight);
			nodePath.add(head);
		}
	}
	
	public void delete(AnyType data)
	{
		current = head;
		ArrayList<Node<AnyType>> nodePath = new ArrayList<Node<AnyType>>();
		
		// initialize nodepath
		for (int i = 0; i < height(); i++)
		{
			Node<AnyType> n = new Node<AnyType>(i);
			nodePath.add(i, n);
		}
		
		// search for node while updating nodepath
		for (int i = height() - 1; i >= 0; i--)
		{
			while (current.next(i) != null && data.compareTo(current.next(i).data) > 0)
			{
				current = current.next(i);
			}
			
			nodePath.set(i, current);
		}
		
		// if node is found, delete it
		if (current.next(0) != null && data.compareTo(current.next(0).value()) == 0)
		{
			count -= 1;
			Node<AnyType> target = current.next(0);
			
			// adjust height if necessary
			trimSkipList(nodePath, target);
			
			// adjust pointers
			for (int i = 0; i < target.height(); i++)
			{
				// previous node now points to node ahead of target node
				try
				{
					nodePath.get(i).next.set(i, target.next(i));
				}
				
				catch (IndexOutOfBoundsException error)
				{
					continue;
				}
			}
		}
	}
	
	public boolean contains(AnyType data)
	{
		current = head;
		
		for (int i = height() - 1; i >= 0; i--)
		{
			while (current.next(i) != null && data.compareTo(current.next(i).data) > 0)
			{
				current = current.next.get(i);
			}
			
			if (current.next(i) != null && data.compareTo(current.next(i).data) == 0)
			{
				return true;
			}
		}
		return false;
	}
	
	public Node<AnyType> get(AnyType data)
	{
		current = head;
		
		for (int i = height() - 1; i >= 0; i--)
		{
			while (current.next(i) != null && data.compareTo(current.next(i).data) > 0)
			{
				current = current.next.get(i);
			}
			if (current.next(i) != null && data.compareTo(current.next(i).data) == 0)
			{
				return current.next(i);
			}
		}
		return null;
	}
	
	public static double difficultyRating()
	{
		return 5.0;
	}

	public static double hoursSpent()
	{
		return 48.0;
	}
	
}
