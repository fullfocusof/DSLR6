#include "RBTreeInterraction.h"

RBTreeInterraction::RBTreeInterraction()
{

}

void RBTreeInterraction::printQuit()
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

void RBTreeInterraction::printTree(RBTree* node, int indent)
{
	if (node != nullptr)
	{
		printTree(node->right, indent + 8);

		for (int i = 0; i < indent; i++)
			cout << " ";

		cout << node->data << "(" << (node->color == NodeColor::RED ? "Red" : "Black") << ")" << endl;

		printTree(node->left, indent + 8);
	}
}

RBTree* RBTreeInterraction::createNode(int data)
{
	RBTree* newNode = new RBTree();
	newNode->data = data;
	newNode->color = NodeColor::RED;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->parent = nullptr;

	return newNode;
}

void RBTreeInterraction::insertNode(RBTree*& root, int data)
{
	RBTree* newNode = createNode(data);
	RBTree* current = root;
	RBTree* parent = nullptr;

	while (current != nullptr)
	{
		parent = current;
		if (data < current->data)
			current = current->left;
		else
			current = current->right;
	}

	newNode->parent = parent;

	if (parent == nullptr)
	{
		root = newNode;
		root->color = NodeColor::BLACK;
	}
	else if (data < parent->data)
		parent->left = newNode;
	else
		parent->right = newNode;

	balanceTreeIns(root, newNode);
}

void RBTreeInterraction::balanceTreeIns(RBTree*& root, RBTree* node)
{
	while (node->parent != nullptr && node->parent->color == NodeColor::RED)
	{
		RBTree* parent = node->parent;
		RBTree* grandparent = parent->parent;

		if (parent == grandparent->left)
		{
			RBTree* uncle = grandparent->right;

			// Case 1: Uncle is also red - Recoloring
			if (uncle != nullptr && uncle->color == NodeColor::RED)
			{
				parent->color = NodeColor::BLACK;
				uncle->color = NodeColor::BLACK;
				grandparent->color = NodeColor::RED;
				node = grandparent;
			}
			else
			{
				// Case 2: Node is right child of parent - Left rotation
				if (node == parent->right)
				{
					leftRotate(root, parent);
					node = parent;
					parent = node->parent;
				}

				// Case 3: Node is left child of parent - Right rotation
				rightRotate(root, grandparent);
				std::swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		else
		{
			RBTree* uncle = grandparent->left;

			// Case 1: Uncle is also red - Recoloring
			if (uncle != nullptr && uncle->color == NodeColor::RED)
			{
				parent->color = NodeColor::BLACK;
				uncle->color = NodeColor::BLACK;
				grandparent->color = NodeColor::RED;
				node = grandparent;
			}
			else
			{
				// Case 2: Node is left child of parent - Right rotation
				if (node == parent->left)
				{
					rightRotate(root, parent);
					node = parent;
					parent = node->parent;
				}

				// Case 3: Node is right child of parent - Left rotation
				leftRotate(root, grandparent);
				std::swap(parent->color, grandparent->color);
				node = parent;
			}
		}
	}

	root->color = NodeColor::BLACK;
}

void RBTreeInterraction::leftRotate(RBTree*& root, RBTree* node)
{
	RBTree* rightChild = node->right;
	node->right = rightChild->left;

	if (node->right != nullptr)
		node->right->parent = node;

	rightChild->parent = node->parent;

	if (node->parent == nullptr)
		root = rightChild;
	else if (node == node->parent->left)
		node->parent->left = rightChild;
	else
		node->parent->right = rightChild;

	rightChild->left = node;
	node->parent = rightChild;
}

void RBTreeInterraction::rightRotate(RBTree*& root, RBTree* node)
{
	RBTree* leftChild = node->left;
	node->left = leftChild->right;

	if (node->left != nullptr)
		node->left->parent = node;

	leftChild->parent = node->parent;

	if (node->parent == nullptr)
		root = leftChild;
	else if (node == node->parent->left)
		node->parent->left = leftChild;
	else
		node->parent->right = leftChild;

	leftChild->right = node;
	node->parent = leftChild;
}

RBTree* RBTreeInterraction::minValueNode(RBTree* node)
{
	RBTree* current = node;

	while (current->left != nullptr)
		current = current->left;

	return current;
}

void RBTreeInterraction::deleteNode(RBTree*& root, int data)
{
	RBTree* node = root;
	RBTree* parent = nullptr;
	bool found = false;

	// Find the node to delete
	while (node != nullptr)
	{
		if (data == node->data)
		{
			found = true;
			break;
		}

		parent = node;

		if (data < node->data)
			node = node->left;
		else
			node = node->right;
	}

	if (!found)
	{
		std::cout << "Node with data " << data << " not found in the tree." << std::endl;
		return;
	}

	if (node->left == nullptr || node->right == nullptr)
	{
		RBTree* child = node->left ? node->left : node->right;

		if (node->color == NodeColor::BLACK)
		{
			if (child != nullptr)
				child->color = NodeColor::BLACK;
			else
				balanceTreeDel(root, node);
		}

		if (parent == nullptr)
			root = child;
		else if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;

		if (child != nullptr)
			child->parent = parent;

		delete node;
	}
	else
	{
		RBTree* successor = minValueNode(node->right);
		node->data = successor->data;
		deleteNode(root, successor->data);
	}
}

void RBTreeInterraction::balanceTreeDel(RBTree*& root, RBTree* node)
{
	if (node == root)
		return;

	RBTree* sibling;
	bool leftChild = false;

	if (node->parent->left == node)
	{
		sibling = node->parent->right;
		leftChild = true;
	}
	else
		sibling = node->parent->left;

	// Case 1: Sibling is red - Rotate to make it black
	if (sibling->color == NodeColor::RED)
	{
		if (leftChild)
			leftRotate(root, node->parent);
		else
			rightRotate(root, node->parent);

		sibling->color = NodeColor::BLACK;
		node->parent->color = NodeColor::RED;
		balanceTreeDel(root, node);
	}
	else
	{
		// Case 2: Sibling is black, and both children are black
		if ((sibling->left == nullptr || sibling->left->color == NodeColor::BLACK) &&
			(sibling->right == nullptr || sibling->right->color == NodeColor::BLACK))
		{
			sibling->color = NodeColor::RED;
			if (node->parent->color == NodeColor::BLACK)
				balanceTreeDel(root, node->parent);
			else
				node->parent->color = NodeColor::BLACK;
		}
		else
		{
			if (leftChild)
			{
				// Case 3: Sibling is black, sibling's left child is red, sibling's right child is black
				if (sibling->right == nullptr || sibling->right->color == NodeColor::BLACK)
				{
					leftRotate(root, sibling);
					sibling->color = NodeColor::RED;
					sibling->left->color = NodeColor::BLACK;
					sibling = sibling->left;
				}

				// Case 4: Sibling is black, sibling's right child is red
				rightRotate(root, node->parent);
				std::swap(node->parent->color, sibling->color);
				sibling->right->color = NodeColor::BLACK;
			}
			else
			{
				// Case 3: Sibling is black, sibling's right child is red, sibling's left child is black
				if (sibling->left == nullptr || sibling->left->color == NodeColor::BLACK)
				{
					rightRotate(root, sibling);
					sibling->color = NodeColor::RED;
					sibling->right->color = NodeColor::BLACK;
					sibling = sibling->right;
				}

				// Case 4: Sibling is black, sibling's left child is red
				leftRotate(root, node->parent);
				std::swap(node->parent->color, sibling->color);
				sibling->left->color = NodeColor::BLACK;
			}

			node->parent->color = NodeColor::BLACK;
		}
	}
}