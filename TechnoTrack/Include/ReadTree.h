#pragma once

#include "../Include/BinaryTree.h"
//char* buf = "( ( ( nil x nil ) * ( nil 1 nil ) ) + ( nil x nil ) )";
//char* buf = "( ( nil x nil ) + ( nil x nil ) )";
//char* buf = "( ( nil x nil ) * ( ( ( nil x nil ) - ( ( ( nil x nil ) + ( nil _sin ( nil x nil ) ) ) ^ ( nil 4 nil ) ) ) / ( ( nil x nil ) + ( nil _sin ( ( ( nil x nil ) ^ ( nil 5 nil ) ) + ( nil 4 nil ) ) ) ) ) )";
//char* buf = "( ( nil 1 nil ) / ( ( nil x nil ) + ( nil _sin ( ( ( nil x nil ) ^ ( nil 5 nil ) ) + ( nil 4 nil ) ) ) ) )";
//char* buf = "( ( nil x nil ) / ( ( nil x nil ) + ( nil 1 nil ) ) )";
char*  buf = "( ( nil x nil ) - ( ( ( nil x nil ) + ( nil _cos ( nil x nil ) ) ) ^ ( nil 4 nil ) ) )";
//char*  buf = "( ( nil x nil ) + ( ( nil x nil ) ^ ( nil -4 nil ) ) )";
//char*  buf = "( ( nil x nil ) - ( nil x nil ) )";
//typedef BinaryTreeNode Node;

BinaryTreeNode* ReadTree()
{
	if (!strncmp("nil", buf, 3))
	{
		buf += 4;
		return NULL;
	}
	
	if (*buf == '(')
	{
		BinaryTreeNode* tree = new BinaryTreeNode(NodeValue(EMPTY, 0));
		buf += 2;
		tree->InsertLeft(ReadTree());
		while (*buf == ')')
		{

			buf++;
			if (*buf == '\0')
				return NULL;
			buf++;
		}
		if (('0' <= *buf && *buf <= '9') || (*buf == '-' && ('0' <= *(buf + 1) && *(buf + 1) <= '9')))
		{
			tree->GetValue().type_ = NUMBER;
			int i = 0;
			while (*buf != ' ')
			{
				tree->GetValue().strData_[i] = *buf;
				i++;
				buf++;
			}
			tree->GetValue().strData_[i] = '\0';
			buf++;
			tree->GetValue().intData_ = atoi(tree->GetValue().strData_);
		}
		else if (*buf == 'x')
		{
			tree->GetValue().type_ = VARIABLE;
			tree->GetValue().strData_[0] = *buf;
			buf += 2;
		}
		else if (*buf == '+' || *buf == '-' || *buf == '*' || *buf == '/' || *buf == '^')
		{
			tree->GetValue().type_ = OPERAND;
			tree->GetValue().strData_[0] = *buf;
			buf += 2;
		}
		else if (!strncmp("_sin", buf, 4))
		{
			tree->GetValue().type_ = OPERAND;
			strcpy(tree->GetValue().strData_, "_sin");
			buf += 5;
		}
		else if (!strncmp("_cos", buf, 4))
		{
			tree->GetValue().type_ = OPERAND;
			strcpy(tree->GetValue().strData_, "_cos");
			buf += 5;
		}
		else
		{
			tree->GetValue().type_ = ERRORS;
		}
		
		tree->InsertRight(ReadTree());
		
		return tree;
	}
	
	return NULL;
}




