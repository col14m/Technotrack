#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"
#include "../Include/D.h"
#include "../Include/Tex.h"
#include "../Include/ReadTree.h"
#include "../Include/WriteTree.h"
#include "../Include/Tex.h"

int main()
{
	typedef BinaryTreeNode Node;

	
	Node t1(NodeValue(NUMBER, 2)),t2 (NodeValue(OPERAND, "sin")), t3(NodeValue(VARIABLE, "x")),*t4 = new Node(NodeValue(VARIABLE, "x")), t5(NodeValue(NUMBER, 2));
	FILE* ptr = fopen("Write1.txt", "w");
	if (ptr == NULL)
		printf("HUY\n");
	//t2.InsertLeft(t4);
	//Node root(t2);
	//t2.InsertLeft(t3);
	//root = d(root);

	//printf("%d", atoi("-10"));
	Node* tree = ReadTree();
	tree->DumpToPNG("test9");
	DumpTexTree("THBS", *tree);
	system("pause");
	Node dTree = d(*tree);
	DumpTexTree("THBS-d", dTree);
	dTree.DumpToPNG("test8");
	system("pause");
	
	SimplyfyNode(&dTree);
	DumpTexTree("THBS-d-u", dTree);
	system("pause");
	//dTree.DumpToPNG("test9");
	WriteTree(tree, ptr);
	//delete t3;
	//DumpTexTree("test8_1", root);
	//SimplyfyNode(root);
	//DumpTexTree("test8_2", root);
	//(root).DumpToPNG("test8_2");
	fclose(ptr);
	//system("pause");
	return 0;
}