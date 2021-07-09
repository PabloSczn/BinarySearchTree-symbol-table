/*
 * Author: Pablo Sanchez Narro
 * Matriculation number: 40486559
 * Binary Search Tree Implementation
 * 
 * Last date of modification: 01/05/2021
*/

#include "BST.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/*Private Methods*/

//To empty the tree
node* BST::empty_tree(node* tree) 
{
	if(tree == NULL)
	{
		return NULL;
	}
	else
	{
		empty_tree(tree->left);
		empty_tree(tree->right);
		delete tree;
	}
	return NULL;
}

//Does the counting for each variable/function and inserts it if it is not in the tree
node* BST::update(string nameVF, int lineVF, string voF, string typeVF, int functionIdentifier, node* tree)
{
	if(tree == NULL && voF != "-")
	{
		tree = new node;
		tree->name = nameVF;
		tree->line = lineVF;
		tree->varOrFunc = voF;
		tree->type = typeVF;
		tree->functionId = functionIdentifier;
		tree->left = tree->right = NULL;
		if(typeVF == "int" || typeVF == "char []")
		{
			tree->references = 0;
		}
		else
		{
			tree->references = -1;
		}
	}			
	else if(tree == NULL && voF == "-")
	{
		delete tree;
	}				
	//References for functions
	else if(nameVF == tree->name && tree->varOrFunc == "function" && tree != NULL)
	{
		tree->references += 1;
	}	
	else if(nameVF < tree->name || functionIdentifier < tree->functionId)
	{
		tree->left = update(nameVF, lineVF, voF, typeVF, functionIdentifier, tree->left);
	}
	else if(nameVF > tree->name || functionIdentifier > tree->functionId)
	{
		tree->right = update(nameVF, lineVF, voF, typeVF, functionIdentifier, tree->right);
	}        									
	//References for variables
	else if(nameVF == tree->name)
	{
		tree->references += 1;
	}			
	//To take two variables with the same name as separate variables
	else if(nameVF == tree->name && voF != "-" && functionIdentifier != tree->functionId && tree->varOrFunc == "variable")
	{
		tree = new node;
		tree->name = nameVF;
		tree->line = lineVF;
		tree->varOrFunc = voF;
		tree->type = typeVF;
		tree->references = 0;
		tree->left = tree->right = NULL;
		
	}						
	return tree;
}

//Finds the minimum node (used to remove)
node* BST::find_min(node* tree)
{
	if(tree == NULL)
	{
		return NULL;
	}
	else if(tree->left == NULL)
	{
		return tree;
	}
	else
	{
		return find_min(tree->left);
	}
}

//Removes node
node* BST::remove(string nameVF, node* tree) 
{
	node* temp;
	if(tree == NULL)
	{
		return NULL;
	}
	else if(nameVF < tree->name)
	{
		tree->left = remove(nameVF, tree->left);	
	}
	else if(nameVF > tree->name)
	{
		tree->right = remove(nameVF, tree->right);
	}
	else if(tree->left && tree->right)
	{
		temp = find_min(tree->right);
		tree->name = temp->name;
		tree->right = remove(tree->name, tree->right);
	}
	else
	{
		temp = tree;
		if(tree->left == NULL)
		{
			tree = tree->right;
		}
		else if(tree->right == NULL)
		{
			tree = tree->left;
		}
		delete temp;
	}

	return tree;
}

//To print the Binary Search Tree in alphabetical order
void BST::in_order(node* tree) 
{
	if(tree == NULL)
	{    
		return;
	}	
	
	in_order(tree->left);

	cout << tree->name << ", line " << tree->line << ", " << tree->varOrFunc
	<< ", " << tree->type << ", referenced " << tree->references << endl;

	in_order(tree->right);
}


/*Public Methods*/

//Creates an empty tree
BST::BST()
{
    root = nullptr;
}

//Destructor
BST::~BST()		
{
	root = empty_tree(root);
}

//Counts how many times a variable or function appears and insert it if is not in the tree
void BST::update(string nameVF, int lineVF, string voF, string typeVF, int functionIdentifier)
{
	root = update(nameVF, lineVF, voF, typeVF, functionIdentifier, root);	
}

//Remove nodes
void BST::remove(string nameVF)
{
	root = remove(nameVF, root);
}

//Prints the tree in order
void BST::print()
{
	in_order(root);
	cout << endl;
}