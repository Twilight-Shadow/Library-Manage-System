#include "reader.h"
const int month_[13] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int is_year(int year) {
	if (year % 4 == 0 && year % 100 != 0) return 1;
	if (year % 400 == 0) return 1;
	return 0;
}
/*
struct TIME {
	int year, month, day;
	inline bool operator<(TIME T) const;
	inline bool operator<=(TIME T) const;
	inline TIME operator+(TIME T) const;
};
int ID;
string name, password;
struct borrowed_book {
	int index;
	TIME borrow, duration;
	inline bool operator<(borrowed_book a) const;
};
std::vector<borrowed_book> owned;
std::vector<borrowed_book> history;
*/
std::map<int, Book*> reader::books;
reader::reader() { ID = 0; }
inline bool reader::TIME::operator<(TIME T) const {
	if (this->year == T.year) {
		if (this->month == T.month) return this->day < T.day;
		else return this->month < T.month;
	}
	else return this->year < T.year;
}
inline bool reader::TIME::operator<=(TIME T) const {
	if (this->year > T.year) return 0;
	else if (this->year == T.year) {
		if (this->month > T.month) return 0;
		else if (this->month == T.month) return (this->day <= T.day);
		else return 1;
	}
	else return 1;
}
inline reader::TIME reader::TIME::operator+(TIME T) const {
	TIME res = TIME{ 0, 0, 0 };
	res.year = this->year + T.year;
	res.month = this->month + T.month;
	res.day = this->day + T.day;
	if (res.month == 2 && is_year(res.year)) {
		if (res.day > month_[res.month - 1] + 1) {
			res.day -= month_[res.month - 1] + 1;
			++res.month;
		}
	}
	else if (res.day > month_[res.month - 1]) {
		res.day -= month_[res.month - 1];
		++res.month;
	}
	if (res.month > 12) res.month -= 12, ++res.year;
	return res;
}
inline bool reader::borrowed_book::operator<(borrowed_book a) const {
	return this->index < a.index;
}
string reader::get_reader_name(void) { return this->name; }
string reader::get_reader_password(void) { return this->password; }
bool reader::check_password(string _password) {
	return (this->password == _password);
}
void reader::create_account(int total) {
	this->ID = ++total;
	this->name = "anonymous" + std::to_string(total);
	this->password = "123456";
	this->owned.clear();
	this->history.clear();
	return;
}
void reader::change_name_reader(string new_name, bool login) {
	if (!login) return;
	this->name = new_name;
	return;
}
void reader::change_password(string new_password, bool login) {
	if (!login) return;
	this->password = new_password;
	return;
}
int reader::search_book_name(string name, bool login) {
	if (!login) return -1;
	return get_index_name(name);
}
int reader::search_book_ISBN(ll isbn, bool login) {
	if (!login) return -1;
	return get_index_ISBN(isbn); 
}
std::vector<int> reader::search_book_author(string author, bool login) {
	if (!login) return std::vector<int>();
	return get_index_author(author);
}
std::vector<int> reader::search_book_publisher(string publisher, bool login) {
	if (!login) return std::vector<int>();
	return get_index_publisher(publisher);
}
void reader::borrow_book(int index, TIME T1, TIME T2, bool login) {
	if (!login) return;
	borrowed_book now;
	now = borrowed_book{ index, T1, T2 };
	owned.push_back(now);
	history.push_back(now);
	return;
}
void reader::return_book(int index, bool login) {
	if (!login) return;
	std::vector<borrowed_book>::iterator it;
	for (it = owned.begin(); it != owned.end(); ++it) {
		if (it->index == index) { owned.erase(it); break; }
	}
	return;
}
std::vector<reader::borrowed_book> reader::search_history(TIME st, TIME ed, bool login) {
	if (!login) return std::vector<reader::borrowed_book>();
	std::vector<borrowed_book> ret;
	std::sort(history.begin(), history.end());
	std::vector<borrowed_book>::iterator it;
	for (it = history.begin(); it != history.end(); ++it) {
		if (st <= it->borrow && it->borrow <= ed) ret.push_back(*it);
	}
	return ret;
}
std::vector<reader::borrowed_book> reader::search_borrowed(TIME st, TIME ed, bool login) {
	if (!login) return std::vector<reader::borrowed_book>();
	std::vector<borrowed_book> ret;
	std::sort(owned.begin(), owned.end());
	std::vector<borrowed_book>::iterator it;
	for (it = owned.begin(); it != owned.end(); ++it) {
		if (st <= it->borrow && it->borrow <= ed) ret.push_back(*it);
	}
	return ret;
}
std::vector<int> reader::book_need_return(TIME T, bool login) {
	std::vector<int> ret;
	if (!login) return ret;
	std::vector<borrowed_book>::iterator it;
	for (it = owned.begin(); it != owned.end(); ++it) {
		if ((it->borrow + it->duration) < T) ret.push_back(it->index);
	}
	return ret;
}
std::vector<Book*> reader::print_all_books(bool login) {
	if (!login) return std::vector<Book*>();
	std::vector<Book*> ret;
	std::map<int, Book*>::iterator it;
	for (it = books.begin(); it != books.end(); ++it) ret.push_back(it->second);
	return ret;
}
Book* reader::print_one_book(int index, bool login) {
	if (!login) return nullptr;
	return books[index];
}
int reader::get_ID(void) { return this->ID; }
std::vector<reader::borrowed_book> reader::search_history(bool login) {
	if (!login) return std::vector<reader::borrowed_book>();
	return history;
}
std::vector<reader::borrowed_book> reader::search_borrowed(bool login) {
	if (!login) return std::vector<reader::borrowed_book>();
	return owned;
}
void reader::read_text_reader(std::ifstream& in) {
	int num = 0; string inp = "";
	in >> num; this->ID = num;
	in >> inp; this->name = inp;
	in >> inp; this->password = inp;
	in >> num;
	for (int i = 1; i <= num; ++i) {
		borrowed_book nov;
		in >> nov.index;
		in >> nov.borrow.year >> nov.borrow.month >> nov.borrow.day;
		in >> nov.duration.year >> nov.duration.month >> nov.duration.day;
		this->history.push_back(nov);
	}
	in >> num;
	for (int i = 1; i <= num; ++i) {
		borrowed_book nov;
		in >> nov.index;
		in >> nov.borrow.year >> nov.borrow.month >> nov.borrow.day;
		in >> nov.duration.year >> nov.duration.month >> nov.duration.day;
		this->owned.push_back(nov);
	}
	return;
}
string reader::get_book_name_index(int index, bool login) {
	if (!login) return "No Access";
	return books[index]->get_name();
}
void reader::clear_owned(bool login) {
	if (!login) return;
	owned.clear();
	return;
}
void reader::clear_history(bool login) {
	if (!login) return;
	history.clear();
	return;
}
int reader::search_history_size(bool login) {
	if (!login) return -1;
	return int(history.size());
}
