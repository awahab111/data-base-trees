#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "SinglyLinkedList.h"
template <class T>
class Key {
public:
	T key_val;
	SLinkedList<int> line_buffer;
	SLinkedList<string> file_name;

	Key(){}

	Key(T x){
		key_val = x;
	}

	Key(T x, int seekgVal, string f) {

		key_val = x;
		line_buffer.insert(seekgVal);
		file_name.insert(f);
	}

	void update_key(int seekgVal, string f) {
		line_buffer.insert(seekgVal);
		file_name.insert(f);
	}

	void print(SLinkedList<string>& fieldHeadings) {
		SNode<int>* seekgVal = line_buffer.head;
		SNode<string>* filename = file_name.head;
		string line, word;
		while (filename != NULL){
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
		word += "\"";
		str.get();// to skip the comma-
	}

	bool operator<(Key val) {
		if (!check_datatype(key_val)){ // If the string is float then we need to convert string to a float and then compare 
			float t1 = stof(key_val);
			float t2 = stof(val.key_val);
			if (t1 < t2)return true;
			else return 0;
		}
		if (key_val < val.key_val) { return true; }
		else return false;
	}

	bool operator>(Key val) {
		if (!check_datatype(key_val)) { // If the string is float then we need to convert string to a float and then compare 
			float t1 = stof(key_val);
			float t2 = stof(val.key_val);
			if (t1 > t2)return true;
			else return 0;
		}
		if (key_val > val.key_val) { return true; }
		else return false;
	}

	bool operator==(Key val) {
		if (key_val == val.key_val) { return true; }
		else return false;
	}

	void fileoperator(ostream & fout) {
		SNode<int> *line = line_buffer.head;
		SNode<string>* name = file_name.head;
		fout << key_val << ',';
		while (line != NULL){
			fout << line->data << ',';
			line = line->next;
		}
		fout << "#," ;
		while (name != NULL){
			fout << name->data << ',';
			name = name->next;
		}
		fout << "#";
	}

	friend ostream& operator<<(ostream& out, const Key<string>& k);
};
ostream& operator<<(ostream& out, const Key<string>& k) {
	SNode<int>* line = k.line_buffer.head;
	out << k.key_val << " ";
	return out;
}
