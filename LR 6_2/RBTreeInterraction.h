#pragma once
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>

#include <list>
#include <queue>
#include <vector>

using namespace std;

enum class NodeColor { BLACK, RED };

struct RBTree
{
	int data;
	NodeColor color;
	RBTree* left;
	RBTree* right;
	RBTree* parent;
};

class RBTreeInterraction
{

public:

	RBTreeInterraction();

	void printQuit();
	void printTree(RBTree* node, int indent = 0);

	RBTree* createNode(int data);
	void insertNode(RBTree*& root, int data);
	void balanceTreeIns(RBTree*& root, RBTree* node);

	void leftRotate(RBTree*& root, RBTree* node);
	void rightRotate(RBTree*& root, RBTree* node);

	RBTree* minValueNode(RBTree* node);
	void deleteNode(RBTree*& root, int data);
	void balanceTreeDel(RBTree*& root, RBTree* node);
};