/*
 * Author: Pablo Sanchez Narro
 * Matriculation number: 40486559
 * Reads a C file and outputs its info and the symbol table in order thanks to the BST
 * 
 * Last date of modification: 01/05/2021
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "BST.h"

using namespace std;

//Void Type
const string voidType = "void";

/*Primitive types*/
const string primitiveTypes[16] = {"bool", "bool*", "char", "char*", "int", "int*",
							  "float", "float*", "double", "double*", "wchar_t",
							  "wchar_t*", "short", "short*", "long", "long*"};

/*Elements of the struct*/
string name, varOrFunc, type;
int functionIdentifier;


/*Functions and variables*/
vector<string> function_list;
vector<string> variable_list;


/*Functions*/
int command_la (int arg);
int get_info (char *file);
int output_file();


/*Binary Search Tree*/
BST tree;


/*Main function*/
int main(int argc, char** argv)
{
	//Cleans screen
	system("cls");	
	
	//Command Line Arguments checker
	command_la(argc);
	
	//File to open
	char* inFile = argv[1];
	
	//Reads information from the C file and stores it on the tree
	get_info(inFile);
	
	//Print the tree in order
	tree.print();
	
	//Remove nodes
	for(int i = 0; i < function_list.size(); i++)
	{
		tree.remove(function_list[i]);
	}	
	for(int j = 0; j < variable_list.size(); j++)
	{
		tree.remove(variable_list[j]);
	}	
	

	//Program ended succesfully
    return 0; 
}


/*Checks if command line arguments are correct*/
int command_la (int arg)
{
	int status = 0;
	
	if (arg > 2)	
	{
		cerr << "You can only read one file!" << endl;
		exit(1);		
	}
	else if (arg < 2)
	{
		cerr << "What file you want to open?" << endl;
		exit(1);
	}	

	return 0;
}


/*Reads the C code and stores its info on the tree*/
int get_info (char *inFile)
{
	ifstream file;
	file.open(inFile);

	//Check for error
	if(file.fail())
	{
		cerr << "Could not open file!" << endl;
		exit(1);
	}
	
	//To go through the code
	string line;
    string token;
    int line_counter = 0;
    functionIdentifier = -1;	//After declaration it will be 0

	//Goes through the file and stores the symbol table on the tree
    while(getline(file, line))
    {
        stringstream stream(line);

        line_counter++;
		
		//Checks the word
        while(stream >> token)
        {
			if(token == voidType)
			{
				stream >> token;
				tree.update(token, line_counter, "function", voidType, functionIdentifier);
				function_list.push_back(token);
				functionIdentifier++;
			}
			//Iterates through primitive types
			for (int i = 0; i < size(primitiveTypes); i++)
			{
				if(token == "int")
				{
					//Stores temporaly the the var/func type
					string varOrFuncType = token;
					stream >> token;
					//Stores temporaly the name of the var/func
					string varOrFunc = token;
					stream >> token;
					
					if(token != "(")	//If it's not a function (so it's a variable)
					{
						tree.update(varOrFunc, line_counter, "variable", varOrFuncType, functionIdentifier);
						variable_list.push_back(varOrFunc);
					}
					else	//If it's not a variable it's a funciton
					{
						tree.update(varOrFunc, line_counter, "function", varOrFuncType, functionIdentifier);
						functionIdentifier++;
						function_list.push_back(varOrFunc);
					}
				}
				else if (token == "long")
				{
					stream >> token;
					//Find "long long"
					if(token == "long")
					{
						stream >> token;
						tree.update(token, line_counter, "variable", "long long", functionIdentifier);						
						variable_list.push_back(token);
					}
					else	//If it's not a long long, it's a long
					{
						tree.update(token, line_counter, "variable", "long", functionIdentifier);						
						variable_list.push_back(token);
					}	
				}
				else if(token == "char")
				{

					stream >> token;
					
					//Stores temporaly the name of the var/func
					string varOrFunc = token;

					stream >> token;
					
					if(token != "(")	//If it's not a function (so, it's a variable)
					{	if(token == "[]")	//If it's char[]
						{
							tree.update(varOrFunc, line_counter, "variable", "char []", functionIdentifier);						
							variable_list.push_back(varOrFunc);
						}
						else	//If it's char
						{
							tree.update(varOrFunc, line_counter, "variable", "char", functionIdentifier);						
							variable_list.push_back(varOrFunc);
						}					
					}
					else	//If it's not a variable it's a funciton
					{
						tree.update(varOrFunc, line_counter, "function", "char", functionIdentifier);						
						functionIdentifier++;
						function_list.push_back(varOrFunc);
					}
				}
				else if (token == primitiveTypes[i])
				{
					string varType = primitiveTypes[i];
					stream >> token;
					tree.update(token, line_counter, "variable", varType, functionIdentifier);						
					variable_list.push_back(token);
				}
			}
			
			//To do the counting
			tree.update(token, line_counter, "-", " ", functionIdentifier);						
		}
	}

	file.close();
	
	cout << "In order function for the Tree:" << endl;
	cout << endl;
	


	return 0;
}