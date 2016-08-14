// Created by Bryan Pakulski 

#include <cstddef>
#include <stdio.h>
#include <vector>

// Our tree data structure, contains data and children nodes
template <typename TYPE> 
struct Node
{
	// Data node storage
	TYPE data;
	// Children pointers
	std::vector<Node*> leaves;
};

// Our main tree class
template <class TYPE>
class tree
{

private:

	// Tree root
	Node<TYPE> *root;

	// Recursive functions go here
	void _destroy_(Node<TYPE> *leaf);
	void _addNode_(TYPE key, TYPE parent, Node<TYPE> *leaf);
	void _printTree_(Node<TYPE> *leaf, int depth);

public:

	tree(void);
	~tree(void);

	// Add node to tree, attach said node to a parent
	void addNode(TYPE key, TYPE parent);

	// Print the current tree and information about it
	void printTree();

};


// Constructor
template <class TYPE> 
tree<TYPE> :: tree(void)
{
	root = NULL;
}


// Deconstructor
template <class TYPE> 
tree<TYPE> :: ~tree(void)
{	
	if (root)
	{
		_destroy_(root);
	}
}


// Addition function
template <class TYPE> void
tree<TYPE> :: addNode(TYPE key, TYPE parent)
{
	if (!root)
	{
		Node<TYPE> *temp = new Node<TYPE>;
		temp->data = key;

		root = temp;
	}
	else
	{
		_addNode_(key, parent, root);
	}
}

template <class TYPE> void
tree<TYPE> :: _addNode_(TYPE key, TYPE parent, Node<TYPE> *leaf)
{

	// Check if state is duplicated
	bool duplicate = false;

	// This will visit every node, as it should in a state machine where shared states can end up at the same final state
	if (leaf->data == parent)
	{
		// No children
		if (leaf->leaves.size() == 0)
		{
			// Append child to parent
			Node<TYPE> *temp = new Node<TYPE>;
			temp->data = key;

			leaf->leaves.push_back(temp);
		}

		// Check for duplicate states
		for (int i = 0; i < leaf->leaves.size(); i++)
		{
			// Exists
			if (key == leaf->leaves[i]->data)
			{
				duplicate = true;
			}
		}

		// No duplicates exist
		if (!duplicate)
		{
			// Append child to parent
			Node<TYPE> *temp = new Node<TYPE>;
			temp->data = key;

			leaf->leaves.push_back(temp);
		}
	}

	// Continue down the tree
	for (int i = 0; i < leaf->leaves.size(); i++)
	{
		_addNode_(key, parent, leaf->leaves[i]);
	}
}


// Print function
template <class TYPE> void
tree<TYPE> :: printTree()
{
	if (!root)
	{
		printf("Empty tree\n");
	}
	else
	{
		_printTree_(root, 0);
	}	
}

template <class TYPE> void
tree<TYPE> :: _printTree_(Node<TYPE> *leaf, int depth)
{
	// If valid leaf
	if (leaf)
	{
		// The depth + 4 variable is used as padding to visualise the tree
		printf("%*.s" "depth: %d\n", depth + 4, " ", depth);
		printf("%*.s" "Value: %d\n", depth + 4, " ", leaf->data);

		// Explore children
		printf("%*.s" "Children (%d): ", depth + 4, " ", leaf->leaves.size());
		for(int i = 0; i < leaf->leaves.size(); i++)
		{
			printf("%d ", leaf->leaves[i]->data);
		}
		printf("\n\n");

		// Recursion down tree
		for (int i = 0; i < leaf->leaves.size(); i++)
		{
			_printTree_(leaf->leaves[i], depth + 1);
		}
	}
}


// Destroy function
template <class TYPE> void
tree<TYPE> :: _destroy_(Node<TYPE> *leaf)
{
	for (int i = 0; i < leaf->leaves.size(); i++)
	{
		_destroy_(leaf->leaves[i]);
	}

	delete leaf;
}