#ifndef SEARCH_PUBLISHER_
#define SEARCH_PUBLISHER_

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

class Search_Publisher {
private:
	static std::map<string, std::vector<int> > Publisher;
public:
	void add_book_publisher(string publisher, int index);
	std::vector<int> get_index_publisher(string publisher);
	void delete_book_publisher(string publisher);
};

#endif