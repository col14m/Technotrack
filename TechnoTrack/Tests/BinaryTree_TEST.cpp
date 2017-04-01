#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)), t2(NodeValue(OPERAND, "sin")), t3 (NodeValue(VARIABLE, "x"));
	
	Node root(t3 ^ t1);
	//t2.InsertLeft(t3);
	//root = d(root);


	d(root).DumpToPNG("test7");
	//delete t3;
	system("pause");/////hyumoi
	return 0;
}