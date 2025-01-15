#ifndef BOOK_H_
#define BOOK_H_

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<fstream>
#include<set>
using std::string;
typedef long long ll;

class Book {
private:
	int index, heat;
	long long ISBN;
	string book_name, author;
	string publisher, published_date;
	string price, pages, description;
	bool operator<(const Book b) const;
public:
	Book();
	void read_text_src(std::ifstream& in);
	int get_index(void);
	ll get_ISBN(void);
	string get_name(void);
	string get_author(void);
	string get_publisher(void);
	string get_published_date(void);
	string get_price(void);
	string get_pages(void);
	string get_description(void);
	void change_ID(int ID, bool login);
	void change_ISBN(ll now, bool login);
	void change_name(string now, bool login);
	void change_author(string now, bool login);
	void change_publisher(string now, bool login);
	void change_published_date(string now, bool login);
	void change_price(string now, bool login);
	void change_pages(string now, bool login);
	void change_description(string now, bool login);
	void add_heat(void);
	int get_heat(void);
};

#endif