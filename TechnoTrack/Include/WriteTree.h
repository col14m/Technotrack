
#include "BinaryTree.h"
#include <stdio.h>

typedef BinaryTreeNode Node;

int WriteTree(Node *Tree, FILE *File)
{
	assert(Tree);
	assert(File);
	fprintf(File, "( ");
	if (Tree->HaveLeftChild())
	{
		//Tree->DumpToPNG("test8");
		WriteTree(Tree->GetLeftNode(), File);
	}
	else
		fprintf(File, "nil ");
	fprintf(File, "%s ", Tree->GetValue().strData_);
	if (Tree->HaveRightChild())
	{
		//Tree->DumpToPNG("test8");
		WriteTree(Tree->GetRightNode(), File);
	}
	else
		fprintf(File, "nil ");
	fprintf(File, ") ");
	return 0;

}