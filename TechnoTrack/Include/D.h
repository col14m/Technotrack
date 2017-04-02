#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"
#include <iostream>

#define R *tree.GetRightNode() 
#define L *tree.GetLeftNode()
#define C(what) *(new BinaryTreeNode(what))
#define VAL tree.GetValue().strData_

BinaryTreeNode& d(BinaryTreeNode& tree)
{
	NodeValue Val = tree.GetValue();
	if (Val.type_ == NUMBER)
	{
		Val.intData_ = 0;
		strcpy(VAL, "0");
		return tree;
	} 
	else if (Val.type_ == VARIABLE)
	{
		Val.type_ = NUMBER;
		Val.intData_ = 1;
		strcpy(VAL, "1");
		return tree;
	}
	else if (Val.type_ == OPERAND)
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
			BinaryTreeNode *NodeR = &C(R);
			tree.GetRightNode()->GetValue().intData_--;
			_itoa_s(tree.GetRightNode()->GetValue().intData_, tree.GetRightNode()->GetValue().strData_,  16, 10);
			return  ((tree * *NodeR) * d(C(L)));
		}
		else
		{

		}

	}
	else if (Val.type_ == ERRORS)
	{

	}
	else if (Val.type_ == EMPTY)
	{

	}

}

#undef R
#undef L
#undef C
#undef VAL
