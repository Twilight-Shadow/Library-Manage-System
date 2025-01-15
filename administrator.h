#ifndef ADMINISTRATOR_H_
#define ADMINISTRATOR_H_

#include "Search_Book_Name.h"
#include "Search_ISBN.h"
#include "Search_Author.h"
#include "Search_Publisher.h"
#include "reader.h"
#include "Book.h"

class Administrator : public reader
{
private:
	string Aname, Apassword;
	std::map<string, reader*> Readers;
public:
	Administrator();
	bool check_password(string _password);
	int get_reader_numbers(bool login);
	bool check_reader_exit(string name, bool login);
	void delete_account(reader* readers, bool login);
	void record(reader* oreader, bool login);
	std::vector<reader*> print_all_readers(bool login);
	reader* print_one_reader(string oname, bool login);
	void add_book(Book* l_book, bool login);
	void delete_book(Book* l_book, bool login);
	void renew_reader(string old_one, string new_one, reader* lacation, bool login);
};

#endif 
