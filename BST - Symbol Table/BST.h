/*
 * Author: Pablo Sanchez Narro
 * Matriculation number: 40486559
 * Binary Search Tree Class
 * 
 * Last date of modification: 01/05/2021
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

//Node of the Binary Search Tree
struct node 
{
	string name;
	int line;
	string varOrFunc;
	string type;
	int references;
	int functionId;
	
	//Left child
	node* left;
	//Right child
	node* right;
};

class BST 
{
	private:    

		node* root;	

		//To empty the tree
		node* empty_tree(node* tree);
		
		//Does the counting for each variable/function and inserts it if it is not in the tree
		node* update(string nameVF, int lineVF, string voF, string typeVF, int functionIdentifier, node* tree);

		//Finds the minimum node (used to remove)
	    node* find_min(node* tree);

		//Removes node
		node* remove(string nameVF, node* tree);

		//To print the Binary Search Tree in alphabetical order
		void in_order(node* tree);
	

	public:
		BST();	//Creates an empty tree
		~BST();	//Destructor

		//Counts how many times a variable or function appears and insert it if is not in the tree
		void update(string nameVF, int lineVF, string voF, string typeVF, int functionIdentifier);
		
		//Remove nodes
		void remove(string nameVF);
		
		//Prints the tree in order
		void print();

};