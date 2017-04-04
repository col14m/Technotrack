#pragma once

#include "../Include/BinaryTree.h"
char* buf = "( ( nil nil nil ) _sin ( nil x nil ) )";
typedef BinaryTreeNode Node;

Node* ReadTree()
{
	if (*buf == '\0')
		return NULL;
	if (!strncmp("nil", buf, 3))
	{
		buf += 4;
		return NULL;
		printf("%s\n", buf);
	}
	
	if (*buf == '(')
	{
		Node* tree = new Node(NodeValue(EMPTY, 0));
		buf += 2;
		printf("%s\n", buf);
		tree->InsertLeft(ReadTree());
		while (*buf == ')')
		{

			buf++;
			printf("%s\n", buf);
			if (*buf == '\0')
				return NULL;
			buf++;
			printf("%s\n", buf);
		}
		if (('0' <= *buf && *buf <= '9') || *buf == '-')
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
			printf("%s\n", buf);
			tree->GetValue().intData_ = atoi(tree->GetValue().strData_);
		}
		else if (*buf == 'x')
		{
			tree->GetValue().type_ = VARIABLE;
			tree->GetValue().strData_[0] = *buf;
			buf++;
			buf++;
			printf("%s\n", buf);
		}
		else if (*buf == '+' || *buf == '-' || *buf == '*' || *buf == '/' || *buf == '^')
		{
			tree->GetValue().type_ = OPERAND;
			tree->GetValue().strData_[0] = *buf;
			buf++;
			buf++;
			printf("%s\n", buf);
		}
		else if (*buf == '_')
		{
			tree->GetValue().type_ = OPERAND;
			strcpy(tree->GetValue().strData_, "sin");
			buf += 5;
			printf("%s\n", buf);
		}
		else if (!strncmp("nil", buf, 3))
		{
			buf += 8;
			strcpy(tree->GetValue().strData_, "nil");
			printf("%s\n", buf);
			delete tree;
			tree = NULL;
			return NULL;
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


