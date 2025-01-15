#include "Search_Book_Name.h"

// std::map<string, int> book_name;
std::map<string, int> Search_Book_Name::book_name;
void Search_Book_Name::add_book_name(string name, int index) {
	book_name.insert(make_pair(name, index));
	return;
}
int Search_Book_Name::get_index_name(string name) {
	return book_name[name];
}
void Search_Book_Name::delete_book_name(string name) {
	std::map<string, int>::iterator it;
	it = book_name.find(name);
	book_name.erase(it);
	return;
}