#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"
#include "../Include/ReadTree.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)),t2 (NodeValue(OPERAND, "sin")), t3(NodeValue(VARIABLE, "x")),*t4 = new Node(NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	
	t2.InsertLeft(t4);
	//Node root(t2);
	//t2.InsertLeft(t3);
	//root = d(root);
	BinaryTreeNode *root = ReadTree();
	//printf("%d", atoi("-10"));
	//root->DumpToPNG("test10_1");
	DumpTexTree("test10_1", *root);
	SimplyfyNode(root);
	root->DumpToPNG("test10_2");
	DumpTexTree("test10_2", *root);
	//delete t3;
	//DumpTexTree("test8_1", root);
	
	//DumpTexTree("test8_2", root);
	//(root).DumpToPNG("test8_2");
	system("pause");
	return 0;
}