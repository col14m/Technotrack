#pragma once

#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

#include "NodeValue.h"

class BinaryTreeNode
{
public:
	BinaryTreeNode();
	BinaryTreeNode(const NodeValue &object);
	BinaryTreeNode(const BinaryTreeNode &node);
	~BinaryTreeNode();

	bool Ok() const;
	void Dump() const;
	void Dump(FILE *log) const;
	void DumpToPNG(char *logPNGname) const;

	BinaryTreeNode *GetLeftNode();
	BinaryTreeNode *GetRightNode();
	BinaryTreeNode *GetParentNode();
	NodeValue &GetValue()
	{
		return data_;
	}

	BinaryTreeNode *CutLeftNode();
	BinaryTreeNode *CutRightNode();

	void InsertLeft(BinaryTreeNode &leftBinaryTreeNode);
	void InsertLeft(BinaryTreeNode *leftBinaryTreeNode);
	void InsertRight(BinaryTreeNode &rightBinaryTreeNode);
	void InsertRight(BinaryTreeNode *rightBinaryTreeNode);

	bool HaveLeftChild() const;
	bool HaveRightChild() const;
	bool HaveChild() const;

private:
	BinaryTreeNode *leftNode_, *rightNode_, *parentNode_;
	NodeValue data_;
};
void ConvertVGtoPNG(char *logPNGname);


BinaryTreeNode::BinaryTreeNode() :
	leftNode_(NULL),
	rightNode_(NULL),
	parentNode_(NULL),
	data_(NodeValue())
{}

BinaryTreeNode::BinaryTreeNode(const NodeValue& object) :
	leftNode_(NULL),
	rightNode_(NULL),
	parentNode_(NULL),
	data_(NodeValue(object))
{}

BinaryTreeNode::BinaryTreeNode(const BinaryTreeNode &node)
{
	InsertLeft(node.HaveLeftChild() ? new BinaryTreeNode(*node.leftNode_) : NULL);
	InsertRight(node.HaveRightChild() ? new BinaryTreeNode(*node.rightNode_) : NULL);
	data_ = NodeValue(node.data_);
}

BinaryTreeNode::~BinaryTreeNode()
{
	delete leftNode_;
	leftNode_ = NULL;

	delete rightNode_;
	rightNode_ = NULL;
}

bool BinaryTreeNode::Ok() const
{
	return true;
}

void BinaryTreeNode::Dump() const
{
	printf("===========================================\n");
	printf("BinaryTreeNode_t (%s) [0x%p] :\n", Ok() ? "ok" : "ERROR", this);
	if (this != NULL)
	{
		printf("\t[0x%p] leftNode_\n", leftNode_);
		printf("\t[0x%p] rightNode_\n", rightNode_);
		printf("\t[0x%p] data_ : \n", &data_);
		data_.Dump();
	}
	printf("===========================================\n");

}

/*void BinaryTreeNode::Dump(FILE *log) const
{
	assert(log);

	fprintf(log, "\nBinaryTreeNode0x%p\n", this); 
	fprintf(log, "[label = \"BinaryTreeNode(%s) [0x%p]\n", Ok() ? "ok" : "ERROR", this);
	fprintf(log, "[0x%p] data_ : \n", &data_);
	data_.Dump(log);
	fprintf(log, "[0x%p] leftNode\n", leftNode_);
	fprintf(log, "[0x%p] rightNode\n", rightNode_);
	fprintf(log, "[0x%p] parentNode\n\"", parentNode_);
	fprintf(log, "%s];\n", Ok() ? "" : ", color = \"red\", fillcolor = \"#ff7d7d\"");

	fprintf(log, "BinaryTreeNode0x%p\n", this);
	
	if (HaveLeftChild())
	{
		fprintf(log, "BinaryTreeNode0x%p->BinaryTreeNode0x%p\n", this, leftNode_);
		leftNode_->Dump(log);
	}

	if (HaveRightChild())
	{
		fprintf(log, "BinaryTreeNode0x%p->BinaryTreeNode0x%p\n", this, rightNode_);
		rightNode_->Dump(log);
	}
}*/

void BinaryTreeNode::Dump(FILE *log) const
{
	assert(log);

	fprintf(log, "\nBinaryTreeNode0x%p\n", this);
	fprintf(log, "[label = \"BinaryTreeNode(%s) \n", Ok() ? "ok" : "ERROR");
	//fprintf(log, "[0x%p] data_ : \n", &data_);
	data_.Dump(log);
	//fprintf(log, "[0x%p] leftNode\n", leftNode_);
	fprintf(log, "\"", rightNode_);
	fprintf(log, "%s];\n", Ok() ? "" : ", color = \"red\", fillcolor = \"#ff7d7d\"");

	fprintf(log, "BinaryTreeNode0x%p\n", this);

	if (HaveLeftChild())
	{
		fprintf(log, "BinaryTreeNode0x%p->BinaryTreeNode0x%p\n", this, leftNode_);
		leftNode_->Dump(log);
	}

	if (HaveRightChild())
	{
		fprintf(log, "BinaryTreeNode0x%p->BinaryTreeNode0x%p\n", this, rightNode_);
		rightNode_->Dump(log);
	}
}

