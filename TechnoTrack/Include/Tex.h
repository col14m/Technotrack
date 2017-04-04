#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"

#define IS_OPER(oper) (IS_TYPE( OPERAND ) && !strcmp(node->GetValue().strData_, oper) )
#define IS_TYPE(t) (node->GetValue().type_ == t)
#define L_VAL (node->GetLeftNode()->GetValue())
#define R_VAL (node->GetRightNode()->GetValue())
#define IS_L_NUM(data) (L_VAL.type_ == NUMBER && L_VAL.intData_ == data )
#define IS_R_NUM(data) (R_VAL.type_ == NUMBER && R_VAL.intData_ == data )
//#define COUNT(oper) /
		

/*
#define ISN_L_NULL ( node.GetLeftNode()!=NULL && node.GetLeftNode()->GetLeftNode() != NULL \
					&& node.GetLeftNode()->GetRightNode() != NULL )
#define ISN_R_NULL ( node.GetRightNode()!=NULL && node.GetRightNode()->GetLeftNode() != NULL \
					&& node.GetRightNode()->GetRightNode() != NULL)



#define L_L_VAL (node.GetLeftNode()->GetLeftNode()->GetValue())
#define L_R_VAL (node.GetLeftNode()->GetRightNode()->GetValue())
#define R_L_VAL (node.GetRightNode()->GetLeftNode()->GetValue())
#define R_R_VAL (node.GetRightNode()->GetRightNode()->GetValue())
#define IS_L_OPER(oper) (L_VAL.type_ == OPERAND && \
						!strcmp(L_VAL.strData_, oper))
#define IS_R_OPER(oper) (R_VAl.type_ == OPERAND && \
						!strcmp(R_VAl.strData_, oper))
#define IS_L_L_DATA(data) (L_L_VAL.type_ == NUMBER && \
						   L_L_VAL.intData_ == (data))
#define IS_L_R_DATA(data) (L_R_VAL.type_ == NUMBER && \
						   L_R_VAL.intData_ == (data))
#define IS_R_L_DATA(data) (R_L_VAL.type_ == NUMBER && \
						   R_L_VAL.intData_ == (data))
#define IS_R_R_DATA(data) (R_R_VAL.type_ == NUMBER && \
						   R_R_VAL.intData_ == (data))
#define PROCESSING( oper, data ) \
	if (ISN_L_NULL && IS_L_OPER((oper)) && IS_L_L_DATA(data)) \
		{delete node.GetLeftNode(); node.InsertLeft(node.GetLeftNode()->GetRightNode()); }\
	if (ISN_L_NULL && IS_L_OPER((oper)) && IS_L_R_DATA(data)) \
		{delete node.GetLeftNode(); node.InsertLeft(node.GetLeftNode()->GetLeftNode()); }\
	if (ISN_R_NULL && IS_R_OPER((oper)) && IS_R_L_DATA(data)) \
		{delete node.GetRightNode();node.InsertRight(node.GetRightNode()->GetRightNode()); }\
	if (ISN_R_NULL && IS_R_OPER((oper)) && IS_R_R_DATA(data)) \
		{delete node.GetRightNode(); node.InsertRight(node.GetRightNode()->GetLeftNode()); }
#define COUNT( oper ) \
	if (ISN_L_NULL && L_L_VAL.type_ == NUMBER && L_R_VAL.type_ == NUMBER) \
		{delete node.GetLeftNode(); node.InsertLeft(new BinaryTreeNode( *(new NodeValue(NUMBER, (int) (L_L_VAL.intData_ oper L_R_VAL.intData_))))); }\
	if (ISN_R_NULL && R_L_VAL.type_ == NUMBER && R_R_VAL.type_ == NUMBER) \
		{delete node.GetRightNode(); node.InsertRight(new BinaryTreeNode( *(new NodeValue(NUMBER, (int) (R_L_VAL.intData_ oper R_R_VAL.intData_))))); }
*/

bool DumpTexNode(BinaryTreeNode *node, FILE *log)
{
	bool check = true;
	if (IS_OPER("\\"))
		fprintf(log, "frac{");
	else if (IS_OPER("*"))
		;
	else if (!(IS_TYPE(NUMBER) || IS_TYPE(VARIABLE) ))
		fprintf(log, "( ");
	
	if (node->HaveLeftChild())
		check &= DumpTexNode(node->GetLeftNode(), log);
	if (IS_OPER("\\"))
		fprintf(log, "}{");
	else
		fprintf(log, " %s ", node->GetValue().strData_);

	if (node->HaveRightChild())
		check &= DumpTexNode(node->GetRightNode(), log);
	if (IS_OPER("\\"))
		fprintf(log, "}");
	else if (IS_OPER("*"))
		;
	else if (!(IS_TYPE(NUMBER) || IS_TYPE(VARIABLE)))
		fprintf(log, " )");

	return check;
}

