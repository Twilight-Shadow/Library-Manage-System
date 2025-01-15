#ifndef READER_H_
#define READER_H_

#include "Search_Book_Name.h"
#include "Search_ISBN.h"
#include "Search_Author.h"
#include "Search_Publisher.h"
#include "Book.h"

class reader: public Search_Book_Name, public Search_ISBN, public Search_Author, public Search_Publisher, public Book
{
public:
	struct TIME {
		int year, month, day;
		inline bool operator<(TIME T) const;
		inline bool operator<=(TIME T) const;
		inline TIME operator+(TIME T) const;
	};
	struct borrowed_book {
		int index;
		TIME borrow, duration;
		inline bool operator<(borrowed_book a) const;
	};
protected:
	int ID;
	string name, password;
	std::vector<borrowed_book> owned;
	std::vector<borrowed_book> history;
	static std::map<int, Book*> books;
public:
	reader();
	int get_ID(void);
	string get_reader_name(void);
	string get_reader_password(void);
	bool check_password(string _password);
	void create_account(int total);
	void change_name_reader(string new_name, bool login);
	void change_password(string new_password, bool login);
	int search_book_name(string name, bool login);
	int search_book_ISBN(ll isbn, bool login);
	std::vector<int> search_book_author(string author, bool login);
	std::vector<int> search_book_publisher(string publisher, bool login);
	void borrow_book(int index, TIME T1, TIME T2, bool login);
	void return_book(int index, bool login);
	std::vector<borrowed_book> search_history(TIME st, TIME ed, bool login);
	std::vector<borrowed_book> search_history(bool login);
	std::vector<borrowed_book> search_borrowed(TIME st, TIME ed, bool login);
	std::vector<borrowed_book> search_borrowed(bool login);
	std::vector<int> book_need_return(TIME T, bool login);
	std::vector<Book*> print_all_books(bool login);
	Book* print_one_book(int index, bool login);
	void read_text_reader(std::ifstream& in);
	string get_book_name_index(int index, bool login);
	void clear_owned(bool login);
	void clear_history(bool login);
	int search_history_size(bool login);
};

#endif