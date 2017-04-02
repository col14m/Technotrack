#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)), t2(NodeValue(NUMBER, 2 )), t3 (NodeValue(VARIABLE, "x"));
	
	Node root(t2 * t1);
	//t2.InsertLeft(t3);
	//root = d(root);


	(root).DumpToPNG("test8");
	//delete t3;
	DumpTexTree("test8_1", root);


	system("pause");
	return 0;
}