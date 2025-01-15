#include "tourist.h"

// string t_name;
// int t_ID;

Tourist::Tourist() { t_ID = 0; }
void Tourist::allocate_name_tourist(int total) {
    this->t_ID = ++total;
    this->t_name = "tourist" + std::to_string(total);
    return;
}
string Tourist::get_tourist_name(void) { return this->t_name; }
int Tourist::search_book_name(string name) { return get_index_name(name); }
int Tourist::search_book_ISBN(ll isbn) { return get_index_ISBN(isbn); }
std::vector<int> Tourist::search_book_author(string author) {
    return get_index_author(author);
}
std::vector<int> Tourist::search_book_publisher(string publisher) {
    return get_index_publisher(publisher);
}