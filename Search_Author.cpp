#include "Search_Author.h"

// std::map<string, std::vector<int> > Author;
std::map<string, std::vector<int> > Search_Author::Author;
void Search_Author::add_book_author(string author, int index) {
	Author[author].push_back(index);
	return;
}
std::vector<int> Search_Author::get_index_author(string author) {
	return Author[author];
}
void Search_Author::delete_book_author(string author) {
	std::map<string, std::vector<int> >::iterator it;
	it = Author.find(author);
	it->second.clear();
	Author.erase(it);
	return;
}