
#include "AVL_Tree.h"
#include "SinglyLinkedList.h"
#include <algorithm>
#include <sstream>

using namespace std;

int check_datatype(string word) {
	for (int  i = 0; i < word.size(); i++)
	{
		if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) return 1; // returns 1 if the value is a string 
	}
	return 0; // returns 0 if the value is float 
}

int getFieldType(string file_name)
{
	fstream fin(file_name, ios:: in);
	string line, word;
	int field;
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

void getCompleteWord(string& word, stringstream& str)
{
	string temp;
	getline(str, temp, '"');
	word += temp;
	str.get();// to skip the comma-
	//str.get();// to skip the comma-

}

int getDataType(string file_name, int field_type)
{
	fstream fin(file_name, ios::in);
	string line, word;
	int data_type;
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


void show_data(string file_name, int field_type) {
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
				if (i == field_type)
				{
					cout << word << endl;
					break;
				}

			}
		}
		
	}
	fin.close();
}

template <class T>
void createLinkedList(string file_name, int field_type, int data_type)
{
	SLinkedList<float> float_list;
	SLinkedList<string> string_list;
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
					if (data_type == 0)
					{
						float key = std::stof(word);
						float_list.insert(key);
					}
					else
						string_list.insert(word);
					break; 
				}

			}
		}

	}
	list.print();
	fin.close();

}

void AVL_Tree_Indexing()
{
	string file_name = "data_1.csv";
	int field_type = getFieldType(file_name);
	//cout << "field_type: " << field_type << endl;
	int data_type = getDataType(file_name, field_type);
	//cout << "data_type: " << data_type << endl;
	//show_data(file_name, field_type);

	if (data_type == 0) //if data type is int/flaot
	{
		SLinkedList<float> list;
		createLinkedList<float>(file_name, list, field_type, data_type);

	}

	else 
	{
		SLinkedList<string> list;
		createLinkedList<string>(file_name, list, field_type, data_type);
	}


	
}


int main()
{
	AVL_Tree_Indexing();

}