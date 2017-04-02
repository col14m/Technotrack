#pragma once

#include "BinaryTree.h"
#include "NodeValue.h"

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

bool DumpTexNode(BinaryTreeNode *node, FILE *log)
{
	bool check = true;
	fprintf(log, "( ");
	
	if (node->HaveLeftChild())
		check &= DumpTexNode(node->GetLeftNode(), log);

	fprintf(log, " %s ", node->GetValue().strData_);

	if (node->HaveRightChild())
		check &= DumpTexNode(node->GetRightNode(), log);

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

	fprintf(nowBat, "C:\\MiKTeX2.9\\miktex\\bin\\x64\\pdflatex.exe ");
	fprintf(nowBat, "\"%%CD%%\\Logs\\BinaryTree\\%s\" ", logTEXname);

	fclose(nowBat);

	WinExec(".\\Logs\\BinaryTree\\toTEX.bat", SW_HIDE);
	system("cls");

	return check;
}





bool SimplyfyNode(BinaryTreeNode &node)
{
	bool check = true;
	if (node.HaveLeftChild())
		check &= SimplyfyNode(*(node.GetLeftNode()));
	if (node.HaveRightChild())
		check &= SimplyfyNode(*(node.GetRightNode()));
	
	// + 0 or 0 + 
	if (IS_L_OPER("+") && IS_L_L_DATA(0))
		node.InsertLeft(node.GetLeftNode()->GetRightNode());
	if (IS_L_OPER("+") && IS_L_R_DATA(0))
		node.InsertLeft(node.GetLeftNode()->GetLeftNode());
	if (IS_R_OPER("+") && IS_R_L_DATA(0))
		node.InsertLeft(node.GetRightNode()->GetRightNode());
	if (IS_R_OPER("+") && IS_R_R_DATA(0))
		node.InsertLeft(node.GetRightNode()->GetLeftNode());

	return true;


}