bool DumpTexTree(const char *logTEXname, BinaryTreeNode &node)
{
	assert(logTEXname);

	FILE *log = NULL;
	bool check = false;

	char fullLogTEXname[40] = ".\\Logs\\BinaryTree\\";
	strcat_s(fullLogTEXname, 40, logTEXname);
	strcat_s(fullLogTEXname, 40, ".tex");
	
	fopen_s(&log, fullLogTEXname, "w");
	assert(log);

	fprintf(log, "\\documentclass{proc}\n"
				 "\\begin{document}\n"
				 "$ ");

	check = DumpTexNode(&node, log);

	fprintf(log, " $\n"
				 "\\end{document}");
	fclose(log);

	FILE *nowBat = NULL;
	fopen_s(&nowBat, ".\\Logs\\BinaryTree\\toTEX.bat", "w");
	assert(nowBat);
	fprintf(nowBat, "cd \"%%CD%%\\Logs\\BinaryTree\\\n "
					"C:\\\"MiKTeX 2.9\"\\miktex\\bin\\x64\\pdflatex.exe ");
	fprintf(nowBat, "%s.tex\" ", logTEXname);

	fclose(nowBat);

	WinExec(".\\Logs\\BinaryTree\\toTEX.bat", SW_HIDE);
	system("cls");

	return check;
}

bool ProcessingNode(BinaryTreeNode *node, int num, char* oper, char side)
{

	if (IS_OPER(oper) && IS_L_NUM(num) && side == 'L')
	{
		BinaryTreeNode *tmpNodeA = node->CutRightNode();
		if (node == node->GetParentNode()->GetLeftNode())
		{
			BinaryTreeNode *tmpNodeB = node->GetParentNode()->CutLeftNode();
			node->GetParentNode()->InsertLeft(tmpNodeA);
			delete tmpNodeB;
		}
		else if (node == node->GetParentNode()->GetRightNode())
		{
			BinaryTreeNode *tmpNodeB = node->GetParentNode()->CutRightNode();
			node->GetParentNode()->InsertRight(tmpNodeA);
			delete tmpNodeB;
		}
	}
	else if (IS_OPER(oper) && IS_R_NUM(num) && side == 'R')
	{
		BinaryTreeNode *tmpNode = node->CutLeftNode();
		if (node == node->GetParentNode()->GetLeftNode())
		{
			delete node->GetParentNode()->CutLeftNode();
			node->GetParentNode()->InsertLeft(tmpNode);
		}
		else if (node == node->GetParentNode()->GetRightNode())
		{
			delete node->GetParentNode()->CutRightNode();
			node->GetParentNode()->InsertRight(tmpNode);
		}
	}
	else
		//assert(0);
	return true;
}

bool SimplyfyNode(BinaryTreeNode *node)
{
	assert(node);
	bool check = true;
	if (node->HaveLeftChild())
		check = SimplyfyNode((node->GetLeftNode()));
	if (node->HaveRightChild())
		check = SimplyfyNode((node->GetRightNode()));

	if (node->HaveLeftChild() && node->HaveRightChild() && L_VAL.type_ == NUMBER && R_VAL.type_ == NUMBER && 
		node->GetParentNode() )
	{
		BinaryTreeNode *nodeParent = node->GetParentNode();
		BinaryTreeNode *newNode = NULL;
		if (IS_OPER("+"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, L_VAL.intData_ + R_VAL.intData_)));
		}
		else if (IS_OPER("-"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, L_VAL.intData_ - R_VAL.intData_)));
		}
		else if (IS_OPER("*"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, L_VAL.intData_ * R_VAL.intData_)));
		}
		else if (IS_OPER("-"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, L_VAL.intData_ - R_VAL.intData_)));
		}
		else if (IS_OPER("//"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, L_VAL.intData_ / R_VAL.intData_)));
		}
		else if (IS_OPER("^"))
		{
			newNode = new BinaryTreeNode(NodeValue(NodeValue(NUMBER, pow(L_VAL.intData_, R_VAL.intData_))));
		}
		if (node == node->GetParentNode()->GetLeftNode())
		{
			delete nodeParent->CutLeftNode();
			nodeParent->InsertLeft(newNode);
		}
		else if (node == node->GetParentNode()->GetRightNode())
		{
			delete nodeParent->CutLeftNode();
			nodeParent->InsertRight(newNode);
		}
	}
	ProcessingNode(node, 0, "+", 'L');
	ProcessingNode(node, 0, "+", 'R');
	ProcessingNode(node, 1, "*", 'L');
	ProcessingNode(node, 1, "*", 'R');
	ProcessingNode(node, 0, "-", 'L');
	ProcessingNode(node, 0, "-", 'R');
	ProcessingNode(node, 1, "^", 'R');
	ProcessingNode(node, 1, "//", 'R');

	if (IS_OPER("*") && IS_R_NUM(0))
	{
		BinaryTreeNode *tmpNodeA = node->CutRightNode();
		if (node == node->GetParentNode()->GetLeftNode())
		{
			BinaryTreeNode *tmpNodeB = node->GetParentNode()->CutLeftNode();
			node->GetParentNode()->InsertLeft(tmpNodeA);
			delete tmpNodeB;
		}
		else if (node == node->GetParentNode()->GetRightNode())
		{
			BinaryTreeNode *tmpNodeB = node->GetParentNode()->CutRightNode();
			node->GetParentNode()->InsertRight(tmpNodeA);
			delete tmpNodeB;
		}
	}
	else if (IS_OPER("*") && IS_L_NUM(0))
	{
		BinaryTreeNode *tmpNode = node->CutLeftNode();
		if (node == node->GetParentNode()->GetLeftNode())
		{
			delete node->GetParentNode()->CutLeftNode();
			node->GetParentNode()->InsertLeft(tmpNode);
		}
		else if (node == node->GetParentNode()->GetRightNode())
		{
			delete node->GetParentNode()->CutRightNode();
			node->GetParentNode()->InsertRight(tmpNode);
		}
	}
	return check;
}