void BinaryTreeNode::DumpToPNG(char *logPNGname) const
{
	assert(logPNGname);

	FILE *log = NULL;

	char fullLogPNGname[40] = ".\\Logs\\BinaryTree\\";
	strcat_s(fullLogPNGname, 40, logPNGname);
	strcat_s(fullLogPNGname, 40, ".vg");

	fopen_s(&log, fullLogPNGname, "w");
	assert(log);

	fprintf(log, "digraph BinaryTreeNode {\n");
	fprintf(log, "node [color = \"green\", fontname = \"Calibri\", fontsize = 12, shape = \"rectangle\", style = \"filled\", fillcolor = \"#caff70\"]; \n");
	
	Dump(log);
	
	fprintf(log, "}\n");
	fclose(log);
	
	ConvertVGtoPNG(logPNGname);
}

bool BinaryTreeNode::HaveLeftChild() const
{
	return leftNode_ != NULL; //C4800, приведение к типу bool 
}

bool BinaryTreeNode::HaveRightChild() const
{
	return rightNode_ != NULL;
}

bool BinaryTreeNode::HaveChild() const
{
	return leftNode_ || rightNode_;
}


BinaryTreeNode *BinaryTreeNode::GetLeftNode()
{
	return leftNode_;
}

BinaryTreeNode *BinaryTreeNode::GetRightNode()
{
	return rightNode_;
}

BinaryTreeNode *BinaryTreeNode::GetParentNode()
{
	return parentNode_;
}

BinaryTreeNode *BinaryTreeNode::CutLeftNode()
{
	BinaryTreeNode *leftNode = leftNode_;
	leftNode_ = NULL;
	return leftNode;
}

BinaryTreeNode *BinaryTreeNode::CutRightNode()
{
	BinaryTreeNode *rightNode = rightNode_;
	rightNode_ = NULL;
	return rightNode;
}

void BinaryTreeNode::InsertLeft(BinaryTreeNode *leftBinaryTreeNode)
{
	assert(!leftNode_);
	if (leftBinaryTreeNode)
	{
		leftBinaryTreeNode->parentNode_ = this;
	}
	leftNode_ = leftBinaryTreeNode;
}

void BinaryTreeNode::InsertLeft(BinaryTreeNode &leftBinaryTreeNode)
{
	assert(!leftNode_);
	leftBinaryTreeNode.parentNode_ = this;
	leftNode_ = &leftBinaryTreeNode;
}

void BinaryTreeNode::InsertRight(BinaryTreeNode *rightBinaryTreeNode)
{
	assert(!rightNode_);
	if (rightBinaryTreeNode)
	{
		rightBinaryTreeNode->parentNode_ = this;
	}
	rightNode_ = rightBinaryTreeNode;
}

void BinaryTreeNode::InsertRight(BinaryTreeNode &rightBinaryTreeNode)
{
	assert(!rightNode_);
	rightBinaryTreeNode.parentNode_ = this;
	rightNode_ = &rightBinaryTreeNode;
}

void ConvertVGtoPNG(char *logPNGname)
{
	assert(logPNGname);

	FILE *nowBat = NULL;
	fopen_s(&nowBat, ".\\Logs\\BinaryTree\\toPNG.bat", "w");
	//printf("+++++++++++++\n");
	assert(nowBat);

	char fullInPNGname[40];
	strcpy_s(fullInPNGname, 40, logPNGname);
	strcat_s(fullInPNGname, 40, ".vg");

	char fullOutPNGname[40];
	strcpy_s(fullOutPNGname, 40, logPNGname);
	strcat_s(fullOutPNGname, 40, ".png");

	fprintf(nowBat, "E:\\Graphviz2.38\\bin\\dot ");
	fprintf(nowBat, "-Tpng \"%%CD%%\\Logs\\BinaryTree\\%s\" ", fullInPNGname);
	fprintf(nowBat, "   -o \"%%CD%%\\Logs\\BinaryTree\\%s\" \n", fullOutPNGname);

	fclose(nowBat);
	//printf("++++++----------------+++++++\n");
	WinExec(".\\Logs\\BinaryTree\\toPNG.bat", SW_HIDE);
	//system("cls");
}

BinaryTreeNode &operator+(BinaryTreeNode &A, BinaryTreeNode &B)
{
	NodeValue sum(OPERAND, "+");
	BinaryTreeNode *nowNode = new BinaryTreeNode(sum);

	nowNode->InsertLeft(A);
	nowNode->InsertRight(B);

	return *nowNode;
}

BinaryTreeNode &operator-(BinaryTreeNode &A, BinaryTreeNode &B)
{
	NodeValue sum(OPERAND, "-");
	BinaryTreeNode *nowNode = new BinaryTreeNode(sum);

	nowNode->InsertLeft(A);
	nowNode->InsertRight(B);

	return *nowNode;
}

BinaryTreeNode &operator*(BinaryTreeNode &A, BinaryTreeNode &B)
{
	NodeValue sum(OPERAND, "*");
	BinaryTreeNode *nowNode = new BinaryTreeNode(sum);

	nowNode->InsertLeft(A);
	nowNode->InsertRight(B);

	return *nowNode;
}

BinaryTreeNode &operator/(BinaryTreeNode &A, BinaryTreeNode &B)
{
	NodeValue sum(OPERAND, "/");
	BinaryTreeNode *nowNode = new BinaryTreeNode(sum);

	nowNode->InsertLeft(A);
	nowNode->InsertRight(B);

	return *nowNode;
}

BinaryTreeNode &operator^(BinaryTreeNode &A, BinaryTreeNode &B)
{
	NodeValue deg(OPERAND, "^");
	BinaryTreeNode *nowNode = new BinaryTreeNode(deg);

	nowNode->InsertLeft(A);
	nowNode->InsertRight(B);

	return *nowNode;
}