#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "../Include/BinaryTree.h"


int main()
{
	typedef BinaryTreeNode Node;////////

	
	Node t1(NodeValue(NUMBER, 5)), t2(NodeValue(NUMBER, 10)), t3(NodeValue(NUMBER, 2));
	
	Node root(t1*t2 + t3*(t2 + t1)/t3);
	
	root.DumpToPNG("test6");
	
	system("pause");
	return 0;
}