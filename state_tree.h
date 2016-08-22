// Created by Bryan Pakulski 

#include <cstddef>
#include <stdio.h>
#include <vector>
#include <queue>

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
	bool _BFS_(TYPE searchterm, Node<TYPE> *leaf);
	bool _IDDFS_(TYPE searchterm, Node<TYPE> *leaf, int depth);
	void _trimDuplicates_(TYPE searchterm, Node<TYPE> *leaf, bool trimming);

	// Overload or edit this function in order to correctly print out the data type you want to display in the printTree function
	void printTYPE(TYPE data);

public:

	tree(void);
	~tree(void);

	// Add node to tree, attach said node to a parent
	void addNode(TYPE key, TYPE parent);

	// Print the current tree and information about it
	void printTree();

	// Breadth First search, searches for the first appearance of the term
	bool BFS(TYPE searchterm);

	// Iterative deepening depth first search
	bool IDDFS(TYPE searchterm, int limit);

	// Trims the tree of all duplicate search term subtrees, essentially a delete function
	void trimDuplicates(TYPE searchterm);

	// Returns hamming distance between two points (state data, not actual nodes)
	int hamming_distance(TYPE x, TYPE y);

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

// Overload this to print out data specific to your application
template <class TYPE> void
tree<TYPE> :: printTYPE(TYPE data)
{
	printf("   data: [");
	for (int i = 0; i < 9; i++)
	{
		printf(" %d ", data.state[i].value);
	}
	printf("]\n");
}

template <class TYPE> void
tree<TYPE> :: _printTree_(Node<TYPE> *leaf, int depth)
{
	// If valid leaf
	if (leaf)
	{
		// The depth + 4 variable is used as padding to visualise the tree
		printf("%*.s" "depth: %d", depth + 4, " ", depth);
		printTYPE(leaf->data);

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


// Breadth First Search, returns true if item exists
template <class TYPE> bool
tree<TYPE> :: BFS(TYPE searchterm)
{
	if (_BFS_(searchterm, root))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class TYPE> bool
tree<TYPE> :: _BFS_(TYPE searchterm, Node<TYPE> *leaf)
{
	// Search queue
	std::queue<Node<TYPE> *> Q;

	if (leaf)
	{
		Q.push(leaf);

		while(!Q.empty())
		{
			Node<TYPE> *t = Q.front();

			Q.pop();

			if(t->data == searchterm){
				return true;
			}

			for (int i = 0; i < t->leaves.size(); i++)
			{
				Q.push(t->leaves[i]);
			}
			
		}
	}

	return false;
}


// Iterative Deepening Depth First Search, returns true if item exists
template <class TYPE> bool
tree<TYPE> :: IDDFS(TYPE searchterm, int limit)
{
	for (int i = 0; i < limit; i++)
	{
		if (_IDDFS_(searchterm, root, i))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

template <class TYPE> bool
tree<TYPE> :: _IDDFS_(TYPE searchterm, Node<TYPE> *leaf, int depth)
{
	if (depth == 0 && leaf->data == searchterm)
	{
		return true;
	}
	else if (depth > 0)
	{
		for (int i = 0; i < leaf->leaves.size(); i++)
		{
			if (_IDDFS_(searchterm, leaf->leaves[i], depth-1))
			{
				return true;
			}
		}
	}

	return false;
}

// Hamming distance function, taken from https://en.wikipedia.org/wiki/Hamming_distance
template <class TYPE> int
tree<TYPE> :: hamming_distance(TYPE x, TYPE y)
{
	int dist = 0;
    unsigned val = x ^ y;

    // Count the number of bits set
    while (val != 0)
    {
        // A bit is set, so increment the count and clear the bit
        dist++;
        val &= val - 1;
    }

    // Return the number of differing bits
    return dist;
}


// Trim function
template <class TYPE> void
tree<TYPE> :: trimDuplicates(TYPE searchterm)
{
	_trimDuplicates_(searchterm, root, false);
}

template <class TYPE> void
tree<TYPE> :: _trimDuplicates_(TYPE searchterm, Node<TYPE> *leaf, bool trimming)
{
	// Search queue
	std::queue<Node<TYPE> *> Q;

	// Recurse through the tree, don't trim unless it's a duplicate, hence the bool argument
	// It gets switched to true once the search term is found
	if (leaf)
	{
		Q.push(leaf);

		while(!Q.empty())
		{

			Node<TYPE> *t = Q.front();

			Q.pop();

			if (t->data == searchterm && trimming == true)
			{
				printf("trimming duplicate leaf of ");
				printTYPE(t->data);
				_destroy_(t);
			}

			if (t->data == searchterm && trimming == false)
			{
				trimming = true;
			}

			for (int i = 0; i < t->leaves.size(); i++)
			{
				Q.push(t->leaves[i]);
			}
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
