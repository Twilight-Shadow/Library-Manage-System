#ifndef SEARCH_ISBN_
#define SEARCH_ISBN_

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<map>
typedef long long ll;
using std::string;
using std::pair;
using std::make_pair;

class Search_ISBN {
private:
	static std::map<ll, int> ISBN;
public:
	void add_book_ISBN(ll isbn, int index);
	int get_index_ISBN(ll isbn);
	void delete_book_ISBN(ll isbn);
};

#endif
