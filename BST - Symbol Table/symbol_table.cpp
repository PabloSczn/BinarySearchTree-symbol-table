/*
 * Author: Pablo Sanchez Narro
 * Matriculation number: 40486559
 * Reads a C file, outputs its info and the symbol table as a text file
 * 
 * Last date of modification: 10/04/2021
*/

#include <iostream>
#include <new>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//Var and function names and types
string *varNames, *funcNames, *varTypes, *funcTypes;

//References for var and functions
int *funcRef, *lineFunctions, **varRefonFunc, **lineVar;

//Void Type
const string voidType = "void";

/* Primitive types */
const string primitiveTypes[16] = {"bool", "bool*", "char", "char*", "int", "int*",
							  "float", "float*", "double", "double*", "wchar_t",
							  "wchar_t*", "short", "short*", "long", "long*"};

//If statements
const string ifStatement = "if";

//While loops
const string whileLoop = "while";

//For loops
const string forLoop = "for";

/*Counters*/
int ifS, whileL, forL, nofVariables, nofFunctions, nofLines;

/*Functions*/
int error_checker (int status);
int command_la (int arg);
int get_info (char *file);
int iniSymbolTable (char *inFile);
int output_file();


/*Main function*/
int main(int argc, char** argv)
{
	//Cleans screen
	system("cls");	
	
	int status = 0;
	
	//Command Line Arguments checker
	command_la(argc);
	
	//File to open
	char* inFile = argv[1];
	
	//If, while, for
	get_info(inFile);
	
	//Initialise Symbol Table information
	iniSymbolTable(inFile);
	
	//Outputs file
	output_file();

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


/*Reads the C code and outputs its info*/
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
	string code;
	
	//Initialise
	ifS = 0;
	whileL = 0;
	forL = 0;
	nofVariables = 0; 
	nofFunctions = 0;
	
	//Information to output on the console
	while (!file.eof())
	{
		file >> code;
		
		if(code == voidType)
		{
			nofFunctions++;
		}
		else if (code == ifStatement)
		{
			ifS++;
		}
		else if (code == whileLoop)
		{
			whileL++;
		}		
		else if (code == forLoop)
		{
			forL++;
		}
		
		//Iterates through primitive types
		for (int i = 0; i < size(primitiveTypes); i++)
		{
			if(code == "int")
			{
				//Go two words ahead
				file >> code;
				file >> code;
				
				if(code != "(")	//If it's not a function (so, it's a variable)
				{
					nofVariables++;
				}
				else	//If it's not a variable it's a funciton
				{
					nofFunctions++;
				}
			}
			else if (code == "long")
			{
				//Avoid counting "long long" as two different
				nofVariables++;
				file >> code;
				file >> code;
			}
			else if (code == primitiveTypes[i])
			{
				nofVariables++;
			}
		}
		
		
	}
	//Rewind
	file.clear();
	file.seekg(0, ios::beg);
	file.close();
	
	//Ouput the information on the console
	cout << "Variables: " << nofVariables << endl;
	cout << "Functions: " << nofFunctions << endl;
	cout << "If Statements: " << ifS << endl;
	cout << "For loops: " << forL << endl;
	cout << "While Loops: " << whileL << endl;
	
	return 0;
}


