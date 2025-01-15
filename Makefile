.PHONY: clean
main: main.o administrator.o Book.o reader.o Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o tourist.o
	g++ main.o administrator.o Book.o reader.o Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o tourist.o -o LMS
main.o:
	g++ main.cpp -o main.o
administrator.o: administrator.cpp administrator.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o reader.o Book.o
	g++ administrator.cpp administrator.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o reader.o Book.o -o administrator.o
reader.o: reader.cpp reader.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o tourist.o Book.o
	g++ reader.cpp reader.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o tourist.o Book.o -o reader.o
tourist.o: tourist.cpp tourist.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o Book.o
	g++ tourist.cpp tourist.h Search_Author.o Search_Book_Name.o Search_ISBN.o Search_Publisher.o Book.o -o tourist.o
Book.o: Book.cpp Book.h
	g++ Book.cpp Book.h -o Book.o
Search_Author.o: Search_Author.cpp Search_Author.h
	g++ Search_Author.cpp Search_Author.h -o Search_Author.o
Search_Book_Name.o: Search_Book_Name.cpp Search_Book_Name.h
	g++ Search_Book_Name.cpp Search_Book_Name.h -o Search_Book_Name.o
Search_ISBN.o: Search_ISBN.cpp Search_ISBN.h
	g++ Search_ISBN.cpp Search_ISBN.h -o Search_ISBN.o
Search_Publisher.o: Search_Publisher.cpp Search_Publisher.h
	g++ Search_Publisher.cpp Search_Publisher.h -o Search_Publisher.o
clean:
	rm -f *.o
	