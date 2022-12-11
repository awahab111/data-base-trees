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
		Menu();
	}

	void Menu() {
		bool while_flag = true;
		while (true) {
			int option;
			system("CLS");
			cout << "Data Base System" << endl;
			cout << "1.Point Search\n2.Range Search\n3.Update\n4.Delete\n5.Read from file\n6.Write to file\n7.Make Tree\n8.Print Tree\n9.Destroy Tree\n10.Use Where Clause\n11.Exit\n";
			cout << "Enter your choice: ";
			cin >> option;
			bool flag = true;
			if (!avl_tree.root) { flag = false; }
			switch (option)
			{
			case 1 :
				if (flag) { pointSearchCall(); }
				else cout << "No Tree Exists" << endl;
				break;
			case 2 : 
				if (flag) {Range_Search();}
				else cout << "No Tree Exists" << endl;
				break;
			case 3:
				if (flag){Update();}
				else cout << "No Tree Exists" << endl;

				break;
			case 4:
				if (flag){Delete();}
				else cout << "No Tree Exists" << endl;
				break;
			case 5:
				if (!flag) { cout << "Loading...." << endl; Read(); cout << "Tree has been made" << endl; }
				else cout << "Tree Already Exists" << endl;
				break;
			case 6:
				if (flag) { cout << "Loading...." << endl; Write(); cout << "Tree has been written to file" << endl; }
				else cout << "No Tree Exists" << endl;
				break;
			case 7:
				if (!flag){
					field_type = getFieldType();
					data_type = getDataType();
					cout << "Loading....." << endl;
					createLinkedList();
					makeAvlTree();
					cout << "Tree Has been Made" << endl;
				}
				else cout << "Tree Already Exists" << endl;
				break;
			case 8 : 
				if (flag) { avl_tree.print2D(avl_tree.root, 1); }
				else cout << "No Tree Exists" << endl;
				break;
			case 9:
				if (flag) { cout << "Destroying..." << endl; Destroy_tree(); cout << "Tree Destroyed" << endl; }
				else cout << "No Tree Exists" << endl;
				break;
			case 10: 
				if (flag) { whereClause(); }
				else cout << "No Tree Exists" << endl;
				break;
			case 11 :
				while_flag = false;
				return;
			default:
				break;
			}
			system("PAUSE");
		}
	}

	void makeAvlTree()
	{
		SNode<Key<string>>* snode = insertion_list.head;
		while (snode != NULL)
		{
			avl_tree.Insert(snode->data); // Inserting data into the tree using the linked list
			snode = snode->next;
		}
	}

	void createLinkedList()
	{
		string line, word;
		bool flag = true;
		for (int i = 0; i < num_of_files; i++)
		{
			ifstream fin(file_name[i], ifstream::binary);
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
							SNode<Key<string>>* duplicate = insertion_list.head;
							while (duplicate != NULL){
								if (duplicate->data.key_val == word){
									duplicate->data.update_key(seekgVal, file_name[i]);
									flag = false;
									break;
								}
								duplicate = duplicate->next;
							}
							//------------------------
							if (word[0] == '#') { flag = false; }
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

	void fillFieldType() {
		ifstream fin(file_name[0], ios::in);
		string line, word;
		getline(fin, line);
		stringstream str(line);
		while (getline(str, word, ',')) {
			fieldHeadings.insert(word); // filling up the headings linkedList
		}
		fin.close();
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
			getline(fin, line);
			getline(fin, line);
			stringstream str(line);
			for (int i = 0; i <= field_type; i++)
			{
				getline(str, word, ',');
				if (word[0] == '"') getCompleteWord(word, str);
				if (i == field_type)
				{
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

	void whereClause()
	{
		
		string key, field, value,operation, whereClause;
		cout << "Enter the where clause: ";
		cin.ignore();
		getline(cin, whereClause);
		stringstream str(whereClause);
		str >> operation;
		str >> key;
		str >> field; // skipping the "where" word
		str >> field;
		str >> value; // skipping '='
		str >> value;
	if(operation[0] == 'p' || operation[0] == 'P')
		pointSearch(key, field, value);

	}

	void pointSearchCall()
	{
		string input = "";
		cout << "Enter the key you want to search for: ";
		cin.ignore();
		getline(cin, input);
		pointSearch(input, "", "");
	}

	void pointSearch(string& input, string field, string value)
	{
		Key<string> searchKey(input); // ==> searchKey.key_value = input;
		AVL_Node<Key<string>>* node = avl_tree.retrieve(searchKey);
		if (node == nullptr)
			cout << "No such key was found.\n";
		else
		{
			string line, word;
			SNode<string>* filename = node->data.file_name.head;
			SNode<int> *seekgVal = node->data.line_buffer.head;

			//========================== If where clause is used =====================
			if (field != "")		
			{
				//---------------- Finding the line that is to be displayed
				for (int i = 0; i < (node->data.file_name.numOfItems); i++)
				{

					ifstream fin(filename->data);
					fin.seekg(seekgVal->data);	//jumping to the index line
					getline(fin, line);	//reading the line
					stringstream str(line);
					SNode<string>* heading = fieldHeadings.head;
					while (field != heading->data)
					{	
						getline(str, word, ',');
						if (word[0] == '"') getCompleteWord(word, str);
						heading = heading->next;

					}
					getline(str, word, ','); 
					if (word == value)	// if the value of wherecaluse matches the value of the inputted field 
					{
						fin.seekg(seekgVal->data, ios::beg);	//go to the start of that line
						getline(fin, line);	// read the line
						stringstream str(line);	//convert the line to stream
						//displaying the line
						heading = fieldHeadings.head;
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
						return;	
					}
					fin.close();
					filename = filename->next;
					seekgVal = seekgVal->next;
				}
				cout << "No such field/value was found.\n";
			}

			else
			{
				//========================== Point search without Where clause =====================
				cout << "Following data has been found:\n";
				for (int i = 0; i < (node->data.file_name.numOfItems); i++)
				{

					ifstream fin(filename->data);
					fin.seekg(seekgVal->data);	//jumping to the line to which key is pointing (multiple lines if duplicates are present)
					getline(fin, line);
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
		AVL_Node<Key<string>>* node = avl_tree.retrieve(searchKey); //searchKey variable was made for the convenience of comparison in the retrieve function

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
				getline(str, word, ',');
				// fetching the line and seekg value of the line that is to be udpated
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

			//--------- saving the line in a linked list word by word
			string tempLine;
			SLinkedList<string> updateLine;
			SLinkedList<string> remainingLines;		//if newVal > oldVal, we stream out the lines below the update_line into the file as well to get rid of the "no space" issue
			ifstream fin(updateFilename);
			fin.seekg(updateLineSeekg);
			getline(fin, line);				//reading the line that is to be overriden
			stringstream str(line);
			while (getline(str, word, ','))
			{
				if (word[0] == '"') getCompleteWord(word, str);
				updateLine.insert(word);
			}
			
			if(newVal > oldVal) //---- special case
			while(getline(fin, tempLine))
			{
				remainingLines.insert(tempLine);
			}
			fin.close();
			//==============| ----- writing the line to file ------ //==============|
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
			//------- special case
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
			//-----------
			fout.close();
		}

	}

	void remove(AVL_Node<Key<string>>* delete_key) {
		SNode<string> *filename_node = delete_key->data.file_name.head; // Initializing the locations of the tuples
		SNode<int>* seekgVal = delete_key->data.line_buffer.head;
		string line, word;
		while (filename_node != NULL){
			//---------------READ THE LINE WHERE CHANGES ARE TO BE MADE----------------
			ifstream fin(filename_node->data);
			fin.seekg(seekgVal->data);
			getline(fin, line);
			fin.close();
			//----------------FILLING THE DELETED DATA WITH #----------------
			fstream fout(filename_node->data, ios::in | ios::out);
			fout.seekp(seekgVal->data);
			SNode<string>* heading = fieldHeadings.head;
			stringstream str(line);
			while (heading != NULL)
			{
				getline(str, word ,',');
				if (word[0] == '"') getCompleteWord(word, str);
				for (int i = 0; i < word.size(); i++){
					if (i == 0)
					{
						fout << "#";
					}
					else fout << '\0';
				}
				heading = heading->next;
				if (heading != NULL){fout << ',';}
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
		if (!delete_node){
			cout << "No such data found!" << endl;
			return;
		}
		remove(delete_node);
		avl_tree.Delete(delete_key, avl_tree.root);
		avl_tree.write();
	}

	void Read() {
		fillFieldType();
		avl_tree.read();
	}

	void Write() {
		avl_tree.write();
	}

	void Destroy_tree() {

		insertion_list.destroy_list();
		fieldHeadings.destroy_list();
		avl_tree.~AVLTree();
	}
};
