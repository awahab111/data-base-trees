#pragma once
#include <iostream>
#include "SinglyLinkedList.h"
template <class T>
class Key {
public:
	T key_val;
	SLinkedList<int> line_buffer;
	SLinkedList<string> file_name;

	Key(){
	
	}

	Key(T x)
	{
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
	void print() {
		SNode<int>* line_node = line_buffer.head;
		fstream f1(file_name.head->data);
		string line, word;
		if (f1.is_open()){
			//cout << "FILE OPENED" << endl;
			f1.seekg(line_node->data);
			getline(f1, line);
			cout << line;
		}
	}

	int check_datatype(string word) {
		for (int i = 0; i < word.size(); i++)
		{
			if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) return 1; // returns 1 if the value is a string 
		}
		return 0; // returns 0 if the value is float 
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
		fout << "#\n";
	}
	friend ostream& operator<<(ostream& out, const Key<string>& k);
};
ostream& operator<<(ostream& out, const Key<string>& k) {
	SNode<int>* line = k.line_buffer.head;
	out << k.key_val << " ";
	while (line != NULL){
		out << line->data << " ";
		line = line->next;
	}
	out << endl;
	return out;
}
