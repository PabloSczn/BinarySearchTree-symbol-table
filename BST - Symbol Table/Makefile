partA:
	cl /EHsc symbol_table.cpp

partB:
	cl /EHsc /c BST.cpp
	lib /OUT:BST.lib BST.obj
	cl /EHsc /c partB.cpp
	link partB.obj BST.lib

BST:
	cl /EHsc /c BST.cpp
	lib /OUT:BST.lib BST.obj
	
clean:
	del *.obj
	del *.exe
	del *.lib