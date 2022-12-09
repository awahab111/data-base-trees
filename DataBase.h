#pragma once
#include "AVL_Tree.h"
#include "SinglyLinkedList.h"
#include "Key.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Database {
public:
	int data_type;
	int field_type;
	string *file_name;
	int num_of_files;
	SLinkedList<Key<string>> insertion_list;
	AVLTree<Key<string>> avl_tree, avl_tree_2;

	Database() {}

	Database(string f1[], int files_count) {
		num_of_files = files_count;
		file_name = new string[num_of_files];
		for (int i = 0; i < num_of_files; i++) { file_name[i] = f1[i]; }
		field_type = getFieldType();
		data_type = getDataType();
		cout << "Create Linked List" << endl;
		createLinkedList();
		cout << "Linked List Made " << endl;
		//insertion_list.print();
		makeAvlTree();
		avl_tree.write();
		avl_tree_2.read();
		avl_tree_2.print2D(avl_tree_2.root, 1);

	}



	void makeAvlTree()
	{
		SNode<Key<string>>* snode = insertion_list.head;
		while (snode != NULL)
		{
			avl_tree.Insert(snode->data);
			snode = snode->next;
		}
	}


	void show_data() {
		fstream fin(file_name[0], ios::in);
		string line, word;
		int data_type;
		int disp_index = 0;
		if (fin.is_open())
		{
			//cout << "File has opened succesfully.\n";
			getline(fin, line);
			while (getline(fin, line)) {
				stringstream str(line);
				for (int i = 0; i <= field_type; i++)
				{
					getline(str, word, ',');
					if (word[0] == '"') getCompleteWord(word, str);
					if (i == field_type) {
						cout << word << endl;
						break;
					}

				}
			}

		}
		fin.close();
	}

	void createLinkedList()
	{
		string line, word;
		for (int i = 0; i < num_of_files; i++)
		{
			fstream fin(file_name[i], ios::in);
			int line_num = 1;
			if (fin.is_open())
			{
				getline(fin, line);
				int seekgVal = fin.tellg(); // starting value of first 'data' row
				while (getline(fin, line)) {	//this loop is for traversing through the whole file line by line
					stringstream str(line);
					for (int j = 0; j <= field_type; j++) // this loop is for traversing through the columns of a single row
					{
						getline(str, word, ',');
						if (word[0] == '"') getCompleteWord(word, str);
						if (j == field_type){
							Key<string> data(word, line_num++, file_name[i], seekgVal);
							insertion_list.insert(data);
							break;
						}
					}
					seekgVal = fin.tellg();	//	getting the start value of each row
				}
			}
			fin.close();
		}
	}

	int getFieldType()
	{
		ifstream fin(file_name[0], ios::in);
		string line, word;
		int field = 0;
		int disp_index = 0;
		if (fin.is_open())
		{
			//cout << "File has opened succesfully.\n";
			getline(fin, line);
			stringstream str(line);
			while (getline(str, word, ',')) {
				cout << disp_index << ". " << word << endl;
				disp_index++;
			}
			cout << "Choose field type : ";
			cin >> field;
		}
		fin.close();

		return field;
	}


	int getDataType()
	{
		ifstream fin(file_name[0], ios::in);
		string line, word;
		int data_type = 0;
		int disp_index = 0;
		if (fin.is_open())
		{
			//cout << "File has opened succesfully.\n";
			getline(fin, line);
			getline(fin, line);
			stringstream str(line);
			for (int i = 0; i <= field_type; i++)
			{
				getline(str, word, ',');
				if (word[0] == '"') getCompleteWord(word, str);
				if (i == field_type)
				{
					cout << "DATA: " << word << endl;
					data_type = check_datatype(word);
					break;
				}

			}
		}
		fin.close();
		return data_type;
	}

	int check_datatype(string word) {
		for (int i = 0; i < word.size(); i++)
		{
			if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) return 1; // returns 1 if the value is a string 
		}
		return 0; // returns 0 if the value is float 
	}

	void getCompleteWord(string& word, stringstream& str)
	{
		string temp;
		getline(str, temp, '"');
		word += temp;
		str.get();// to skip the comma-
	}
};
