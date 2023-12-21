#include "TreeAVLInterraction.h"

TreeAVLInterraction::TreeAVLInterraction()
{

}

void TreeAVLInterraction::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

void TreeAVLInterraction::printTree(AVLTree* node, int indent)
{
	if (node == nullptr)
	{
		return;
	}

	printTree(node->right, indent + 8);

	for (int i = 0; i < indent; i++)
	{
		cout << " ";
	}
	cout << node->data << endl;

	printTree(node->left, indent + 8);
}

int TreeAVLInterraction::getHeight(AVLTree* node)
{
	return (node != nullptr) ? node->height : 0;
}

void TreeAVLInterraction::calcHeight(AVLTree* node)
{
	int leftH = getHeight(node->left);
	int rightH = getHeight(node->right);
	node->height = max(leftH, rightH) + 1;
}

int TreeAVLInterraction::heightDiff(AVLTree* node)
{
	return (node != nullptr) ? getHeight(node->right) - getHeight(node->left) : 0;
}

AVLTree* TreeAVLInterraction::rotateRight(AVLTree* node)
{
	AVLTree* leftNode = node->left;
	node->left = leftNode->right;
	leftNode->right = node;
	calcHeight(node);
	calcHeight(leftNode);

	return leftNode;
}

AVLTree* TreeAVLInterraction::rotateLeft(AVLTree* node)
{
	AVLTree* right = node->right;
	node->right = right->left;
	right->left = node;	
	calcHeight(node);
	calcHeight(right);

	return right;
}

AVLTree* TreeAVLInterraction::balanceTree(AVLTree* node)
{
	calcHeight(node);
	int heightD = heightDiff(node);

	if (heightD > 1)
	{
		if (heightDiff(node->right) < 0)
		{
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}

	if (heightD < -1)
	{
		if (heightDiff(node->left) > 0)
		{
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}

	return node;
}

AVLTree* TreeAVLInterraction::insertNode(AVLTree* node, int value)
{
	if (node == nullptr)
	{
		AVLTree* temp = new AVLTree;
		temp->data = value;
		temp->left = temp->right = nullptr;
		temp->height = 1;

		return temp;
	}

	if (value < node->data)
	{
		node->left = insertNode(node->left, value);
	}
	else if (value > node->data)
	{
		node->right = insertNode(node->right, value);
	}
	else
	{
		return node;
	}

	return balanceTree(node);
}

AVLTree* TreeAVLInterraction::deleteNode(AVLTree* node, int value)
{
	if (node == nullptr) return nullptr;

	if (value < node->data)
	{
		node->left = deleteNode(node->left, value);
	}
	else if (value > node->data)
	{
		node->right = deleteNode(node->right, value);
	}
	else
	{
		if (node->left == nullptr || node->right == nullptr)
		{
			AVLTree* temp = node->left ? node->left : node->right;

			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
			{
				*node = *temp;
			}

			delete temp;
		}
		else
		{
			AVLTree* temp = findMinNode(node->right);
			node->data = temp->data;
			node->right = deleteNode(node->right, temp->data);
		}
	}

	if (node == nullptr) return nullptr;

	return balanceTree(node);
}

AVLTree* TreeAVLInterraction::findMinNode(AVLTree* node)
{
	if (node == nullptr) return nullptr;

	while (node->left != nullptr)
	{
		node = node->left;
	}
	return node;
}