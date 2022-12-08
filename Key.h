#pragma once
#include <iostream>
template <class T>
class Key {
public:
	T key_val;
	int line_num;
	string file_name;
	Key(T x, int line, string f) {
		key_val = x;
		line_num = line;
		file_name = f;
	}
	void print() {
		fstream f1(file_name);
		string line, word;
		if (f1.is_open()){
			cout << "FILE OPENED" << endl;
			for (int i = 0; i < line_num; i++){
				getline(f1, line);
			}
			getline(f1, line);
			cout << line;
		}
	}
};