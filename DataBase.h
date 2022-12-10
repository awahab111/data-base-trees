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
	SLinkedList<string> fieldHeadings;

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
		//insertion_list.head->data.print();
		makeAvlTree();
		avl_tree.write();
		avl_tree_2.read();
		//pointSearch();
		//avl_tree_2.print2D(avl_tree_2.root, 1);
		//Update();
		//Range_Search();
		Delete();
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
		SNode<Key<string>> *duplicate = insertion_list.head;
		bool flag = true;
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
							//------------------------
							while (duplicate != NULL){
								if (duplicate->data.key_val == word){
									duplicate->data.update_key(seekgVal, file_name[i]);
									flag = false;
									break;
								}
								duplicate = duplicate->next;
							}
							duplicate = insertion_list.head;
							//------------------------
							if (flag){
								Key<string> data(word, seekgVal, file_name[i]);
								insertion_list.insert(data);
							}
							flag = true;
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
				fieldHeadings.insert(word); // filling up the headings linkedList
				cout << disp_index << ". " << word << endl; //displaying the headings for user to create index tree on
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
		word += ',';
		word += temp;
		word += "\"";
		str.get();// to skip the comma-
	}

	//void Print_Key() {
	//	string line, word;
	//	SNode<string>* filename = node->data.file_name.head;
	//	SNode<int>* seekgVal = node->data.line_buffer.head;
	//	cout << "Following data has been found:\n";
	//	for (int i = 0; i < (node->data.file_name.numOfItems); i++)
	//	{

	//		ifstream fin(filename->data);
	//		fin.seekg(seekgVal->data);	//jumping to the index line
	//		getline(fin, line);	//reading the line
	//		stringstream str(line);
	//		SNode<string>* heading = fieldHeadings.head;
	//		cout << "===========================\n";
	//		while (heading)
	//		{
	//			getline(str, word, ',');
	//			if (word[0] == '"') getCompleteWord(word, str);
	//			cout << heading->data << ": " << word << endl;
	//			heading = heading->next;
	//		}
	//		cout << "===========================\n";
	//		fin.close();
	//		filename = filename->next;
	//		seekgVal = seekgVal->next;
	//	}
	//}

