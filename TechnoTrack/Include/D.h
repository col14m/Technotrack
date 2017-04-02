#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"

#define R *tree.GetRightNode() 
#define L *tree.GetLeftNode()
#define C(what) *(new BinaryTreeNode(what))
#define VAL tree.GetValue().strData_

BinaryTreeNode& d(BinaryTreeNode& tree)
{
	if (tree.GetValue().type_ == NUMBER)
	{
		tree.GetValue().intData_ = 0;
		strcpy(VAL, "0");
		//tree.GetValue().strData_[0] = '0';
		//tree.GetValue().strData_[1] = '\0';
		return tree;
	} 
	else if (tree.GetValue().type_ == VARIABLE)
	{
		tree.GetValue().type_ = NUMBER;
		tree.GetValue().intData_ = 1;
		strcpy(VAL, "1");
		//tree.GetValue().strData_[0] = '1';
		//tree.GetValue().strData_[1] = '\0';
		return tree;
	}
	else if (tree.GetValue().type_ == OPERAND)
	{
		if (VAL[0] == '+')
			return d(L) + d(R);
		else if (VAL[0] == '-')
			return d(L) - d(R);
		else if (VAL[0] == '*')
			return d(C(L)) * C(R) + L * d(R);
		else if (VAL[0] == '/')
			return (d(C(L)) * C(R) - L * d(R)) / (C(R) * C(R));
		else if (!strcmp(VAL, "sin"))
		{
			strcpy(VAL, "cos");
			return tree * d(C(L));
		}
		else if (VAL[0] == '^')
		{
			BinaryTreeNode *Tmp = &C(R);
			tree.GetRightNode()->GetValue().intData_--;
			return  ((tree * *Tmp) * d(C(L)));
		}
			


	}

}

#undef R
#undef L
#undef C
#undef VAL