/*
bool SimplyfyNode(BinaryTreeNode &node)
{
	bool check = true;
	if (node.HaveLeftChild())
		check = SimplyfyNode(*(node.GetLeftNode()));
	if (node.HaveRightChild())
		check = SimplyfyNode(*(node.GetRightNode()));
	
	// + 0 or 0 + 
	/*
	if (IS_L_OPER("+") && IS_L_L_DATA(0))
		node.InsertLeft(node.GetLeftNode()->GetRightNode());
	if (IS_L_OPER("+") && IS_L_R_DATA(0))
		node.InsertLeft(node.GetLeftNode()->GetLeftNode());
	if (IS_R_OPER("+") && IS_R_L_DATA(0))
		node.InsertLeft(node.GetRightNode()->GetRightNode());
	if (IS_R_OPER("+") && IS_R_R_DATA(0))
		node.InsertLeft(node.GetRightNode()->GetLeftNode());
	

	if ( ISN_L_NULL || ISN_R_NULL )
	{
		COUNT(+)
		COUNT(*)
		COUNT(/)
		COUNT(-)
		PROCESSING("+", 0)
		PROCESSING("-", 0)
		PROCESSING("*", 1)
		PROCESSING("*", 1)

			//if (L_L_VAL.type_ == NUMBER && L_R_VAL.type_ == NUMBER)
				//node.InsertLeft(new BinaryTreeNode(*(new NodeValue(NUMBER, L_L_VAL.intData_ + L_R_VAL.intData_))));
				//if (R_L_VAL.type_ == NUMBER && R_R_VAL.type_ == NUMBER) \
					node.InsertLeft(new BinaryTreeNode( (new NodeValue(NUMBER, R_L_VAL.intData_ oper R_R_VAL.intData_))));
		// PROCESSING( "/", 1 )
		if (IS_R_OPER("/") && IS_R_R_DATA(1)) \
				node.InsertLeft(node.GetRightNode()->GetLeftNode());
		if (IS_L_OPER("/") && IS_L_R_DATA(1)) \
			node.InsertLeft(node.GetLeftNode()->GetLeftNode());
		//PROCESSING( "^", 1)
		if (IS_R_OPER("^") && IS_R_R_DATA(1)) \
			node.InsertLeft(node.GetRightNode()->GetLeftNode());
		if (IS_L_OPER("^") && IS_L_R_DATA(1)) \
			node.InsertLeft(node.GetLeftNode()->GetLeftNode());
		//PROCESSINR( 
		if (IS_L_OPER(("*")) && IS_L_L_DATA(0))
			node.InsertLeft(node.GetLeftNode()->GetLeftNode());
		if (IS_L_OPER("*") && IS_L_R_DATA(0))
			node.InsertLeft(node.GetLeftNode()->GetRightNode());
		if (IS_R_OPER("*") && IS_R_L_DATA(0))
			node.InsertLeft(node.GetRightNode()->GetLeftNode());
		if (IS_R_OPER("*") && IS_R_R_DATA(0))
			node.InsertLeft(node.GetRightNode()->GetRightNode());
	}
	return check;
}
*/
