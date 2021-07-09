Coursework 2
Compiled using Visual Studio Command Line (C++ must be installed in VS)

This program uses C++ to read a C file and output a symbol table.

To run the program, write nmake on the console. To clean the program, write nmake clean.

Toolchain: Visual Studio 2019 Developer Command Prompt v16.8.4


Makefile targets:

	partA -> compiles symbol_table.cpp

	partB -> compiles partB.cpp, builds the library and links everything

	BST -> just builds the library (BST.h and BST.cpp)

	clean -> Remove all object, executables and library files