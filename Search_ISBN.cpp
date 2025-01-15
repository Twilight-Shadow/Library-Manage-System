#include "Search_ISBN.h"

// std::map<ll, int> ISBN;
std::map<ll, int> Search_ISBN::ISBN;
void Search_ISBN::add_book_ISBN(ll isbn, int index) {
	ISBN.insert(make_pair(isbn, index));
	return;
}
int Search_ISBN::get_index_ISBN(ll isbn) {
	return ISBN[isbn];
}
void Search_ISBN::delete_book_ISBN(ll isbn) {
	std::map<ll, int>::iterator it;
	it = ISBN.find(isbn);
	ISBN.erase(it);
	return;
}