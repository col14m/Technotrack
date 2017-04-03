#pragma once

#include "../Include/BinaryTree.h"
char* buf = "( ( ( nil x nil ) - ( ( nil x nil ) ^ ( nil 4 nil ) ) ) / ( ( nil x nil ) + ( nil 7 nil ) ) )";
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
		//buf += 2;
		while (*buf == ')')
		{

			buf++;
			printf("%s\n", buf);
			if (*buf == '\0')
				return NULL;
			buf++;
			printf("%s\n", buf);
			//return tree;
		}
		if ('0' <= *buf && *buf <= '9')
		{
			tree->GetValue().type_ = NUMBER;
			int i = 0;
			while (*buf != ' ')
			{
				tree->GetValue().strData_[i] = *buf;
				i++;
				buf++;
				assert(*buf == ' ');
			}
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
		

		else
		{
			tree->GetValue().type_ = ERRORS;
		}
		
		tree->InsertRight(ReadTree());
		//buf++;
		//buf++;
		return tree;
		
	}
	
	return NULL;
}


