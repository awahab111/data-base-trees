#pragma once
#include "AVL_Tree.h"
#include "SinglyLinkedList.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
class Database {
public:
	int data_type;
	int field_type;
	string file_name;
	SLinkedList<string> insertion_list;
	AVLTree<string> avl_tree;

	Database() {}

	Database(string f1) {
		file_name = f1;
		field_type = getFieldType();
		data_type = getDataType();
		createLinkedList();
		makeAvlTree();
	}

	void makeAvlTree()
	{
		SNode<string>* snode = insertion_list.head;
		while (snode != NULL)
		{
			avl_tree.Insert(snode->data);
			snode = snode->next;
		}
	}


	void show_data() {
		fstream fin(file_name, ios::in);
		string line, word;
		int data_type;
		int disp_index = 0;
		if (fin.is_open())
		{
			cout << "File has opened succesfully.\n";
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
		fstream fin(file_name, ios::in);
		string line, word;
		if (fin.is_open())
		{
			cout << "File has opened succesfully.\n";
			getline(fin, line);
			while (getline(fin, line)) {
				stringstream str(line);
				for (int i = 0; i <= field_type; i++)
				{
					getline(str, word, ',');
					if (word[0] == '"') getCompleteWord(word, str);
					if (i == field_type)
					{
						insertion_list.insert(word);
						break;
					}

				}
			}

		}

		fin.close();

	}

	int getFieldType()
	{
		ifstream fin(file_name, ios::in);
		string line, word;
		int field = 0;
		int disp_index = 0;
		if (fin.is_open())
		{
			cout << "File has opened succesfully.\n";
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
		ifstream fin(file_name, ios::in);
		string line, word;
		int data_type = 0;
		int disp_index = 0;
		if (fin.is_open())
		{
			cout << "File has opened succesfully.\n";
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
