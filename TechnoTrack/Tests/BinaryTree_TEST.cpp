#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)),*t2 = new Node(NodeValue(OPERAND, "sin")), t3 (NodeValue(VARIABLE, "x")), *t4 = new Node (NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	
	t2->InsertLeft(t4);
	//Node root(t2);
	//t2.InsertLeft(t3);
	//root = d(root);


	d(*t2).DumpToPNG("test7");
	//delete t3;
	system("pause");/////hyumoi
	return 0;
}