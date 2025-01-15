#ifndef SEARCH_BOOK_NAME_
#define SEARCH_BOOK_NAME_

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<map>
using std::string;
using std::pair;
using std::make_pair;

class Search_Book_Name {
private:
	static std::map<string, int> book_name;
public:
	void add_book_name(string name, int index);
	int get_index_name(string name);
	void delete_book_name(string name);
};

#endif