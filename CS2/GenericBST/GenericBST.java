// Nawras Rawas Qalaji, NID:413580
// COP 3503, Fall 2021
// Using Notepad++ and Linux Bash Shell on Windows 10 (ubuntu)

// ====================
// GenericBST: BST.java
// ====================
// Basic binary search tree (BST) implementation that supports insert() and
// delete() operations. This framework is provided for you to modify as part of
// Programming Assignment #2.


import java.io.*;
import java.util.*;

// Binary search tree node, has variables for storing data of anytype and for pointing to the left and right nodes in the tree
class Node<AnyType>
{	
	AnyType data;
	Node<AnyType> left, right;

	Node(AnyType data)
	{
		this.data = data;
	}
}

public class GenericBST<AnyType extends Comparable<AnyType>>
{
	private Node<AnyType> root;
	
	// inserts new node into BST using the insert(Node<AnyType> root, AnyType data) function
	public void insert(AnyType data)
	{
		root = insert(root, data);
	}
	
	// inserts a node into the binary tree using BST sorting rules, e.g. lower numbers inputed left side, ect; returns the new root
	private Node<AnyType> insert(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return new Node<AnyType>(data);
		}
		// since generic type, must use compareTo method from Comparable to search through tree
		else if (data.compareTo(root.data) == -1)
		{
			root.left = insert(root.left, data);
		}
		else if (data.compareTo(root.data) == 1)
		{
			root.right = insert(root.right, data);
		}

		return root;
	}

	// deletes node from BST using the delete(Node<AnyType> root, AnyType data) function 
	public void delete(AnyType data)
	{
		root = delete(root, data);
	}
	// finds node in binary tree and deletes it using BST sorting rules, sorting the newly edited tree afterwards; returns the new root
	private Node<AnyType> delete(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return null;
		}
		else if (data.compareTo(root.data) == -1)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo(root.data) == 1)
		{
			root.right = delete(root.right, data);
		}
		else
		{
			if (root.left == null && root.right == null)
			{
				return null;
			}
			else if (root.left == null)
			{
				return root.right;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is not empty.
	private AnyType findMax(Node<AnyType> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}
	
	// searches for specific node in BST using the contains(Node<AnyType> root, AnyType data) function; returns boolean if found or not
	public boolean contains(AnyType data)
	{
		return contains(root, data);
	}
	
	// searches for specifc node in tree using the BST sorting rules; returns boolean if found or not
	private boolean contains(Node<AnyType> root, AnyType data)
	{
		if (root == null)
		{
			return false;
		}
		else if (data.compareTo(root.data) == -1)
		{
			return contains(root.left, data);
		}
		else if (data.compareTo(root.data) == 1)
		{
			return contains(root.right, data);
		}
		else
		{
			return true;
		}
	}
	
	// prints BST in inorder using recursive inorder() function
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}
	// used above
	private void inorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	// prints BST in preorder using recursive preorder() function
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	// used above
	private void preorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}
	
	// prints BST in postorder using recursive postorder() function
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}
	
	// used above
	private void postorder(Node<AnyType> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

	public static double difficultyRating()
	{
		return 1.0;
	}

	public static double hoursSpent()
	{
		return 3.0;
	}
}
