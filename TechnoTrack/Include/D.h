#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"


BinaryTreeNode& d(BinaryTreeNode& tree)
{
	if (tree.GetValue().type_ == NUMBER)
	{
		tree.GetValue().intData_ = 0;
		tree.GetValue().strData_[0] = '0';
		tree.GetValue().strData_[1] = '\0';
		return tree;
	} 
	else if (tree.GetValue().type_ == VARIABLE)
	{
		tree.GetValue().type_ = NUMBER;
		tree.GetValue().intData_ = 1;
		tree.GetValue().strData_[0] = '1';
		tree.GetValue().strData_[1] = '\0';
		return tree;
	}

}

