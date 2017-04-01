#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 5)), t2(NodeValue(OPERAND, "sin")), *t3 = new Node (NodeValue(VARIABLE, "x"));
	
	//Node root(t1 * t2);
	t2.InsertLeft(t3);
	d(t2);
	//root = d(root);

	t2.DumpToPNG("test7");
	//delete t3;
	system("pause");/////hyumoi
	return 0;
}