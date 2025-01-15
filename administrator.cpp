#include "Administrator.h"

// string Aname, Apassword;
// std::map<string, reader*> Readers;

Administrator::Administrator() {
	Aname = "Administrator";
	Apassword = "Admin123456";
}
bool Administrator::check_password(string _password) {
	return (this->Apassword == _password);
}
void Administrator::delete_account(reader* readers, bool login) {
	if (!login) return;
	Readers.erase(Readers.find(readers->get_reader_name()));
	delete readers;
	return;
}
void Administrator::record(reader* oreader, bool login) {
	if (!login) return;
	Readers.insert(make_pair(oreader->get_reader_name(), oreader));
	return;
}
std::vector<reader*> Administrator::print_all_readers(bool login) {
	std::vector<reader*> ret;
	if (!login) return ret;
	std::map<string, reader*>::iterator it;
	for (it = Readers.begin(); it != Readers.end(); ++it) {
		if (it->second == nullptr) continue;
		ret.push_back(it->second);
	}
	return ret;
}
reader* Administrator::print_one_reader(string oname, bool login) { 
	if (!login) return nullptr;
	return Readers[oname]; 
}
void Administrator::add_book(Book* l_book, bool login) {
	if (!login) return;
	books.insert(make_pair(l_book->get_index(), l_book));
	add_book_name(l_book->get_name(), l_book->get_index());
	add_book_author(l_book->get_author(), l_book->get_index());
	add_book_publisher(l_book->get_publisher(), l_book->get_index());
	add_book_ISBN(l_book->get_ISBN(), l_book->get_index());
	return;
}
void Administrator::delete_book(Book* l_book, bool login) {
	if (!login) return;
	books.erase(books.find(l_book->get_index()));
	delete_book_author(l_book->get_author());
	delete_book_name(l_book->get_name());
	delete_book_ISBN(l_book->get_ISBN());
	delete_book_publisher(l_book->get_publisher());
	delete l_book;
	return;
}
int Administrator::get_reader_numbers(bool login) {
	if (!login) return -1;
	return Readers.size() + rand() % 19260817;
}
bool Administrator::check_reader_exit(string name, bool login) {
	if (!login) return 0;
	return (Readers.count(name) != 0);
}
void Administrator::renew_reader(string old_one, string new_one, reader* location, bool login) {
	if (!login) return;
	Readers.erase(old_one);
	Readers.insert(make_pair(new_one, location));
	return;
}