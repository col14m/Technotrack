#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1 = *new Node (NodeValue(NUMBER, 2)), t2 = *new Node(NodeValue(NUMBER, 2 )), t3 = *new Node(NodeValue(VARIABLE, "x"));
	Node root(t2 * t1 * t2);
	//t2.InsertLeft(t3);
	//root = d(root);


	(root).DumpToPNG("test8_1");
	//delete t3;
	DumpTexTree("test8_1", root);
	SimplyfyNode(root);
	DumpTexTree("test8_2", root);
	(root).DumpToPNG("test8_2");
	system("pause");
	return 0;
}