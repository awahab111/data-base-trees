#pragma once
#include "Queue.h"
#include "Key.h"
//#include <string>
#include <fstream>
#include <sstream>
using namespace std;
template <class T>
class AVL_Node
{
public:
	T data;
	int height = 0;
	AVL_Node<T>* left = nullptr;
	AVL_Node<T>* right = nullptr;

	AVL_Node(T d){
		data = d;
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

	void write() {
		ofstream f1("r1.csv");
		writeAVLTree(root, f1);
	}

	void writeAVLTree(AVL_Node<T>* root, ofstream& out) {

		if (!root) {
			out << "#\n";
		}
		else {
			root->data.fileoperator(out);
			writeAVLTree(root->left, out);
			writeAVLTree(root->right, out);
		}

	}

	void read() {
		ifstream f1("r1.csv");
		readAVLTree(this->root, f1);
		f1.close();
	}
	void readAVLTree(AVL_Node<T>*& root, ifstream& fin) {
		Key<string> key_val;
		bool isKey;
		if (!readKey(fin, key_val, isKey)){
			return;
		}
		if (isKey)
		{
			root = new AVL_Node<T> (key_val);
			readAVLTree(root->left, fin);
			readAVLTree(root->right, fin);
		}
		
		
	}

	bool readKey(ifstream& fin, Key<string>& data , bool& a) {
		string line, word;
		getline(fin, line);
		stringstream str(line);
		if (line[0] == '#') {
			a = false;
			return false;
		}
		getline(str, word, ',');
		data.key_val = word;
		getline(str, word, ',');
		while (!(word[0] == '#')) {
			data.line_buffer.insert(stoi(word));
			getline(str, word, ',');
		}
		getline(str, word, ',');
		while (!(word[0] == '#')) {
			data.file_name.insert(word);
			getline(str, word, ',');
		}
		a = true;
		return true;
	}



	void Insert(T val) {
		/*if (data_type == 0)
		{
			float temp = stof(val);
			Insert_(temp, root);
		}*/
		Insert_(val, root);
	}

	AVL_Node<T>* Insert_(T X, AVL_Node<T>* root) {
		if (root == NULL)	root = new AVL_Node<T>(X);
		else if (X < root->data) {
			root->left = Insert_(X, root->left);
			if (Height(root->left) - Height(root->right) == 2)
				if (X < root->left->data)
					root = RRotation(root); // RR rotation
				else
					root = RL_Rotation(root); // RL rotation
		}
		else if (X > root->data) {
			root->right = Insert_(X, root->right);
			if (Height(root->right) - Height(root->left) == 2)
				if (X > root->right->data)
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


	AVL_Node<T>* retrieve(Key<string> node)
	{
		if (!root)
		{
			cout << "Tree does not exist.\n";
			return nullptr;
		}
		else
		{
			AVL_Node<T>* temp = root;
			while (temp)
			{
				if (temp->data.key_val == node.key_val) return temp;
				if (node > temp->data)
					temp = temp->right;
				else if (node < temp->data)
					temp = temp->left;
			}
		}
		return nullptr;		//value wasnt found
	}

	void PreOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		cout << node->data << " ";
		PreOrderTraversal(node->left);
		PreOrderTraversal(node->right);

	}

	void PostOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		PostOrderTraversal(node->left);
		PostOrderTraversal(node->right);
		cout << node->data << " ";

	}

	void InOrderTraversal(AVL_Node<T>* node)
	{

		if (node == nullptr)
			return;
		InOrderTraversal(node->left);
		cout << node->data << " ";
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
			cout << temp.data << " ";

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
				cout << node->data << " ";
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
		return temp->data;
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
		else if (val == node->data) {
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
				node->data = min;
				node->right = Delete(min, temp);
			}
		}
		else if (val < node->data) { node->left = Delete(val, node->left); }
		else if (val > node->data) { node->right = Delete(val, node->right); }
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
		cout << r->data << "\n"; // 6
		print2D(r->left, space); // Process left child  7
	}
	AVL_Node<T>* Search(T d) {
		AVL_Node<T>* node = root;
		while (node != NULL)
		{
			if (node->data < d)
			{
				node = node->left;
			}
			else if (node->data > d)
			{
				node = node->right;
			}
			else if (node->data == d)
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
	//	else if (k == root-> data)
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
	//			root->data = min;
	//			Delete(min, temp);
	//		}
	//	}
	//	else if (k < root->data)
	//		Delete(k, root->left);
	//	else if (k > root->data)
	//		Delete(k, root->right);
	//}

};