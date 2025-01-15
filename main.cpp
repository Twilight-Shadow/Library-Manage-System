#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<fstream>
#include<Windows.h>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<iomanip>
#include<queue>
#include "Administrator.h"
#include "reader.h"
#include "tourist.h"
#include "Book.h"
using std::string;
Administrator Admin;
template <class I> inline void read(I& x) {
	x = 0; int f = 1; char ch;
	do { ch = getchar(); if (ch == '-') f = -1; } while (ch < '0' || ch > '9');
	do { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); } while (ch >= '0' && ch <= '9');
	x *= f; return;
}
void Admin_up_screen(int y, int m, int d) {
	system("cls");
	printf("欢迎！Administrator, 时间：%04d/%02d/%02d , 输入 E 登出\n", y, m, d);
	return;
}
void Tourist_up_screen(Tourist& t, int y, int m, int d) {
	system("cls");
	printf("欢迎！");
	std::cout << t.get_tourist_name() << ", ";
	printf("时间：%04d/%02d/%02d , 输入 E 登出\n", y, m, d);
	return;
}
void Reader_up_screen(reader* r, int y, int m, int d) {
	system("cls");
	printf("欢迎！");
	std::cout << r->get_reader_name() << ", ";
	printf("时间：%04d/%02d/%02d , 输入 E 登出\n", y, m, d);
	return;
}
template<typename I> I _min(I a, I b) { return a < b ? a : b; }
template<typename I> I _max(I a, I b) { return a > b ? a : b; }
void print_lasted_news_1(bool login) {
	if (!login) return;
	std::vector<Book*> ret = Admin.print_all_books(login);
	std::set<pair<int, string> > now_heat;
	for (Book* i : ret) {
		if (now_heat.size() < 10) now_heat.insert(make_pair(i->get_heat(), i->get_name()));
		else if (i->get_heat() > now_heat.begin()->first) {
			now_heat.erase(now_heat.begin());
			now_heat.insert(make_pair(i->get_heat(), i->get_name()));
		}
	}
	int nocnt = 0;
	for (auto i = now_heat.rbegin(); i != now_heat.rend(); ++i) {
		++nocnt;
		printf("%2d. ", nocnt);
		std::cout << std::setw(55) << i->second << "     ";
		std::cout << "被借阅 " << i->first << " 次\n";
	}
	return;
}
void print_lasted_news_2(bool login) {
	if (!login) return;
	std::vector<reader*> ret = Admin.print_all_readers(login);
	std::set<pair<int, string> > stronger;
	for (reader* i : ret) {
		if (stronger.size() < 10) stronger.insert(make_pair(i->search_history_size(login), i->get_reader_name()));
		else if (i->search_history_size(login) > stronger.begin()->first) {
			stronger.erase(stronger.begin());
			stronger.insert(make_pair(i->search_history_size(login), i->get_reader_name()));
		}
	}
	int nocnt = 0;
	for (auto i = stronger.rbegin(); i != stronger.rend(); ++i) {
		++nocnt;
		printf("%2d. ", nocnt);
		std::cout << std::setw(26) << i->second << ' ';
		std::cout << "已借阅 " << i->first << " 次\n";
	}
	return;
}
void print_lasted_news_3(bool login) {
	if (!login) return;
	std::vector<Book*> ret = Admin.print_all_books(login);
	std::set<pair<string, string> > new_pub;
	for (Book* i : ret) {
		if (new_pub.size() < 10) new_pub.insert(make_pair(i->get_published_date(), i->get_name()));
		else if (i->get_published_date() > new_pub.begin()->first) {
			new_pub.erase(new_pub.begin());
			new_pub.insert(make_pair(i->get_published_date(), i->get_name()));
		}
	}
	int nocnt = 0;
	for (auto i = new_pub.rbegin(); i != new_pub.rend(); ++i) {
		++nocnt;
		printf("%2d. ", nocnt);
		std::cout << std::setw(55) << i->second << "      ";
		std::cout << "出版日期： " << i->first << '\n';
	}
	return;
}
int main() {
	std::ifstream collect;
	srand(time(0));
	collect.open("src.txt", std::ios::in);
	int cnt = 0;
	while (!collect.eof()) {
		Book* now = new Book;
		now->read_text_src(collect);
		Admin.add_book(now, 1);
		++cnt;
		printf("Successfully loading book #%d\n", cnt);
	}
	Admin.delete_book(Admin.print_one_book(0, 1), 1);
	collect.close();
	collect.open("readers.txt", std::ios::in);
	cnt = 0;
	while (!collect.eof()) {
		reader* now = new reader;
		now->read_text_reader(collect);
		Admin.record(now, 1);
		++cnt;
		printf("Successfully loading reader #%d\n", cnt);
	}
	Admin.delete_account(Admin.print_one_reader("", 1), 1);
	Main_page:
	system("cls");
	time_t local_time;
	time(&local_time);
	tm temp_current_date;
	localtime_s(&temp_current_date, &local_time);
	reader::TIME current_date;
	current_date.year = temp_current_date.tm_year + 1900;
	current_date.month = temp_current_date.tm_mon + 1;
	current_date.day = temp_current_date.tm_mday;
	printf(" _____________________________________________________________ \n");
	printf("|                                                             |\n");
	printf("|                                                             |\n");
	printf("|                    欢迎来到图书管理系统！                   |\n");
	printf("|                       Made by Shadow                        |\n");
	printf("|                                                             |\n");
	printf("|                       请选择登录模式：                      |\n");
	printf("|            A：管理员登录  R：读者登录  T:游客登录           |\n");
	printf("|                                                             |\n");
	printf("|                         或按 E 退出                         |\n");
	printf("|                                                             |\n");
	printf("|                      [输入后请按回车键]                     |\n");
	printf("|                                                             |\n");
	printf("|                       时间：%04d/%02d/%02d                      |\n", current_date.year, current_date.month, current_date.day);
	printf("|                                                             |\n");
	printf(" ------------------------------------------------------------- \n");
	string action;
	std::cin >> action;
	int login_statu = -1; // 1 for admin, 2 for reader, 0 for tourist
	if (action[0] == 'E') goto END;
	else if (action[0] == 'A') {
		system("cls");
		int tried = 0;
		while (++tried <= 3) {
			if (tried == 1) puts("请输入管理员密码：");
			else puts("请重新输入管理员密码：");
			string input_password = "";
			char asc;
			while ((asc = _getch()) != '\r') {
				if (asc != '\b') {
					input_password.push_back(asc);
					putchar('*');
				}
				else if(input_password.size()){
					putchar('\b');
					putchar(' ');
					putchar('\b');
					input_password.pop_back();
				}
				std::cout.flush();
			}
			puts("");
			if (Admin.check_password(input_password)) {
				login_statu = 1;
				puts("您已成功登录！（身份：管理员）");
				break;
			}
			else {
				puts("登录失败！");
				Sleep(700);
				system("cls");
			}
		}
		if (login_statu == -1) {
			puts("请稍后再试！");
			goto Main_page;
		}
		Start_page_1:
		Admin_up_screen(current_date.year, current_date.month, current_date.day);
		puts("功能：");
		puts("1.管理读者");
		puts("2.管理图书");
		puts("3.查看最新信息");
		puts("输入对应序号/字母以进入");
		std::cin >> action;
		if (action[0] == 'E' || action[0] == 'B') {
			login_statu = -1;
			goto Main_page;
		}
		else if (action[0] == '1') {
			Manage_Reader:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.查询所有读者信息(10人一页)");
			puts("2.查找读者(用户名)");
			puts("3.更改账户信息");
			puts("4.创建账户");
			puts("输入对应序号/字母以进入, 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
			Roll_page_reader:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				std::vector<reader*> ret = Admin.print_all_readers((login_statu == 1));
				static int tot_page_r = 0;
				for (int i = tot_page_r * 10; i < _min((tot_page_r + 1) * 10, (int)ret.size()); ++i) {
					std::cout << i + 1 << ". ";
					std::cout << std::setw(15) << ret[i]->get_reader_name() << ' ';
					std::cout << std::setw(25) << ret[i]->get_reader_password() << '\n';
				}
				int all = ret.size() / 10;
				printf("第 %d 页， 共 %d 页\n", tot_page_r + 1, all + 1);
				puts("输入 L 进入上一页，输入 R 进入下一页, 输入 B 返回上一级");
				std::cin >> action;
				if (action[0] == 'L') {
					if (tot_page_r == 0) goto Wrong_roll_page_reader;
					--tot_page_r;
					goto Roll_page_reader;
				}
				else if (action[0] == 'R') {
					if (tot_page_r == all) goto Wrong_roll_page_reader;
					++tot_page_r;
					goto Roll_page_reader;
				}
				else if (action[0] == 'B') goto Manage_Reader;
				else if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else {
					Wrong_roll_page_reader:
					puts("错误！");
					Sleep(1000);
					goto Roll_page_reader;
				}
			}
			else if (action[0] == '2') {
				See_one_reader:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的用户名：");
				std::cin >> action;
				reader* result = Admin.print_one_reader(action, (login_statu == 1));
				if (result == nullptr) {
					puts("无此用户！");
					Sleep(1000);
					goto Manage_Reader;
				}
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("该用户的信息为：");
				printf("用户名："); std::cout << result->get_reader_name() << '\n';
				printf("密码："); std::cout << result->get_reader_password() << '\n';
				puts("1.查看所有当前借阅记录");
				puts("2.查看指定时间内的借阅记录");
				puts("3.查看所有借阅历史");
				puts("4.查看指定时间内的借阅历史");
				puts("输入数字以继续，输入 B 返回上一级：");
				std::cin >> action;
				std::vector<reader::borrowed_book> ret;
				if (action[0] == '1') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					ret = result->search_borrowed((login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("当前无借阅图书");
					else {
						printf("当前借阅的图书为：\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
					}
				}
				else if (action[0] == '2') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					puts("请输入起始时间(年/月/日)和终止时间(年/月/日), 数字之间以空格分隔");
					reader::TIME st, et;
					read(st.year), read(st.month), read(st.day);
					read(et.year), read(et.month), read(et.day);
					ret = result->search_borrowed(st, et, (login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("当前无借阅图书");
					else {
						printf("当前借阅的图书为：\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
					}
				}
				else if (action[0] == '3') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					ret = result->search_history((login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("当前无借阅历史！");
					else {
						printf("以往借阅的图书为：\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
						puts("");
					}
				}
				else if (action[0] == '4') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					puts("请输入起始时间(年/月/日)和终止时间(年/月/日), 数字之间以空格分隔");
					reader::TIME st, et;
					read(st.year), read(st.month), read(st.day);
					read(et.year), read(et.month), read(et.day);
					ret = result->search_history(st, et, (login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("当前无借阅历史！");
					else {
						printf("以往借阅的图书为：\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
						puts("");
					}
				}
				else if (action[0] == 'B') goto Manage_Reader;
				else if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else {
					puts("错误！");
					Sleep(1000);
					goto See_one_reader;
				}
				puts("");
				puts("输入 C 继续查询，输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto See_one_reader;
				else if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else goto Manage_Reader;
			}
			else if (action[0] == '3') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要管理的用户名：");
				string name__;
				std::cin >> name__;
				reader* result = Admin.print_one_reader(name__, (login_statu == 1));
				if (result == nullptr) {
					puts("无此用户！");
					Sleep(1000);
					goto Manage_Reader;
				}
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("该用户的信息为：");
				printf("用户名："); std::cout << result->get_reader_name() << '\n';
				printf("密码：  "); std::cout << result->get_reader_password() << '\n';
				puts("\n输入 C1 更改用户名");
				puts("输入 C2 更改密码");
				puts("输入 C3 清除当前借阅记录");
				puts("输入 C4 清除借阅历史");
				puts("输入 C5 删除账户");
				puts("输入 B 返回");
				std::cin >> action;
				if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else if (action[0] == 'B') goto Manage_Reader;
				string new_things;
				if (action[1] == '1') {
					puts("请输入新的用户名：");
					std::cin >> new_things;
					result->change_name_reader(new_things, (login_statu == 1));
					Admin.renew_reader(name__, new_things, result, (login_statu == 1));
					puts("修改成功！");
				}
				else if (action[1] == '2') {
					puts("请输入新的密码：");
					std::cin >> new_things;
					result->change_password(new_things, (login_statu == 1));
					puts("修改成功！");
				}
				else if (action[1] == '3') {
					result->clear_owned((login_statu == 1));
					puts("清空成功！");
				}
				else if (action[1] == '4') {
					result->clear_history((login_statu == 1));
					puts("清空成功！");
				}
				else if (action[1] == '5') {
					Admin.delete_account(Admin.print_one_reader(name__, (login_statu == 1)), (login_statu == 1));
					puts("删除成功！");
				}
				else {
					puts("错误！");
					goto Manage_Reader;
				}
				puts("\n2秒后返回上一页");
				Sleep(2000);
				goto Manage_Reader;
			}
			else if (action[0] == '4') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				reader* new_reader = new reader;
				new_reader->create_account(Admin.get_reader_numbers((login_statu == 1)));
				printf("创建成功！\n");
				printf("当前的用户名为： ");
				std::cout << new_reader->get_reader_name() << '\n';
				printf("当前的密码为： 123456\n");
				Admin.record(new_reader, (login_statu == 1));
				Sleep(2000);
				goto Manage_Reader;
			}
			else if (action[0] == 'B') goto Start_page_1;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Manage_Reader;
			}
		}
		else if (action[0] == '2') {
			Manage_book:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.查询所有图书信息(20本一页)");
			puts("2.查询图书(书名)");
			puts("3.查询图书(作者)");
			puts("4.查询图书(ISBN)");
			puts("5.查询图书(出版社)");
			puts("6.更改图书信息");
			puts("输入对应序号/字母以进入， 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Roll_page_b:
				system("cls");
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				std::vector<Book*> libr = Admin.print_all_books(login_statu == 1);
				static int tot_page_b = 0;
				int all = libr.size() / 20;
				for (int i = tot_page_b * 20; i < _min((tot_page_b + 1) * 20, (int)libr.size()); ++i) {
					std::cout << std::setw(50) << libr[i]->get_name() << ' ';
					std::cout << std::setw(50) << libr[i]->get_author() << ' ';
					puts("");
				}
				printf("第 %d 页， 共 %d 页\n", tot_page_b + 1, all + 1);
				puts("输入 L 进入上一页，输入 R 进入下一页, 输入 B 返回上一级");
				std::cin >> action;
				if (action[0] == 'L') {
					if (tot_page_b == 0) goto Wrong_roll_page_book;
					--tot_page_b;
					goto Roll_page_b;
				}
				else if (action[0] == 'R') {
					if (tot_page_b == all) goto Wrong_roll_page_book;
					++tot_page_b;
					goto Roll_page_b;
				}
				else if (action[0] == 'B') goto Manage_book;
				else if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else {
					Wrong_roll_page_book:
					puts("错误！");
					Sleep(1000);
					goto Roll_page_b;
				}
			}
			else if (action[0] == '2') {
				Search_book_name_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的书名！");
				std::cin >> action;
				int idx = Admin.search_book_name(action, (login_statu == 1));
				Book* ret = Admin.print_one_book(idx, (login_statu == 1));
				if (ret == nullptr) {
					puts("错误！");
					Sleep(1000);
					goto Manage_book;
				}
				printf("ISBN号： "); std::cout << ret->get_ISBN() << '\n';
				printf("作者： "); std::cout << ret->get_author() << '\n';
				printf("出版社： "); std::cout << ret->get_publisher() << '\n';
				printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
				printf("页数："); std::cout << ret->get_pages() << '\n';
				printf("价格："); std::cout << ret->get_price() << '\n';
				printf("简述： "); std::cout << ret->get_description() << '\n';
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_name_admin;
				else goto Manage_book;
			}
			else if (action[0] == '3') {
				Search_book_author_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的作者！");
				std::cin >> action;
				std::vector<int> ret = Admin.search_book_author(action, (login_statu == 1));
				for (int i : ret) {
					Book* u = Admin.print_one_book(i, (login_statu == 1));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_publisher() << '\n';
				}
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_author_admin;
				else goto Manage_book;
			}
			else if (action[0] == '4') {
				Search_book_ISBN_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的ISBN号");
				ll isbn = 0;
				std::cin >> isbn;
				int idx = Admin.search_book_ISBN(isbn, (login_statu == 1));
				Book* ret = Admin.print_one_book(idx, (login_statu == 1));
				if (ret == nullptr) {
					puts("错误！");
					Sleep(1000);
					goto Manage_book;
				}
				printf("作者： "); std::cout << ret->get_author() << '\n';
				printf("出版社： "); std::cout << ret->get_publisher() << '\n';
				printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
				printf("页数："); std::cout << ret->get_pages() << '\n';
				printf("价格："); std::cout << ret->get_price() << '\n';
				printf("描述： "); std::cout << ret->get_description() << '\n';
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_ISBN_admin;
				else goto Manage_book;
			}
			else if (action[0] == '5') {
				Search_book_publisher_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的出版社！");
				std::cin >> action;
				std::vector<int> ret = Admin.search_book_publisher(action, (login_statu == 1));
				for (int i : ret) {
					Book* u = Admin.print_one_book(i, (login_statu == 1));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_author() << '\n';
				}
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_publisher_admin;
				else goto Manage_book;
			}
			else if (action[0] == '6') {
				Change_book_info:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("1.更改书籍名称");
				puts("2.更改书籍ISBN号");
				puts("3.更改书籍作者");
				puts("4.更改书籍出版社");
				puts("5.更改书籍出版日期");
				puts("6.更改书籍价格");
				puts("7.更改书籍页数");
				puts("8.更改书籍简述");
				puts("9.增添图书");
				puts("10.删除图书");
				string name__, __name;
				std::cin >> action;
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				if (action[0] == 'B') goto Manage_book;
				if (action[0] == '1' && action[1] != '0') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的书籍名称：");
					std::cin >> __name;
					book__->change_name(__name, (login_statu == 1));
				}
				else if (action[0] == '2') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的ISBN号：");
					ll isbn__ = 0;
					std::cin >> isbn__;
					book__->change_ISBN(isbn__, (login_statu == 1));
				}
				else if (action[0] == '3') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的作者名：");
					std::cin >> __name;
					book__->change_author(__name, (login_statu == 1));
				}
				else if (action[0] == '4') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的出版社：");
					std::cin >> __name;
					book__->change_publisher(__name, (login_statu == 1));
				}
				else if (action[0] == '5') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的出版日期：");
					std::cin >> __name;
					book__->change_published_date(__name, (login_statu == 1));
				}
				else if (action[0] == '6') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的价格");
					std::cin >> __name;
					book__->change_price(__name, (login_statu == 1));
				}
				else if (action[0] == '7') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的页数");
					std::cin >> __name;
					book__->change_pages(__name, (login_statu == 1));
				}
				else if (action[0] == '8') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("请输入新的简述");
					std::cin >> __name;
					book__->change_description(__name, (login_statu == 1));
				}
				else if (action[0] == '9') {
					puts("请输入需要添加的图书信息，顺序及格式如下(不同信息之间以换行分割)：");
					puts("编号(不可为0)，名称，ISBN号，作者，出版社，出版日期(年/月/日)，价格，页数，简述");
					ll now_in; Book* now_booking = new Book;
					std::cin >> now_in;
					now_booking->change_ID(now_in, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_name(name__, (login_statu == 1));
					std::cin >> now_in;
					now_booking->change_ISBN(now_in, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_author(name__, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_publisher(name__, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_published_date(name__, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_price(name__, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_pages(name__, (login_statu == 1));
					std::cin >> name__;
					now_booking->change_description(name__, (login_statu == 1));
					Admin.add_book(now_booking, (login_statu == 1));
				}
				else if (action[0] == '1' && action[1] == '0') {
					puts("请输入当前书籍名称: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					if (book__ == nullptr) {
						puts("该书籍不存在！");
						goto Change_book_info;
					}
					Admin.delete_book(book__, (login_statu == 1));
				}
				else {
					puts("错误！");
					Sleep(1000);
					goto Manage_book;
				}
				puts("修改成功！2秒后返回上一页");
				Sleep(2000);
				goto Manage_book;
			}
			else if (action[0] == 'B') goto Start_page_1;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_1;
			}
		}
		else if (action[0] == '3') {
			Show_news_admin:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.借阅次数前十的图书");
			puts("2.借阅次数前十的读者");
			puts("3.最新出版前十的图书");
			puts("输入对应序号/字母以进入， 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				print_lasted_news_1(login_statu == 1);
			}
			else if (action[0] == '2') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				print_lasted_news_2(login_statu == 1);
			}
			else if (action[0] == '3') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				print_lasted_news_3(login_statu == 1);
			}
			else if (action[0] == 'B') goto Start_page_1;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_1;
			}
			puts("输入 B 返回上一级");
			std::cin >> action;
			goto Show_news_admin;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("错误！");
			Sleep(1000);
			goto Start_page_1;
		}
	}
	else if (action[0] == 'T') {
		Tourist tourist;
		srand(time(0));
		tourist.allocate_name_tourist(rand() % 19190810 + 100000000);
		login_statu = 0;
		Start_page_2:
		Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
		puts("1.查询所有图书信息(20本一页)");
		puts("2.查询图书(书名)");
		puts("3.查询图书(作者)");
		puts("4.查询图书(ISBN)");
		puts("5.查询图书(出版社)");
		puts("6.查看最新信息");
		puts("输入对应序号/字母以进入");
		std::cin >> action;
		if (action[0] == '1') {
			Roll_page_t:
			system("cls");
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			std::vector<Book*> libr = Admin.print_all_books(login_statu == 0);
			static int tot_page_t = 0;
			int all = libr.size() / 20;
			for (int i = tot_page_t * 20; i < _min((tot_page_t + 1) * 20, (int)libr.size()); ++i) {
				std::cout << std::setw(50) << libr[i]->get_name() << ' ';
				std::cout << std::setw(50) << libr[i]->get_author() << ' ';
				puts("");
			}
			printf("第 %d 页， 共 %d 页\n", tot_page_t + 1, all + 1);
			puts("输入 L 进入上一页，输入 R 进入下一页, 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == 'L') {
				if (tot_page_t == 0) goto Wrong_roll_page_book_t;
				--tot_page_t;
				goto Roll_page_t;
			}
			else if (action[0] == 'R') {
				if (tot_page_t == all) goto Wrong_roll_page_book_t;
				++tot_page_t;
				goto Roll_page_t;
			}
			else if (action[0] == 'B') goto Start_page_2;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
			Wrong_roll_page_book_t:
				puts("错误！");
				Sleep(1000);
				goto Roll_page_t;
			}
		}
		else if (action[0] == '2') {
			Search_book_name_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("请输入需要查询的书名！");
			std::cin >> action;
			int idx = tourist.search_book_name(action);
			Book* ret = Admin.print_one_book(idx, (login_statu == 0));
			if (ret == nullptr) {
				puts("错误！");
				Sleep(1000);
				goto Start_page_2;
			}
			printf("ISBN号： "); std::cout << ret->get_ISBN() << '\n';
			printf("作者： "); std::cout << ret->get_author() << '\n';
			printf("出版社： "); std::cout << ret->get_publisher() << '\n';
			printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
			printf("页数："); std::cout << ret->get_pages() << '\n';
			printf("价格："); std::cout << ret->get_price() << '\n';
			printf("简述： "); std::cout << ret->get_description() << '\n';
			puts("\n输入 C 继续， 输入 B 返回");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_name_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '3') {
			Search_book_author_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("请输入需要查询的作者！");
			std::cin >> action;
			std::vector<int> ret = tourist.search_book_author(action);
			for (int i : ret) {
				Book* u = Admin.print_one_book(i, (login_statu == 0));
				std::cout << std::setw(50) << u->get_name() << ' ';
				std::cout << std::setw(50) << u->get_publisher() << '\n';
			}
			puts("\n输入 C 继续， 输入 B 返回");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_author_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '4') {
			Search_book_ISBN_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("请输入需要查询的ISBN号");
			ll isbn = 0;
			std::cin >> isbn;
			int idx = tourist.search_book_ISBN(isbn);
			Book* ret = Admin.print_one_book(idx, (login_statu == 0));
			if (ret == nullptr) {
				puts("错误！");
				Sleep(1000);
				goto Start_page_2;
			}
			printf("作者： "); std::cout << ret->get_author() << '\n';
			printf("出版社： "); std::cout << ret->get_publisher() << '\n';
			printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
			printf("页数："); std::cout << ret->get_pages() << '\n';
			printf("价格："); std::cout << ret->get_price() << '\n';
			printf("描述： "); std::cout << ret->get_description() << '\n';
			puts("\n输入 C 继续， 输入 B 返回");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_ISBN_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '5') {
			Search_book_publisher_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("请输入需要查询的出版社！");
			std::cin >> action;
			std::vector<int> ret = tourist.search_book_publisher(action);
			for (int i : ret) {
				Book* u = Admin.print_one_book(i, (login_statu == 0));
				std::cout << std::setw(50) << u->get_name() << ' ';
				std::cout << std::setw(50) << u->get_author() << '\n';
			}
			puts("\n输入 C 继续， 输入 B 返回");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_publisher_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '6') {
			Show_news_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("1.借阅次数前十的图书");
			puts("2.借阅次数前十的读者");
			puts("3.最新出版前十的图书");
			puts("输入对应序号/字母以进入， 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
				print_lasted_news_1(login_statu == 0);
			}
			else if (action[0] == '2') {
				Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
				print_lasted_news_2(login_statu == 0);
			}
			else if (action[0] == '3') {
				Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
				print_lasted_news_3(login_statu == 0);
			}
			else if (action[0] == 'B') goto Start_page_2;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_2;
			}
			puts("输入 B 返回上一级");
			std::cin >> action;
			goto Show_news_tourist;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("错误！");
			goto Start_page_2;
		}
	}
	else if (action[0] == 'R') {
		system("cls");
		printf("请选择 注册(r) 或者 登录(l)\n");
		reader* login_reader = nullptr;
		std::cin >> action;
		char asc = getchar();
		if (action[0] == 'r') {
			Register:
			system("cls");
			reader* new_reader = new reader;
			new_reader->create_account(Admin.get_reader_numbers(1));
			printf("创建成功！\n");
			printf("您当前的用户名为： ");
			std::cout << new_reader->get_reader_name() << '\n';
			printf("您当前的密码为： 123456\n");
			printf("请及时修改您的用户名与密码！5秒后将跳转到图书页面\n");
			Admin.record(new_reader, 1);
			login_reader = new_reader;
			login_statu = 2;
			Sleep(5000);
		}
		else if (action[0] == 'l') {
			Login_reader:
			string login_name, act;
			system("cls");
			printf("请输入您的用户名：\n");
			std::cin >> login_name;
			if (!Admin.check_reader_exit(login_name, 1)) {
				printf("用户名不存在！请选择：注册(r)  重新输入(i)  退出(e)\n");
				std::cin >> act;
				if (act[0] == 'r') goto Register;
				else if (act[0] == 'i') goto Login_reader;
				else goto Main_page;
			}
			login_reader = Admin.print_one_reader(login_name, 1);
			int tried = 0;
			while (++tried <= 3) {
				if (tried == 1) puts("请输入密码：");
				else puts("请重新输入密码：");
				string input_password = "";
				char asc;
				while ((asc = _getch()) != '\r') {
					if (asc != '\b') {
						input_password.push_back(asc);
						putchar('*');
					}
					else if (input_password.size()) {
						putchar('\b');
						putchar(' ');
						putchar('\b');
						input_password.pop_back();
					}
				}
				puts("");
				if (login_reader->check_password(input_password)) {
					login_statu = 2;
					puts("您已成功登录！（身份：读者）");
					break;
				}
				else {
					puts("登录失败！");
					Sleep(1000);
					system("cls");
				}
			}
			if (login_statu == -1) {
				puts("请稍后再试！");
				Sleep(1000);
				goto Main_page;
			}
		}
		Start_page_3:
		Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
		puts("1.查看图书");
		puts("2.借阅/归还图书");
		puts("3.查看历史记录");
		puts("4.修改账户信息");
		puts("5.查看最新信息");
		std::vector<int> _rt = login_reader->book_need_return(reader::TIME{ current_date.year, current_date.month, current_date.day }, (login_statu == 2));
		if (_rt.size()) {
			puts("-------------------------------------------------");
			puts("当前有尚未归还的图书！请及时归还！");
			for (int i : _rt) std::cout << login_reader->get_book_name_index(i, (login_statu == 2)) << '\n';
			puts("-------------------------------------------------");
		}
		std::cin >> action;
		if (action[0] == '1') {
			See_book_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.查询所有图书信息(20本一页)");
			puts("2.查询图书(书名)");
			puts("3.查询图书(作者)");
			puts("4.查询图书(ISBN)");
			puts("5.查询图书(出版社)");
			puts("输入对应序号/字母以进入，输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Roll_page_r:
				system("cls");
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				std::vector<Book*> libr = Admin.print_all_books(login_statu == 2);
				static int tot_page_r = 0;
				int all = libr.size() / 20;
				for (int i = tot_page_r * 20; i < _min((tot_page_r + 1) * 20, (int)libr.size()); ++i) {
					std::cout << std::setw(50) << libr[i]->get_name() << ' ';
					std::cout << std::setw(50) << libr[i]->get_author() << ' ';
					puts("");
				}
				printf("第 %d 页， 共 %d 页\n", tot_page_r + 1, all + 1);
				puts("输入 L 进入上一页，输入 R 进入下一页, 输入 B 返回上一级");
				std::cin >> action;
				if (action[0] == 'L') {
					if (tot_page_r == 0) goto Wrong_roll_page_book_r;
					--tot_page_r;
					goto Roll_page_r;
				}
				else if (action[0] == 'R') {
					if (tot_page_r == all) goto Wrong_roll_page_book_r;
					++tot_page_r;
					goto Roll_page_r;
				}
				else if (action[0] == 'B') goto See_book_reader;
				else if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else {
					Wrong_roll_page_book_r:
					puts("错误！");
					Sleep(1000);
					goto Roll_page_r;
				}
			}
			else if (action[0] == '2') {
				Search_book_name_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的书名！");
				std::cin >> action;
				int idx = login_reader->search_book_name(action, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				if (ret == nullptr) {
					puts("错误！");
					Sleep(1000);
					goto See_book_reader;
				}
				printf("ISBN号： "); std::cout << ret->get_ISBN() << '\n';
				printf("作者： "); std::cout << ret->get_author() << '\n';
				printf("出版社： "); std::cout << ret->get_publisher() << '\n';
				printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
				printf("页数："); std::cout << ret->get_pages() << '\n';
				printf("价格："); std::cout << ret->get_price() << '\n';
				printf("简述： "); std::cout << ret->get_description() << '\n';
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_name_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '3') {
				Search_book_author_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的作者！");
				std::cin >> action;
				std::vector<int> ret = login_reader->search_book_author(action, (login_statu == 2));
				for (int i : ret) {
					Book* u = login_reader->print_one_book(i, (login_statu == 2));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_publisher() << '\n';
				}
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_author_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '4') {
				Search_book_ISBN_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的ISBN号");
				ll isbn = 0;
				std::cin >> isbn;
				int idx = login_reader->search_book_ISBN(isbn, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				if (ret == nullptr) {
					puts("错误！");
					Sleep(1000);
					goto See_book_reader;
				}
				printf("作者： "); std::cout << ret->get_author() << '\n';
				printf("出版社： "); std::cout << ret->get_publisher() << '\n';
				printf("出版日期： "); std::cout << ret->get_published_date() << '\n';
				printf("页数："); std::cout << ret->get_pages() << '\n';
				printf("价格："); std::cout << ret->get_price() << '\n';
				printf("描述： "); std::cout << ret->get_description() << '\n';
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_ISBN_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '5') {
				Search_book_publisher_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要查询的出版社！");
				std::cin >> action;
				std::vector<int> ret = login_reader->search_book_publisher(action, (login_statu == 2));
				for (int i : ret) {
					Book* u = login_reader->print_one_book(i, (login_statu == 2));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_author() << '\n';
				}
				puts("\n输入 C 继续， 输入 B 返回");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_publisher_reader;
				else goto See_book_reader;
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_3;
			}
		}
		else if (action[0] == '2') {
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.借阅图书");
			puts("2.归还图书");
			puts("输入对应序号/字母以进入，输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Borrow_book:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要借阅的图书名称：");
				std::cin >> action;
				int idx = 0, days = 0;
				idx = login_reader->search_book_name(action, (login_statu == 2));
				if (idx == 0) {
					puts("不存在该书！");
					Sleep(1000);
					goto Borrow_book;
				}
				puts("请输入您希望借阅的时长(不超过14天，输入天数)：");
				std::cin >> days;
				if (days < 0 || days > 14) {
					puts("借阅时间不符合要求！");
					Sleep(1000);
					goto Borrow_book;
				}
				login_reader->borrow_book(idx, reader::TIME{ current_date.year, current_date.month, current_date.day }, reader::TIME{ 0, 0, days }, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				ret->add_heat();
				puts("借阅成功！");
			}
			else if (action[0] == '2') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入需要归还的图书名称：");
				std::cin >> action;
				int idx = login_reader->search_book_name(action, (login_statu == 2));
				login_reader->return_book(idx, (login_statu == 2));
				puts("归还成功！");
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_3;
			}
			Sleep(2000);
			goto Start_page_3;
		}
		else if (action[0] == '3') {
			Search_info_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.查看所有当前借阅记录");
			puts("2.查看指定时间内的借阅记录");
			puts("3.查看所有借阅历史");
			puts("4.查看指定时间内的借阅历史");
			puts("5.清空历史记录");
			puts("输入对应序号/字母以进入，输入 B 返回上一级");
			std::cin >> action;
			std::vector<reader::borrowed_book> ret;
			if (action[0] == '1') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				ret = login_reader->search_borrowed((login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("当前无借阅图书");
				else {
					printf("当前借阅的图书为：\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '2') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入起始时间(年/月/日)和终止时间(年/月/日), 数字之间以空格分隔");
				reader::TIME st, et;
				read(st.year), read(st.month), read(st.day);
				read(et.year), read(et.month), read(et.day);
				ret = login_reader->search_borrowed(st, et, (login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("当前无借阅图书");
				else {
					printf("当前借阅的图书为：\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '3') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				ret = login_reader->search_history((login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("当前无借阅历史！");
				else {
					printf("以往借阅的图书为：\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '4') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("请输入起始时间(年/月/日)和终止时间(年/月/日), 数字之间以空格分隔");
				reader::TIME st, et;
				read(st.year), read(st.month), read(st.day);
				read(et.year), read(et.month), read(et.day);
				ret = login_reader->search_history(st, et, (login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("当前无借阅历史！");
				else {
					printf("以往借阅的图书为：\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '5') {
				login_reader->clear_history(login_statu == 2);
				puts("\n清空成功！");
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_3;
			}
			puts("\n输入 C 继续，输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == 'C') goto Search_info_reader;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else goto Start_page_3;
		}
		else if (action[0] == '4') {
			Change_info_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("输入 C1 更改用户名");
			puts("输入 C2 更改密码");
			puts("输入 C3 清除借阅历史");
			puts("输入 C4 删除账户");
			puts("输入 B 返回");
			std::cin >> action;
			if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else if (action[0] == 'B') goto Start_page_3;
			string new_things;
			if (action[1] == '1') {
				puts("请输入新的用户名：");
				std::cin >> new_things;
				Admin.renew_reader(login_reader->get_reader_name(), new_things, login_reader, (login_statu == 2));
				login_reader->change_name_reader(new_things, (login_statu == 2));
				puts("修改成功！");
			}
			else if (action[1] == '2') {
				puts("请输入新的密码：");
				std::cin >> new_things;
				login_reader->change_password(new_things, (login_statu == 2));
				puts("修改成功！");
			}
			else if (action[1] == '3') {
				login_reader->clear_history((login_statu == 2));
				puts("清空成功！");
			}
			else if (action[1] == '4') {
				Admin.delete_account(Admin.print_one_reader(login_reader->get_reader_name(), (login_statu == 2)), (login_statu == 2));
				puts("删除成功！2秒后自动退出");
				Sleep(2000);
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				goto Start_page_3;
			}
			puts("输入 C 继续，输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == 'C') goto Change_info_reader;
			else goto Start_page_3;
		}
		else if (action[0] == '5') {
			Show_news_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.借阅次数前十的图书");
			puts("2.借阅次数前十的读者");
			puts("3.最新出版前十的图书");
			puts("输入对应序号/字母以进入， 输入 B 返回上一级");
			std::cin >> action;
			if (action[0] == '1') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				print_lasted_news_1(login_statu == 2);
			}
			else if (action[0] == '2') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				print_lasted_news_2(login_statu == 2);
			}
			else if (action[0] == '3') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				print_lasted_news_3(login_statu == 2);
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("错误！");
				Sleep(1000);
				goto Start_page_3;
			}
			puts("输入 B 返回上一级");
			std::cin >> action;
			goto Show_news_reader;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("错误！");
			Sleep(1000);
			goto Start_page_3;
		}
	}
	else {
		puts("错误！");
		Sleep(1000);
		goto Main_page;
	}
	END:
	system("cls");
	std::ofstream save;
	save.open("src.txt", std::ios::out);
	std::vector<Book*> rep = Admin.print_all_books(1);
	for (auto i : rep) {
		save << i->get_index() << '\n';
		save << i->get_ISBN() << '\n';
		save << i->get_name() << '\n';
		save << i->get_author() << '\n';
		save << i->get_publisher() << '\n';
		save << i->get_published_date() << '\n';
		save << i->get_price() << '\n';
		save << i->get_pages() << '\n';
		save << i->get_description() << '\n';
		save << i->get_heat() << '\n';
		++cnt;
		printf("Successfully saved book #%d\n", cnt);
	}
	save.close();
	save.open("readers.txt", std::ios::out);
	std::vector<reader*> ret = Admin.print_all_readers(1);
	cnt = 0;
	for (reader* i : ret) {
		save << i->get_ID() << '\n';
		save << i->get_reader_name() << '\n';
		save << i->get_reader_password() << '\n';
		std::vector<reader::borrowed_book> o;
		o = i->search_history(1);
		save << o.size() << '\n';
		for (int j = 0; j < o.size(); ++j) {
			save << o[j].index << '\n';
			save << o[j].borrow.year << ' ' << o[j].borrow.month << ' ' << o[j].borrow.day << '\n';
			save << o[j].duration.year << ' ' << o[j].duration.month << ' ' << o[j].duration.day << '\n';
		}
		o = i->search_borrowed(1);
		save << o.size() << '\n';
		for (int j = 0; j < o.size(); ++j) {
			save << o[j].index << '\n';
			save << o[j].borrow.year << ' ' << o[j].borrow.month << ' ' << o[j].borrow.day << '\n';
			save << o[j].duration.year << ' ' << o[j].duration.month << ' ' << o[j].duration.day << '\n';
		}
		++cnt;
		printf("Successfully saved reader #%d\n", cnt);
	}
	save.close();
	system("cls");
	return 0;
}