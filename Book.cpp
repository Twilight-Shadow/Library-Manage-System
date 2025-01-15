#include "Book.h"
/*
int index;
long long ISBN;
string book_name, author;
string publisher, published_date;
string price, pages, description;
std::set<Book> all_book;
*/

Book::Book() { index = 0, heat = 0, ISBN = 0ll;  }
bool Book::operator<(const Book b) const { return (this->index < b.index); }
void Book::read_text_src(std::ifstream& in){
	char buff[4096];
	long long n = 0, numbers = 0;
	string s_buff = "";
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) numbers = (numbers << 1) + (numbers << 3) + (buff[i] ^ 48);
	this->index = numbers;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) numbers = (numbers << 1) + (numbers << 3) + (buff[i] ^ 48);
	this->ISBN = numbers;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->book_name = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->author = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->publisher = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->published_date = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->price = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->pages = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) s_buff.push_back(buff[i]);
	this->description = s_buff;
	n = 0, numbers = 0, s_buff.clear();
	in.getline(buff, 4095, '\n');
	n = strlen(buff);
	for (int i = 0; i < n; ++i) numbers = (numbers << 1) + (numbers << 3) + (buff[i] ^ 48);
	this->heat = numbers;
	return;
}
int Book::get_index(void) { return this->index; }
ll Book::get_ISBN(void) { return this->ISBN; }
string Book::get_name(void) { return this->book_name; }
string Book::get_author(void) { return this->author; }
string Book::get_publisher(void) { return this->publisher; }
string Book::get_published_date(void) { return this->published_date; }
string Book::get_price(void) { return this->price; }
string Book::get_pages(void) { return this->pages; }
string Book::get_description(void) { return this->description; }
void Book::change_ISBN(ll now, bool login) {
	if (!login) return;
	this->ISBN = now;
	return;
}
void Book::change_name(string now, bool login) { 
	if (!login) return;
	this->book_name = now;
	return; 
}
void Book::change_author(string now, bool login) {
	if (!login) return;
	this->author = now; 
	return; 
}
void Book::change_publisher(string now, bool login) {
	if (!login) return;
	this->publisher = now; 
	return; 
}
void Book::change_published_date(string now, bool login) { 
	if (!login) return;
	this->published_date = now; 
	return; 
}
void Book::change_price(string now, bool login) {
	if (!login) return;
	this->price = now;
	return; 
}
void Book::change_pages(string now, bool login) {
	if (!login) return;
	this->pages = now; 
	return; 
}
void Book::change_description(string now, bool login) { 
	if (!login) return;
	this->description = now; 
	return; 
}
void Book::change_ID(int ID, bool login) {
	if (!login) return;
	this->index = ID;
	return;
}
void Book::add_heat(void) {
	this->heat = this->heat + 1;
	return;
}
int Book::get_heat(void) { return this->heat; }