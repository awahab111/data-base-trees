#include "DataBase.h"

//AVL_Node<float>* makeAvlTree_float(SLinkedList<string> list)
//{
//	AVLTree<float> avl_tree;
//	SNode<string>* snode = list.head;
//	float key;
//	while (snode != NULL)
//	{
//		key = stof(snode->data);
//		avl_tree.Insert(key, avl_tree.root);
//		snode = snode->next;
//	}
//
//	return avl_tree.root;
//
//}

//void AVL_Tree_Indexing()
//{
//	string file_name = "data_1.csv";
//	AVLTree<float> tree_f;
//	AVLTree<string> tree_s;
//
//	int field_type = getFieldType(file_name);
//	//cout << "field_type: " << field_type << endl;
//	int data_type = getDataType(file_name, field_type);
//	//cout << "data_type: " << data_type << endl;
//	//show_data(file_name, field_type);
//	SLinkedList<string> list;
//	createLinkedList(file_name, list, field_type);
//	if (data_type == 0)
//	{
//		tree_f.root = makeAvlTree_float(list);
//	}
//	else {
//		tree_s.root = makeAvlTree_string(list);
//	}
//	//tree_f.print2D(tree_f.root, 1);
//	if (data_type == 0)
//	{
//		return tree_f.root;
//	}
//	else return tree_s.root;
//
//}


int main()
{
	//string ab = "data_1.csv";
	Database bruh("data_1.csv");

}