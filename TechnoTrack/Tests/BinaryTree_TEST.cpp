#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)),*t2 = new Node(NodeValue(OPERAND, "sin")), t3 (NodeValue(VARIABLE, "x")), *t4 = new Node (NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	Node *n1 = new Node(NodeValue(OPERAND, "*"));
	Node *n2 = new Node(NodeValue(OPERAND, "+"));
	n2->InsertLeft(new Node(NodeValue(NUMBER, 0)));
	n2->InsertRight(new Node(NodeValue(NUMBER, 7)));
	n1->InsertRight(t5);
	n1->InsertLeft(n2);
	t2->InsertRight(t4);
	n1->DumpToPNG("test10_1");
	DumpTexTree("test10_1", *n1);
	SimplyfyNode(n1);
	n1->DumpToPNG("test10_2");
	DumpTexTree("test10_2", *n1);
	//Node root(t2);
	//t2.InsertLeft(t3);
	//root = d(root);


	//d(*t2).DumpToPNG("test9");
	//delete t3;
	//t2->DumpToPNG("test10");
	//DumpTexTree("test10", *t2 );
	//SimplyfyNode(root);
	//DumpTexTree("test8_2", root);
	//(root).DumpToPNG("test8_2");
	system("pause");
	return 0;
}