/*Initialise output file information*/
int iniSymbolTable (char *inFile)
{	
	//To store name of variables
	varNames = new string[nofVariables];
	int i = 0;	//Counter to advance in index

	//To store variable types (of each variable)
	varTypes = new string[nofVariables];	
	
	//To store name of functions
	funcNames = new string[nofFunctions];
	int j = 0;	//Counter to advance in index

	//To store function types (of each function)
	funcTypes = new string[nofFunctions];
	
	
	//Open file
	ifstream file;
	file.open(inFile);

	//Check for error
	if(file.fail())
	{
		cerr << "Could not open file!" << endl;
		exit(1);
	}
	
	//To go through the code
	string code;
	
	//To store names and types
	while (!file.eof())
	{
		file >> code;
		
		if(code == voidType)
		{
			funcTypes[j] = code;
			file >> code;
			funcNames[j] = code;
			j++;
		}

		//Iterates through primitive types
		for (int p = 0; p < size(primitiveTypes); p++)
		{
			if(code == "int")
			{
				//Stores temporaly the name of the var/func type
				string varOrFuncType = code;
				
				file >> code;
				
				//Stores temporaly the name of the var/func
				string varOrFunc = code;

				file >> code;
				
				
				if(code != "(")	//If it's not a function (so, it's a variable)
				{					
					varTypes[i] = varOrFuncType;	
					varNames[i] = varOrFunc;	
					i++;
				}
				else	//If it's not a variable it's a funciton
				{
					funcTypes[j] = varOrFuncType;
					funcNames[j] = varOrFunc;
					j++;
				}
			}
			else if(code == "char")
			{

				file >> code;
				
				//Stores temporaly the name of the var/func
				string varOrFunc = code;

				file >> code;
				
				
				if(code != "(")	//If it's not a function (so, it's a variable)
				{	if(code == "[]")
					{
						varTypes[i] = "char []";
					}
					else
					{
						varTypes[i] = "char";			
					}					
					varNames[i] = varOrFunc;
					i++;
				}
				else	//If it's not a variable it's a funciton
				{
					funcTypes[j] = "char";
					funcNames[j] = varOrFunc;
					j++;
				}
			}
			//Long or long long
			else if (code == "long")
			{
				file >> code;
				if (code == "long")
				{
					varTypes[i] = "long long";
					file >> code;
					varNames[i] = code;
					i++;
				}
				else
				{
					varTypes[i] = "long";
					varNames[i] = code;
					i++;					
				}
			}
			else if (code == primitiveTypes[p])
			{
				varTypes[i] = code;
				file >> code;
				varNames[i] = code;
				i++;
			}
		}
		
		
	}
	//Rewind
	file.clear();
	file.seekg(0, ios::beg);

	//Function references
	funcRef = new int[nofFunctions];
	
	//Function number of lines
	lineFunctions = new int[nofFunctions];
	
	//Initialise references to -1 (to include declaration)
	//After declaration this will be 0
	for(int w = 0; w < nofFunctions; w++)
	{
		funcRef[w] = -1;
	}	

	//Initialise number of lines
	nofLines = 0;
	for (int z = 0; z < nofFunctions; z++)
	{
		lineFunctions[z] = 0;
	}
	
	string line;
	string token;
	while(getline(file, line))
	{
		nofLines++;
		stringstream stream(line);
		while(stream >> token)
		{
			for (int q = 0; q < nofFunctions; q++)
			{
				if (token == funcNames[q])
				{
					if(funcRef[q] == -1)		//Before declaration (avoiding override)
					{
						lineFunctions[q] = nofLines;		//The line where it is declared
					}
					funcRef[q]++;
				}
			}	
		}
	}
	//Rewind
	file.clear();
	file.seekg(0, ios::beg);


	//References of variables on functions
	varRefonFunc = new int*[nofFunctions];
	for (int o = 0; o < nofFunctions; o++)
	{
		// varRefonFunc[nofFunctions][nofVariables]
		varRefonFunc[o] = new int[nofVariables];
	}
	
	//Initialise
	for(int i = 0; i < nofFunctions; i++)
	{
		for(int j = 0; j < nofVariables; j++)
		{
			varRefonFunc[i][j] = -1;
		}
	}
	
	//To go through code
	string word;
	int t = 0;
	//To get variable references
	while(!file.eof())
	{
		file >> word;
		if(word == funcNames[t])
		{
			//while it doesn't reach the next function nor the end of the file
			while(word != funcNames[t+1] && !file.eof())
			{
				file >> word;
				for(int s = 0; s < nofVariables; s++)
				{
					if(word == varNames[s])
					{
						//varRefonFunc[functions][variables]++
						*(*(varRefonFunc+t)+s) += 1;
					}
					else if(word == funcNames[t+1])	//If another function is found
					{
						//Increase function counter
						t++;
						continue;
					}					
				}
			}
			
		}
	}
	//Rewind
	file.clear();
	file.seekg(0, ios::beg);

	//Line of variables in each function
	lineVar = new int*[nofFunctions];
	for (int o = 0; o < nofFunctions; o++)
	{
		// lineVar[nofFunctions][nofVariables]
		lineVar[o] = new int[nofVariables];
	}
	
	//Initialise
	for(int i = 0; i < nofFunctions; i++)
	{
		for(int j = 0; j < nofVariables; j++)
		{
			lineVar[i][j] = 0;
		}
	}


	//To go through functions
	int func = -1;
	//TO go through variables
	int v = 0;
	int nLines = 0;
	
	string line2;
	string token2;
	//To get the lines where the duplicate variables are initialised
	while(getline(file, line2))
	{
		nLines++;
		stringstream stream(line2);
		while(stream >> token2)
		{	
			for (int p = 0; p < size(primitiveTypes); p++)
			{
				if(token2 == "int")
				{
					stream >> token2;
					stream >> token2;
					
					if(token2 != "(")	//If it's not a function (variable)
					{		
						//lineVar[nofFunctions][nofVariables] (In each function, nofLines of each variable)				
						*(*(lineVar+func)+v) = nLines;
						v++;
					}
					else	//It it's a function
					{
						func++;
					}
				}
				else if (token2 == primitiveTypes[p])
				{
					//lineVar[nofFunctions][nofVariables]
					*(*(lineVar+func)+v) = nLines;
					v++;
				}	
			}
			if(token2 == voidType)
			{
				func++;
			}
		}
	}
	
	file.close();
	cout << endl;	

	
	return 0;
}


