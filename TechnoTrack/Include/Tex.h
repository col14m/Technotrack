#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"

#define IS_TYPE(t) (node->GetValue().type_ == t)
#define IS_OPER(oper) (IS_TYPE( OPERAND ) && !strcmp(node->GetValue().strData_, oper))
#define L_VAL (node.GetLeftNode()->GetValue())
#define R_VAl (node.GetRightNode()->GetValue())
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
	if (IS_L_OPER((oper)) && IS_L_L_DATA(data)) \
		node.InsertLeft(node.GetLeftNode()->GetRightNode()); \
	if (IS_L_OPER((oper)) && IS_L_R_DATA(data)) \
		node.InsertLeft(node.GetLeftNode()->GetLeftNode()); \
	if (IS_R_OPER((oper)) && IS_R_L_DATA(data)) \
		node.InsertLeft(node.GetRightNode()->GetRightNode()); \
	if (IS_R_OPER((oper)) && IS_R_R_DATA(data)) \
		node.InsertLeft(node.GetRightNode()->GetLeftNode());
#define COUNT( oper ) \
	if (L_L_VAL.type_ == NUMBER && L_R_VAL.type_ == NUMBER) \
		node.InsertLeft(new BinaryTreeNode( *(new NodeValue(NUMBER, (int) (L_L_VAL.intData_ oper L_R_VAL.intData_))))); \
	if (R_L_VAL.type_ == NUMBER && R_R_VAL.type_ == NUMBER) \
		node.InsertLeft(new BinaryTreeNode( *(new NodeValue(NUMBER, (int) (R_L_VAL.intData_ oper R_R_VAL.intData_)))));

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
	*/

	if (node.GetLeftNode()!= NULL && node.GetRightNode()!= NULL 
		&& (node.GetLeftNode()->GetLeftNode()!= NULL &&node.GetLeftNode()->GetRightNode() != NULL
		|| node.GetRightNode()->GetRightNode() != NULL &&node.GetRightNode()->GetRightNode() != NULL))
	{
		//COUNT(+)
		//COUNT(*)
		//COUNT(/)
		//COUNT(-)
		if (L_L_VAL.type_ == NUMBER)
			printf("wdqwwdwd============================================\n");
		if (L_R_VAL.type_ == NUMBER)
			printf("wdqwwdwd===============================\n");
		if (R_L_VAL.type_ == NUMBER)
			printf("wdqwwdwd====================================\n");
		if (R_R_VAL.type_ == NUMBER)
			printf("wdqwwdwd================================================\n");
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