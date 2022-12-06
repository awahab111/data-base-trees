
#include "AVL_Tree.h"
#include <algorithm>

using namespace std;






int main()
{
	AVLTree tree;
	tree.Insert(9, tree.root);
	tree.Insert(5, tree.root);
	tree.Insert(10, tree.root);
	tree.Insert(0, tree.root);
	tree.Insert(6, tree.root);
	tree.Insert(11, tree.root);
	tree.Insert(-1, tree.root);
	tree.Insert(1, tree.root);
	tree.Insert(2, tree.root);
	//tree.(tree.root);

	tree.PreOrderTraversal(tree.root);
	tree.root = tree.Delete(10, tree.root);
	cout << endl;
	tree.PreOrderTraversal(tree.root);

//	tree.Remove(tree.root, 10);
	//cout << endl;
	//tree.LevelOrder(tree.root);

}