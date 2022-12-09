#pragma once
#include <iostream>
template <class T>
class Key {
public:
	T key_val;
	int line_num;
	string file_name;
	int seekgValue;

	Key(){}

	Key(T x, int line, string f, int seekgVal) {

		key_val = x;
		line_num = line;
		file_name = f;
		seekgValue = seekgVal;
	}

	void print() {
		fstream f1(file_name);
		string line, word;
		if (f1.is_open()){
			//cout << "FILE OPENED" << endl;
			for (int i = 0; i < line_num; i++){
				getline(f1, line);
			}
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
	void fileoperator(ostream & fout) {
		fout << key_val << '&' << line_num << '&' << file_name << '\n';
	}
	friend ostream& operator<<(ostream& out, const Key<string>& k);
};
ostream& operator<<(ostream& out, const Key<string>& k) {
	out << k.key_val;
	return out;
}