//	template<class T>
	void pointSearch()
	{
		string input = "";
		cout << "Search for: ";
		cin.ignore();
		getline(cin, input);

		Key<string> searchKey(input); // ==> searchKey.key_value = input;
		AVL_Node<Key<string>>* node = avl_tree.retrieve(searchKey);
		if (node == nullptr)
			cout << "No such key was found.\n";
		else
		{
			string line, word;
			SNode<string>* filename = node->data.file_name.head;
			SNode<int> *seekgVal = node->data.line_buffer.head;
			cout << "Following data has been found:\n";
			for (int i = 0; i < (node->data.file_name.numOfItems); i++)
			{

				ifstream fin(filename->data);
				fin.seekg(seekgVal->data);	//jumping to the index line
				getline(fin, line);	//reading the line
				stringstream str(line);
				SNode<string>* heading = fieldHeadings.head;
				cout << "===========================\n";
				while (heading)
				{
					getline(str, word, ',');
					if (word[0] == '"') getCompleteWord(word, str);
					cout << heading->data << ": " << word << endl;
					heading = heading->next;
				}
				cout << "===========================\n";
				fin.close();
				filename = filename->next;
				seekgVal = seekgVal->next;
			}
		}
	}

	void Range_Search() {
		string lower, upper;
		//---------------Taking Input for out range--------------------
		cin.ignore();
		cout << "Enter your Lower Search Limit: ";
		getline(cin, lower);
		cout << "Enter your Upper Search Limit: ";
		getline(cin, upper);
		//-----------------------------------------
		Key<string> lower_lim(lower), upper_lim(upper); // Making the input into keys
		SLinkedList <Key<string>> search_result; // Initializing our linked list for the search results which we get from our range search
		avl_tree.RangeSearch(avl_tree.root, lower_lim, upper_lim, search_result);// Calling the Range search function in AVL Tree 
		SNode<Key<string>>* search_node = search_result.head;
		while (search_node != NULL){
			search_node->data.print(fieldHeadings);// printing the values of our keys
			search_node = search_node->next;
		}

	}

	void Update()
	{
		string input, field, oldVal, newVal;
		cin.ignore();
		cout << "Enter the key whose data you want to update: ";
		getline(cin, input);
		cout << "Name of the field to be modified: ";
		getline(cin, field);
		cout << "Enter the old value: ";
		getline(cin, oldVal);
		cout << "Enter the new value: ";
		getline(cin, newVal);

		Key<string> searchKey(input); // ==> searchKey.key_value = input;
		AVL_Node<Key<string>>* node = avl_tree.retrieve(searchKey);

		if (node == nullptr)
			cout << "No such key was found.\n";
		else
		{
			string line, word, updateFilename;
			int matchingValCount = 0, updateLineSeekg = 0;
			SNode<string>* filename = node->data.file_name.head;
			SNode<int>* seekgVal = node->data.line_buffer.head;

			//---------------- Finding the line that is to be updated
			for (int i = 0; i < (node->data.file_name.numOfItems); i++)
			{

				ifstream fin(filename->data);			
				fin.seekg(seekgVal->data);	//jumping to the index line
				getline(fin, line);	//reading the line
				stringstream str(line);
				//
				SNode<string>* heading = fieldHeadings.head;
				while (field != heading->data)
				{
					getline(str, word, ',');
					if (word[0] == '"') getCompleteWord(word, str);
					heading = heading->next;

				}
				//----- this condition is necessary in case of repeated old values
				getline(str, word, ',');
				if (word == oldVal) 
				{
					matchingValCount++;
					updateLineSeekg = seekgVal->data;
					updateFilename = filename->data;
				}
				if (matchingValCount > 1) //------ if The old value is repeated, error is displayed.
				{
					cout << "Error404: Duplicate Old values were found.\n";
					return;
				}
				//
				fin.close();
				filename = filename->next;
				seekgVal = seekgVal->next;
			}

			//--------- saving the line
			string tempLine;
			SLinkedList<string> updateLine;
			SLinkedList<string> remainingLines;
			ifstream fin(updateFilename);
			fin.seekg(updateLineSeekg);
			getline(fin, line);				//reading the line that is to be overriden
			stringstream str(line);
			while (getline(str, word, ','))
			{
				if (word[0] == '"') getCompleteWord(word, str);
				updateLine.insert(word);
			}
			if(newVal > oldVal)
			while(getline(fin, tempLine))
			{
				remainingLines.insert(tempLine);
			}
			fin.close();
			//------------ writing the line to file
			SNode<string>* traverser = updateLine.head;
			ofstream fout(updateFilename, ios:: in | ios::out);
			fout.seekp(updateLineSeekg);
			//--------- removing the old line
			for (int i = 0; i < line.size(); i++)
				fout << '\0';
			//-----
			fout.seekp(updateLineSeekg, ios::beg);
			SNode<string>* heading = fieldHeadings.head;
			while (field != heading->data)
			{
				fout << traverser->data << ',';
				traverser = traverser->next;
				heading = heading->next;
			}
			fout << newVal << ',';
			traverser = traverser->next; //skipping the old value
			while (traverser)
			{
				if (traverser->next)	//if end is not reached
					fout << traverser->data << ',';
				else
					fout << traverser->data;
				traverser = traverser->next;
			}
			if (newVal > oldVal)
			{
				fout << '\n';
				traverser = remainingLines.head;
				while (traverser)
				{
					fout << traverser->data << '\n';
					traverser = traverser->next;
					
				}
			}
		//	fout << tempLine;
			fout.close();
		}

	}

	void remove(AVL_Node<Key<string>>* delete_key) {
		SNode<string> *filename_node = delete_key->data.file_name.head; // Initializing the locations of the tuples
		SNode<int>* seekgVal = delete_key->data.line_buffer.head;
		string line, word;
		while (filename_node != NULL){
			fstream fout(filename_node->data, ios::in | ios::out);
			fout.seekp(seekgVal->data);
			SNode<string>* heading = fieldHeadings.head;
			getline(fout, line);
			stringstream str(line);
			while (heading != NULL)
			{
				getline(str, word ,',');
				if (word[0] == '"') getCompleteWord(word, str);
				for (int i = 0; i < word.size(); i++){
					fout << "# ";
				}
				fout << "# ,";
				heading = heading->next;
			}
			fout.close();
			filename_node = filename_node->next;
			seekgVal = seekgVal->next;
		}
	}

	void Delete() {
		string delete_val;
		cin.ignore();
		cout << "Enter the Key you want to delete: ";
		getline(cin, delete_val);
		Key<string> delete_key(delete_val);
		AVL_Node<Key<string>>* delete_node = avl_tree.retrieve(delete_key);
		remove(delete_node);
		//avl_tree.Delete(delete_key, avl_tree.root);
	}

};