/*Outputs symbol_table*/
int output_file ()
{
	ofstream outFile;	
	outFile.open("identifiers.txt"); // Name file indetifiers.txt
	
	//To remove duplicates
	string varN = "";
	
	//For each function
	for(int l = 0; l<nofFunctions; l++)
	{
		//Outputs functions information 
		outFile << funcNames[l] << ", line " << lineFunctions[l] << ", function, " << funcTypes[l] <<
		", referenced " << funcRef[l]<< endl;
		
		for(int k = 0; k<nofVariables; k++)			
		{
			//Outputs variable informations, without duplicates
			//varRefonFunc[functions][variables] goes through each function and for each variable counts  the time it appears on the function
			if(varRefonFunc[l][k] != -1 && funcNames[l] != "main" && varN != varNames[k]&& varN != varNames[k+1] && lineVar[l][k] != 0)
			{
				outFile << varNames[k] << " (" << funcNames[l] << "), " << "line " << lineVar[l][k] 
				<< ", variable, " << varTypes[k] << ", referenced " << varRefonFunc[l][k] << endl;
				varN = varNames[k];
			}
			else if(varRefonFunc[l][k] != -1 && funcNames[l] != "main" && varN != varNames[k]&& varN != varNames[k-1] && lineVar[l][k] != 0)
			{
				outFile << varNames[k] << " (" << funcNames[l] << "), " << "line " << lineVar[l][k]
				<< ", variable, " << varTypes[k] << ", referenced " << varRefonFunc[l][k] << endl;
				varN = varNames[k];
			}			
			
			//lineVar (liveVar[functions][variables]) goes through each variable for each function so we have to find the index of the variable
			else if(varRefonFunc[l][k] != -1 && funcNames[l] != "main" && varN != varNames[k]&& varN != varNames[k-1]&& lineVar[l][k] == 0)
			{
				int index = 0;
				for(int i = 0; i < nofFunctions; i++)
				{
					for(int j = 0; j < nofVariables; j++)
					{
						if(i == l && varN != varNames[j] && lineVar[i][j] != 0)
						{
							index = j;
						}
					}
				}
				
				outFile << varNames[k] << " (" << funcNames[l] << "), " << "line " << lineVar[l][index]
				<< ", variable, " << varTypes[k] << ", referenced " << varRefonFunc[l][k] << endl;
				varN = varNames[k];
			}

		}
		
	}
	
	//For the variables of the main function
	//When "long long" is found change the index by one
	int change = 0;
	for(int l = 0; l<nofFunctions; l++)
	{		
		for(int k = 0; k<nofVariables; k++)
		{
			if(varRefonFunc[l][k] != -1 && funcNames[l] == "main" && varN != varNames[k] && varTypes[k] != "long long"&& change == 0)
			{	
				varN = varNames[k];
				outFile << varNames[k] << ", line " << lineVar[l][k] 
				<< ", variable, " << varTypes[k] << ", referenced " << varRefonFunc[l][k] << endl;
			}
			else if(varRefonFunc[l][k] != -1 && funcNames[l] == "main" && varN != varNames[k]&& change == 0)
			{	
				k++;
				varN = varNames[k];
				outFile << varNames[k-1] << ", line " << lineVar[l][k] 
				<< ", variable, " << varTypes[k-1] << ", referenced " << varRefonFunc[l][k-1] << endl;
				
				change = 1;
			}
			else if(varRefonFunc[l][k] != -1 && funcNames[l] == "main" && varN != varNames[k] && change == 1)
			{
				if(k+1 == nofVariables) //Final pair of variables
				{	
					//Penultimate
					outFile << varNames[k-1] << ", line " << lineVar[l][k] 
					<< ", variable, " << varTypes[k-1] << ", referenced " << varRefonFunc[l][k-1] << endl;	
					
					//Last
					outFile << varNames[k] << ", line " << lineVar[l][k+1] 
					<< ", variable, " << varTypes[k] << ", referenced " << varRefonFunc[l][k] << endl;
				}
				else
				{
					outFile << varNames[k-1] << ", line " << lineVar[l][k] 
					<< ", variable, " << varTypes[k-1] << ", referenced " << varRefonFunc[l][k-1] << endl;					
				}
			}

		}
		
	}
	
	outFile.close();
	
	//Free memory - Avoiding memory leaks! ;)
	delete[] varNames;
	delete[] funcNames;
	delete[] varTypes;
	delete[] funcTypes;
	delete[] funcRef;
	delete[] lineFunctions;
	for(int i = 0; i < nofFunctions; i++)
	{
		delete[] varRefonFunc[i];	
	}
	delete[] varRefonFunc;
	varRefonFunc = NULL; //To not point to a space of memory we're not using
	for(int i = 0; i < nofFunctions; i++)
	{
		delete[] lineVar[i];	
	}
	delete[] lineVar;
	lineVar = NULL; //To not point to a space of memory we're not using
	
	return 0;
}