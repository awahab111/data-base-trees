#pragma once
#include "Queue.h"
#include "Key.h"
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
	int SPACE= 5; // for the print function
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

		if (!root) { // if the node is null then write #
			out << "#\n";
		}
		else {
			// Writing the data to the file using preorder traversal 
			root->data.fileoperator(out);
			out << ',' << root->height << '\n';
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
		int key_height;
		bool isKey;
		if (!readKey(fin, key_val, isKey, key_height)){ // Read from the file
			return;
		}
		if (isKey)
		{
			// Using preorder to make the tree again
			root = new AVL_Node<T> (key_val);
			root->height = key_height;
			readAVLTree(root->left, fin);
			readAVLTree(root->right, fin);
		}
	}

	bool readKey(ifstream& fin, Key<string>& data , bool& a, int& height) {
		// Function to make a tree by reading from a file
		string line, word;
		getline(fin, line);
		stringstream str(line);
		// --------- Extracting data from the file 
		if (line[0] == '#') {
			a = false; // if data was not found return false
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
		getline(str, word, ',');
		height = stoi(word);
		//------------------------------
		a = true; // if data was found then return true
		return true;
	}

	void Insert(T val) {
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
				if (temp->data == node) return temp; // Val was found 
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

	void delete_tree(AVL_Node<T>* node) {
		if (node == NULL) {return;} // Using Post Order to delete the tree
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}

	void RangeSearch(AVL_Node<T>* root, T lower_lim, T upper_lim, SLinkedList<T>& result) {
		if (root == NULL) { return; } // Base Case
		if (lower_lim < root->data){ 
			RangeSearch(root->left, lower_lim, upper_lim, result); // Moving to the left subtree if data is greater than the lower limit
		}
		if ((root->data < upper_lim || root->data == upper_lim) && (root->data > lower_lim || root->data == lower_lim)) {
			result.insert(root->data); // insert the data into the linked list if data is within the lower and upper lim
		}
		RangeSearch(root->right, lower_lim, upper_lim, result); // else data is smaller than the lower lim and move to the right subtree
	}

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

	T getMin(AVL_Node<T>* root)
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

	AVL_Node<T>* Delete(T val, AVL_Node<T>* node) {
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
				T min = getMin(temp);
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

	// This uses Inorder traversal to print a tree vertically
	void print2D(AVL_Node<T>* r, int space) {
		if (r == NULL) // base case
			return;
		space += SPACE; // Increase distance between levels
		print2D(r->right, space); // printing right child first
		cout << endl;
		for (int i = SPACE; i < space; i++) 
			cout << " ";  // Printing space between to nodes needs to increase as it gets closer to the root
		cout << r->data << "\n";
		print2D(r->left, space);
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

	~AVLTree() {
		delete_tree(root);
		root = NULL;
	}
};