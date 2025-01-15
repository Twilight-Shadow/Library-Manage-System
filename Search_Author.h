#ifndef SEARCH_AUTHOR_
#define SEARCH_AUTHOR_

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
typedef long long ll;
using std::string;
using std::pair;
using std::make_pair;

class Search_Author {
private:
	static std::map<string, std::vector<int> > Author;
public:
	void add_book_author(string author, int index);
	std::vector<int> get_index_author(string author);
	void delete_book_author(string author);
};

#endif
