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

struct AVLTree
{
	int data;
	int height;
	AVLTree* left;
	AVLTree* right;
};

class TreeAVLInterraction
{
	
public:

	TreeAVLInterraction();

	void printQuit();
	void printTree(AVLTree* node, int indent = 0);

	int getHeight(AVLTree* node);
	void calcHeight(AVLTree* node);
	int heightDiff(AVLTree* node);

	AVLTree* rotateRight(AVLTree* node);
	AVLTree* rotateLeft(AVLTree* node);

	AVLTree* balanceTree(AVLTree* node);

	AVLTree* insertNode(AVLTree* node, int value);
	AVLTree* deleteNode(AVLTree* node, int value);
	AVLTree* findMinNode(AVLTree* node);
};