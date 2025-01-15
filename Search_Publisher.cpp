#include "Search_Publisher.h"

// std::map<string, std::vector<int> > Publisher;
std::map<string, std::vector<int> > Search_Publisher::Publisher;
void Search_Publisher::add_book_publisher(string publisher, int index) {
	Publisher[publisher].push_back(index);
	return;
}
std::vector<int> Search_Publisher::get_index_publisher(string publisher) {
	return Publisher[publisher];
}
void Search_Publisher::delete_book_publisher(string publisher) {
	std::map<string, std::vector<int> >::iterator it;
	it = Publisher.find(publisher);
	it->second.clear();
	Publisher.erase(it);
	return;
}