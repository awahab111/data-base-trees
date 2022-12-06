#pragma once
#include "Queue.h"
class Node
{
public:
	int key;
	int height = 0;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int d) :key(d) {}

	int getHeight()
	{
		return height;
	}

};

class AVLTree
{
public:
	Node* root = nullptr;

	AVLTree()
	{}

	//functions
	//void insert(int k)
	//{
	//	Node* newNode = new Node(k);
	//	if (!root)
	//	{
	//		root = newNode;
	//	}
	//	else
	//	{
	//		Node* temp = root;
	//		while (temp)
	//		{
	//			if (temp->left == nullptr && k < temp->key)
	//			{
	//				temp->left = newNode;
	//				break;
	//			}
	//			if (temp->right == nullptr && k > temp->key)
	//			{
	//				temp->right = newNode;
	//				break;
	//			}
	//			if (k > temp->key)
	//				temp = temp->right;
	//			else if (k < temp->key)
	//				temp = temp->left;
	//		}
	//		
	//		
	//	}
	//}

	int Height(Node* P)
	{

		if (P == NULL)
			return -1;

		else

			return P->height;

	}

	int Max(int a, int b)
	{
		if (a > b) return a;
		return b;
	}

	Node* Insert(int X, Node* root) {
		if (root == NULL)	root = new Node(X);

		else if (X < root->key) {
			root->left = Insert(X, root->left);
			if (Height(root->left) - Height(root->right) == 2)
				if (X < root->left->key)
					root = RRotation(root); // RR rotation
				else
					root = RL_Rotation(root); // RL rotation

		}
		else if (X > root->key) {
			root->right = Insert(X, root->right);
			if (Height(root->right) - Height(root->left) == 2)
				if (X > root->right->key)
					root = LRotation(root); // LL rotation
				else
					root = LR_Rotation(root); // LR rotation
		}
		root->height = Max(Height(root->left), Height(root->right)) + 1;
		this->root = root;
		return root;
	}


	Node* LRotation(Node* node) {
		Node* temp;
		temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node->height = Max(Height(node->left), Height(node->right)) + 1;
		temp->height = Max(Height(temp->right), node->height) + 1;
		return temp;
	}


	Node* RRotation(Node* node) {
		Node* temp;
		temp = node->left;
		node->left = temp->right;
		temp->right = node;
		node->height = Max(Height(node->left), Height(node->right)) + 1;
		temp->height = Max(Height(temp->left), node->height) + 1;
		return temp;
	}

	Node* RL_Rotation(Node* K3)
	{

		K3->left = LRotation(K3->left);
		return RRotation(K3);
	}

	Node* LR_Rotation(Node* K1)
	{
		K1->right = RRotation(K1->right);
		return LRotation(K1);
	}

	bool retrive(int k)
	{
		if (!root)
		{
			return false;
		}
		else
		{
			Node* temp = root;
			while (temp)
			{
				if (temp->key == k) return true;
				if (k > temp->key)
					temp = temp->right;
				else if (k < temp->key)
					temp = temp->left;
			}
		}
		return false;
	}

	void PreOrderTraversal(Node* node)
	{

		if (node == nullptr)
			return;
		cout << node->key << " ";
		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);

	}

	void PostOrderTraversal(Node* node)
	{

		if (node == nullptr)
			return;
		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		cout << node->key << " ";

	}

	void InOrderTraversal(Node* node)
	{

		if (node == nullptr)
			return;
		InOrderTraversal(node->left);
		cout << node->key << " ";
		InOrderTraversal(node->right);

	}

	void LevelOrder(Node* root)
	{
		if (root == nullptr)return;
		Queue<Node> queue;
		queue.enqueue(*root);
		while (!queue.isEmpty())
		{
			Node temp = queue.dequeue();
			cout << temp.key << " ";

			if (temp.left != nullptr) queue.enqueue(*temp.left);
			if (temp.right != nullptr) queue.enqueue(*temp.right);
		}
	}

	int getMin(Node* root)
	{
		Node* temp = root;

		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp->key;
	}

	Node* getMinNode(Node* root)
	{
		Node* temp = root;

		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp;
	}

	int balanceFactor(Node* N)
	{
		if (N == NULL)
			return 0;
		return Height(N->left) -
			Height(N->right);
	}

	Node* Delete(int val, Node* node) {
		Node* temp;
		if (!node) return node;
		else if (val == node->key) {
			if (!node->right) {
				temp = node->left;
				delete node;
				node = temp;
			}
			else if (!node->left) {
				temp = node->right;
				delete node;
				node = temp;
			}
			else {
				temp = node->right;
				int min = getMin(temp);
				node->key = min;
				node->right = Delete(min, temp);
			}
		}
		else if (val < node->key) { node->left = Delete(val, node->left); }
		else if (val > node->key) { node->right = Delete(val, node->right); }
		if (node == NULL) { return node; }
		node->height = 1 + max(Height(node->left), Height(node->right));
		int bf = balanceFactor(node);
		if (bf > 1 && balanceFactor(root->left) >= 0)
			return RRotation(root);

		if (bf > 1 && balanceFactor(root->left) < 0)
		{
			return RL_Rotation(root);
		}

		if (bf < -1 && balanceFactor(root->right) <= 0)
			return LRotation(root);

		if (bf < -1 && balanceFactor(root->right) > 0)
		{
			return LR_Rotation(root);
		}
		return node;
	}

	//void Delete(int k, Node*& root)
	//{
	//	if (!root) return;
	//	else if (k == root-> key)
	//	{
	//		
	//		 if (!root->left)//left is null
	//		{
	//			Node* temp = root->right;
	//			delete root;
	//			root = temp;
	//		}
	//		else if (!root->right)//right is null
	//		{
	//			Node* temp = root->left;
	//			delete root;
	//			root = temp;
	//		}
	//		else
	//		{
	//			Node* temp = root->right;
	//			int min = getMin(temp);
	//			root->key = min;
	//			Delete(min, temp);
	//		}
	//	}
	//	else if (k < root->key)
	//		Delete(k, root->left);
	//	else if (k > root->key)
	//		Delete(k, root->right);
	//}

};