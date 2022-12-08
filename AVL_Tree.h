#pragma once
#include "Queue.h"
#include <fstream>
#include <sstream>
using namespace std;
template <class T>
class AVL_Node
{
public:
	T key;
	int height = 0;
	AVL_Node<T>* left = nullptr;
	AVL_Node<T>* right = nullptr;

	AVL_Node(T d){
		key = d;
	}

	int getHeight()
	{
		return height;
	}

};

template <class T>
class AVLTree
{
public:
	AVL_Node<T>* root;
	AVLTree()
	{
		root = NULL;
	}

	//functions
	//void insert(int k)
	//{
	//	AVL_Node<T>* newNode = new AVL_Node(k);
	//	if (!root)
	//	{
	//		root = newNode;
	//	}
	//	else
	//	{
	//		AVL_Node<T>* temp = root;
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

	int Height(AVL_Node<T>* P)
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

	void Insert(T val) {
		Insert_(val, root);
	}

	AVL_Node<T>* Insert_(T X, AVL_Node<T>* root) {
		if (root == NULL)	root = new AVL_Node<T>(X);

		else if (X < root->key) {
			root->left = Insert_(X, root->left);
			if (Height(root->left) - Height(root->right) == 2)
				if (X < root->left->key)
					root = RRotation(root); // RR rotation
				else
					root = RL_Rotation(root); // RL rotation

		}
		else if (X > root->key) {
			root->right = Insert_(X, root->right);
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


	AVL_Node<T>* LRotation(AVL_Node<T>* node) {
		AVL_Node<T>* temp;
		temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node->height = Max(Height(node->left), Height(node->right)) + 1;
		temp->height = Max(Height(temp->right), node->height) + 1;
		return temp;
	}


	AVL_Node<T>* RRotation(AVL_Node<T>* node) {
		AVL_Node<T>* temp;
		temp = node->left;
		node->left = temp->right;
		temp->right = node;
		node->height = Max(Height(node->left), Height(node->right)) + 1;
		temp->height = Max(Height(temp->left), node->height) + 1;
		return temp;
	}

	AVL_Node<T>* RL_Rotation(AVL_Node<T>* K3)
	{

		K3->left = LRotation(K3->left);
		return RRotation(K3);
	}

	AVL_Node<T>* LR_Rotation(AVL_Node<T>* K1)
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
			AVL_Node<T>* temp = root;
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

	void PreOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		cout << node->key << " ";
		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);

	}

	void PostOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		cout << node->key << " ";

	}

	void InOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		InOrderTraversal(node->left);
		cout << node->key << " ";
		InOrderTraversal(node->right);

	}

	/*void LevelOrder(AVL_Node<T>* root)
	{
		if (root == nullptr)return;
		Queue<AVL_Node<T>> queue;
		queue.enqueue(*root);
		while (queue.num_items < 1)
		{
			AVL_Node<T> temp = queue.dequeue();
			cout << temp.key << " ";

			if (temp.left != nullptr) queue.enqueue(*temp.left);
			if (temp.right != nullptr) queue.enqueue(*temp.right);
		}
	}*/
	void LevelOrder(AVL_Node<T>* ptr) {
		if (root == NULL) { return; }
		Queue <AVL_Node<T>*> q1;
		q1.enqueue(root);
		q1.enqueue(NULL);
		while (q1.num_items > 1)
		{
			AVL_Node<T>* node = q1.Front();
			q1.dequeue();
			if (node == NULL)
			{
				q1.enqueue(NULL);
				cout << endl;
			}
			else {
				if (node->left)
				{
					q1.enqueue(node->left);
				}
				if (node->right)
				{
					q1.enqueue(node->right);
				}
				cout << node->key << " ";
			}



		}
	}


	int getMin(AVL_Node<T>* root)
	{
		AVL_Node<T>* temp = root;

		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp->key;
	}

	AVL_Node<T>* getMinNode(AVL_Node<T>* root)
	{
		AVL_Node<T>* temp = root;

		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp;
	}

	int balanceFactor(AVL_Node<T>* N)
	{
		if (N == NULL)
			return 0;
		return Height(N->left) -
			Height(N->right);
	}

	AVL_Node<T>* Delete(int val, AVL_Node<T>* node) {
		AVL_Node<T>* temp;
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

	// Copied plz change this
	int SPACE = 5;
	void print2D(AVL_Node<T>* r, int space) {
		if (r == NULL) // Base case  1
			return;
		space += SPACE; // Increase distance between levels   2
		print2D(r->right, space); // Process right child first 3 
		cout << endl;
		for (int i = SPACE; i < space; i++) // 5 
			cout << " "; // 5.1  
		cout << r->key << "\n"; // 6
		print2D(r->left, space); // Process left child  7
	}
	AVL_Node<T>* Search(T d) {
		AVL_Node<T>* node = root;
		while (node != NULL)
		{
			if (node->key < d)
			{
				node = node->left;
			}
			else if (node->key > d)
			{
				node = node->right;
			}
			else if (node->key == d)
			{
				cout << "Found";
				break;
			}
		}
		return node;
	}

	//void Delete(int k, AVL_Node<T>*& root)
	//{
	//	if (!root) return;
	//	else if (k == root-> key)
	//	{
	//		
	//		 if (!root->left)//left is null
	//		{
	//			AVL_Node<T>* temp = root->right;
	//			delete root;
	//			root = temp;
	//		}
	//		else if (!root->right)//right is null
	//		{
	//			AVL_Node<T>* temp = root->left;
	//			delete root;
	//			root = temp;
	//		}
	//		else
	//		{
	//			AVL_Node<T>* temp = root->right;
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