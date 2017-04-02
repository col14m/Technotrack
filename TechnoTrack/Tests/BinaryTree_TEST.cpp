#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)),t2 (NodeValue(OPERAND, "sin")), t3(NodeValue(VARIABLE, "x")),*t4 = new Node(NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	
	t2.InsertLeft(t4);
	Node root(t2);
	//t2.InsertLeft(t3);
	//root = d(root);


	d(root).DumpToPNG("test7");
	//delete t3;
	//DumpTexTree("test8_1", root);
	//SimplyfyNode(root);
	//DumpTexTree("test8_2", root);
	//(root).DumpToPNG("test8_2");
	system("pause");
	return 0;
}