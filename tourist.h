#ifndef TOURIST_H_
#define TOURIST_H_

#include "Search_Book_Name.h"
#include "Search_ISBN.h"
#include "Search_Author.h"
#include "Search_Publisher.h"
#include "Book.h"

class Tourist: public Search_Book_Name, public Search_ISBN, public Search_Author, public Search_Publisher, public Book
{
private:
    string t_name;
    int t_ID;
public:
    Tourist();
    void allocate_name_tourist(int total);
    string get_tourist_name(void);
    int search_book_name(string name);
    int search_book_ISBN(ll isbn);
    std::vector<int> search_book_author(string author);
    std::vector<int> search_book_publisher(string publisher);
};
#endif