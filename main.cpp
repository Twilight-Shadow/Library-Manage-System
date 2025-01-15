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
	printf("��ӭ��Administrator, ʱ�䣺%04d/%02d/%02d , ���� E �ǳ�\n", y, m, d);
	return;
}
void Tourist_up_screen(Tourist& t, int y, int m, int d) {
	system("cls");
	printf("��ӭ��");
	std::cout << t.get_tourist_name() << ", ";
	printf("ʱ�䣺%04d/%02d/%02d , ���� E �ǳ�\n", y, m, d);
	return;
}
void Reader_up_screen(reader* r, int y, int m, int d) {
	system("cls");
	printf("��ӭ��");
	std::cout << r->get_reader_name() << ", ";
	printf("ʱ�䣺%04d/%02d/%02d , ���� E �ǳ�\n", y, m, d);
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
		std::cout << "������ " << i->first << " ��\n";
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
		std::cout << "�ѽ��� " << i->first << " ��\n";
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
		std::cout << "�������ڣ� " << i->first << '\n';
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
	printf("|                    ��ӭ����ͼ�����ϵͳ��                   |\n");
	printf("|                       Made by Shadow                        |\n");
	printf("|                                                             |\n");
	printf("|                       ��ѡ���¼ģʽ��                      |\n");
	printf("|            A������Ա��¼  R�����ߵ�¼  T:�ο͵�¼           |\n");
	printf("|                                                             |\n");
	printf("|                         �� E �˳�                         |\n");
	printf("|                                                             |\n");
	printf("|                      [������밴�س���]                     |\n");
	printf("|                                                             |\n");
	printf("|                       ʱ�䣺%04d/%02d/%02d                      |\n", current_date.year, current_date.month, current_date.day);
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
			if (tried == 1) puts("���������Ա���룺");
			else puts("�������������Ա���룺");
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
				puts("���ѳɹ���¼������ݣ�����Ա��");
				break;
			}
			else {
				puts("��¼ʧ�ܣ�");
				Sleep(700);
				system("cls");
			}
		}
		if (login_statu == -1) {
			puts("���Ժ����ԣ�");
			goto Main_page;
		}
		Start_page_1:
		Admin_up_screen(current_date.year, current_date.month, current_date.day);
		puts("���ܣ�");
		puts("1.�������");
		puts("2.����ͼ��");
		puts("3.�鿴������Ϣ");
		puts("�����Ӧ���/��ĸ�Խ���");
		std::cin >> action;
		if (action[0] == 'E' || action[0] == 'B') {
			login_statu = -1;
			goto Main_page;
		}
		else if (action[0] == '1') {
			Manage_Reader:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.��ѯ���ж�����Ϣ(10��һҳ)");
			puts("2.���Ҷ���(�û���)");
			puts("3.�����˻���Ϣ");
			puts("4.�����˻�");
			puts("�����Ӧ���/��ĸ�Խ���, ���� B ������һ��");
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
				printf("�� %d ҳ�� �� %d ҳ\n", tot_page_r + 1, all + 1);
				puts("���� L ������һҳ������ R ������һҳ, ���� B ������һ��");
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
					puts("����");
					Sleep(1000);
					goto Roll_page_reader;
				}
			}
			else if (action[0] == '2') {
				See_one_reader:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ���û�����");
				std::cin >> action;
				reader* result = Admin.print_one_reader(action, (login_statu == 1));
				if (result == nullptr) {
					puts("�޴��û���");
					Sleep(1000);
					goto Manage_Reader;
				}
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("���û�����ϢΪ��");
				printf("�û�����"); std::cout << result->get_reader_name() << '\n';
				printf("���룺"); std::cout << result->get_reader_password() << '\n';
				puts("1.�鿴���е�ǰ���ļ�¼");
				puts("2.�鿴ָ��ʱ���ڵĽ��ļ�¼");
				puts("3.�鿴���н�����ʷ");
				puts("4.�鿴ָ��ʱ���ڵĽ�����ʷ");
				puts("���������Լ��������� B ������һ����");
				std::cin >> action;
				std::vector<reader::borrowed_book> ret;
				if (action[0] == '1') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					ret = result->search_borrowed((login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("��ǰ�޽���ͼ��");
					else {
						printf("��ǰ���ĵ�ͼ��Ϊ��\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
					}
				}
				else if (action[0] == '2') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					puts("��������ʼʱ��(��/��/��)����ֹʱ��(��/��/��), ����֮���Կո�ָ�");
					reader::TIME st, et;
					read(st.year), read(st.month), read(st.day);
					read(et.year), read(et.month), read(et.day);
					ret = result->search_borrowed(st, et, (login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("��ǰ�޽���ͼ��");
					else {
						printf("��ǰ���ĵ�ͼ��Ϊ��\n");
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
					if (ret.size() == 0) puts("��ǰ�޽�����ʷ��");
					else {
						printf("�������ĵ�ͼ��Ϊ��\n");
						for (int i = 0; i < ret.size(); ++i) {
							printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
							std::cout << Admin.get_book_name_index(ret[i].index, (login_statu == 1)) << '\n';
						}
						puts("");
					}
				}
				else if (action[0] == '4') {
					Admin_up_screen(current_date.year, current_date.month, current_date.day);
					puts("��������ʼʱ��(��/��/��)����ֹʱ��(��/��/��), ����֮���Կո�ָ�");
					reader::TIME st, et;
					read(st.year), read(st.month), read(st.day);
					read(et.year), read(et.month), read(et.day);
					ret = result->search_history(st, et, (login_statu == 1));
					puts("");
					if (ret.size() == 0) puts("��ǰ�޽�����ʷ��");
					else {
						printf("�������ĵ�ͼ��Ϊ��\n");
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
					puts("����");
					Sleep(1000);
					goto See_one_reader;
				}
				puts("");
				puts("���� C ������ѯ������ B ����");
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
				puts("��������Ҫ������û�����");
				string name__;
				std::cin >> name__;
				reader* result = Admin.print_one_reader(name__, (login_statu == 1));
				if (result == nullptr) {
					puts("�޴��û���");
					Sleep(1000);
					goto Manage_Reader;
				}
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("���û�����ϢΪ��");
				printf("�û�����"); std::cout << result->get_reader_name() << '\n';
				printf("���룺  "); std::cout << result->get_reader_password() << '\n';
				puts("\n���� C1 �����û���");
				puts("���� C2 ��������");
				puts("���� C3 �����ǰ���ļ�¼");
				puts("���� C4 ���������ʷ");
				puts("���� C5 ɾ���˻�");
				puts("���� B ����");
				std::cin >> action;
				if (action[0] == 'E') {
					login_statu = -1;
					goto Main_page;
				}
				else if (action[0] == 'B') goto Manage_Reader;
				string new_things;
				if (action[1] == '1') {
					puts("�������µ��û�����");
					std::cin >> new_things;
					result->change_name_reader(new_things, (login_statu == 1));
					Admin.renew_reader(name__, new_things, result, (login_statu == 1));
					puts("�޸ĳɹ���");
				}
				else if (action[1] == '2') {
					puts("�������µ����룺");
					std::cin >> new_things;
					result->change_password(new_things, (login_statu == 1));
					puts("�޸ĳɹ���");
				}
				else if (action[1] == '3') {
					result->clear_owned((login_statu == 1));
					puts("��ճɹ���");
				}
				else if (action[1] == '4') {
					result->clear_history((login_statu == 1));
					puts("��ճɹ���");
				}
				else if (action[1] == '5') {
					Admin.delete_account(Admin.print_one_reader(name__, (login_statu == 1)), (login_statu == 1));
					puts("ɾ���ɹ���");
				}
				else {
					puts("����");
					goto Manage_Reader;
				}
				puts("\n2��󷵻���һҳ");
				Sleep(2000);
				goto Manage_Reader;
			}
			else if (action[0] == '4') {
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				reader* new_reader = new reader;
				new_reader->create_account(Admin.get_reader_numbers((login_statu == 1)));
				printf("�����ɹ���\n");
				printf("��ǰ���û���Ϊ�� ");
				std::cout << new_reader->get_reader_name() << '\n';
				printf("��ǰ������Ϊ�� 123456\n");
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
				puts("����");
				Sleep(1000);
				goto Manage_Reader;
			}
		}
		else if (action[0] == '2') {
			Manage_book:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.��ѯ����ͼ����Ϣ(20��һҳ)");
			puts("2.��ѯͼ��(����)");
			puts("3.��ѯͼ��(����)");
			puts("4.��ѯͼ��(ISBN)");
			puts("5.��ѯͼ��(������)");
			puts("6.����ͼ����Ϣ");
			puts("�����Ӧ���/��ĸ�Խ��룬 ���� B ������һ��");
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
				printf("�� %d ҳ�� �� %d ҳ\n", tot_page_b + 1, all + 1);
				puts("���� L ������һҳ������ R ������һҳ, ���� B ������һ��");
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
					puts("����");
					Sleep(1000);
					goto Roll_page_b;
				}
			}
			else if (action[0] == '2') {
				Search_book_name_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ��������");
				std::cin >> action;
				int idx = Admin.search_book_name(action, (login_statu == 1));
				Book* ret = Admin.print_one_book(idx, (login_statu == 1));
				if (ret == nullptr) {
					puts("����");
					Sleep(1000);
					goto Manage_book;
				}
				printf("ISBN�ţ� "); std::cout << ret->get_ISBN() << '\n';
				printf("���ߣ� "); std::cout << ret->get_author() << '\n';
				printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
				printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
				printf("ҳ����"); std::cout << ret->get_pages() << '\n';
				printf("�۸�"); std::cout << ret->get_price() << '\n';
				printf("������ "); std::cout << ret->get_description() << '\n';
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_name_admin;
				else goto Manage_book;
			}
			else if (action[0] == '3') {
				Search_book_author_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ�����ߣ�");
				std::cin >> action;
				std::vector<int> ret = Admin.search_book_author(action, (login_statu == 1));
				for (int i : ret) {
					Book* u = Admin.print_one_book(i, (login_statu == 1));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_publisher() << '\n';
				}
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_author_admin;
				else goto Manage_book;
			}
			else if (action[0] == '4') {
				Search_book_ISBN_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ��ISBN��");
				ll isbn = 0;
				std::cin >> isbn;
				int idx = Admin.search_book_ISBN(isbn, (login_statu == 1));
				Book* ret = Admin.print_one_book(idx, (login_statu == 1));
				if (ret == nullptr) {
					puts("����");
					Sleep(1000);
					goto Manage_book;
				}
				printf("���ߣ� "); std::cout << ret->get_author() << '\n';
				printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
				printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
				printf("ҳ����"); std::cout << ret->get_pages() << '\n';
				printf("�۸�"); std::cout << ret->get_price() << '\n';
				printf("������ "); std::cout << ret->get_description() << '\n';
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_ISBN_admin;
				else goto Manage_book;
			}
			else if (action[0] == '5') {
				Search_book_publisher_admin:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ�ĳ����磡");
				std::cin >> action;
				std::vector<int> ret = Admin.search_book_publisher(action, (login_statu == 1));
				for (int i : ret) {
					Book* u = Admin.print_one_book(i, (login_statu == 1));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_author() << '\n';
				}
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_publisher_admin;
				else goto Manage_book;
			}
			else if (action[0] == '6') {
				Change_book_info:
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				puts("1.�����鼮����");
				puts("2.�����鼮ISBN��");
				puts("3.�����鼮����");
				puts("4.�����鼮������");
				puts("5.�����鼮��������");
				puts("6.�����鼮�۸�");
				puts("7.�����鼮ҳ��");
				puts("8.�����鼮����");
				puts("9.����ͼ��");
				puts("10.ɾ��ͼ��");
				string name__, __name;
				std::cin >> action;
				Admin_up_screen(current_date.year, current_date.month, current_date.day);
				if (action[0] == 'B') goto Manage_book;
				if (action[0] == '1' && action[1] != '0') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µ��鼮���ƣ�");
					std::cin >> __name;
					book__->change_name(__name, (login_statu == 1));
				}
				else if (action[0] == '2') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µ�ISBN�ţ�");
					ll isbn__ = 0;
					std::cin >> isbn__;
					book__->change_ISBN(isbn__, (login_statu == 1));
				}
				else if (action[0] == '3') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µ���������");
					std::cin >> __name;
					book__->change_author(__name, (login_statu == 1));
				}
				else if (action[0] == '4') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µĳ����磺");
					std::cin >> __name;
					book__->change_publisher(__name, (login_statu == 1));
				}
				else if (action[0] == '5') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µĳ������ڣ�");
					std::cin >> __name;
					book__->change_published_date(__name, (login_statu == 1));
				}
				else if (action[0] == '6') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µļ۸�");
					std::cin >> __name;
					book__->change_price(__name, (login_statu == 1));
				}
				else if (action[0] == '7') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µ�ҳ��");
					std::cin >> __name;
					book__->change_pages(__name, (login_statu == 1));
				}
				else if (action[0] == '8') {
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					puts("�������µļ���");
					std::cin >> __name;
					book__->change_description(__name, (login_statu == 1));
				}
				else if (action[0] == '9') {
					puts("��������Ҫ��ӵ�ͼ����Ϣ��˳�򼰸�ʽ����(��ͬ��Ϣ֮���Ի��зָ�)��");
					puts("���(����Ϊ0)�����ƣ�ISBN�ţ����ߣ������磬��������(��/��/��)���۸�ҳ��������");
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
					puts("�����뵱ǰ�鼮����: ");
					std::cin >> name__;
					Book* book__ = Admin.print_one_book(Admin.search_book_name(name__, (login_statu == 1)), (login_statu == 1));
					if (book__ == nullptr) {
						puts("���鼮�����ڣ�");
						goto Change_book_info;
					}
					Admin.delete_book(book__, (login_statu == 1));
				}
				else {
					puts("����");
					Sleep(1000);
					goto Manage_book;
				}
				puts("�޸ĳɹ���2��󷵻���һҳ");
				Sleep(2000);
				goto Manage_book;
			}
			else if (action[0] == 'B') goto Start_page_1;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("����");
				Sleep(1000);
				goto Start_page_1;
			}
		}
		else if (action[0] == '3') {
			Show_news_admin:
			Admin_up_screen(current_date.year, current_date.month, current_date.day);
			puts("1.���Ĵ���ǰʮ��ͼ��");
			puts("2.���Ĵ���ǰʮ�Ķ���");
			puts("3.���³���ǰʮ��ͼ��");
			puts("�����Ӧ���/��ĸ�Խ��룬 ���� B ������һ��");
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
				puts("����");
				Sleep(1000);
				goto Start_page_1;
			}
			puts("���� B ������һ��");
			std::cin >> action;
			goto Show_news_admin;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("����");
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
		puts("1.��ѯ����ͼ����Ϣ(20��һҳ)");
		puts("2.��ѯͼ��(����)");
		puts("3.��ѯͼ��(����)");
		puts("4.��ѯͼ��(ISBN)");
		puts("5.��ѯͼ��(������)");
		puts("6.�鿴������Ϣ");
		puts("�����Ӧ���/��ĸ�Խ���");
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
			printf("�� %d ҳ�� �� %d ҳ\n", tot_page_t + 1, all + 1);
			puts("���� L ������һҳ������ R ������һҳ, ���� B ������һ��");
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
				puts("����");
				Sleep(1000);
				goto Roll_page_t;
			}
		}
		else if (action[0] == '2') {
			Search_book_name_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("��������Ҫ��ѯ��������");
			std::cin >> action;
			int idx = tourist.search_book_name(action);
			Book* ret = Admin.print_one_book(idx, (login_statu == 0));
			if (ret == nullptr) {
				puts("����");
				Sleep(1000);
				goto Start_page_2;
			}
			printf("ISBN�ţ� "); std::cout << ret->get_ISBN() << '\n';
			printf("���ߣ� "); std::cout << ret->get_author() << '\n';
			printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
			printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
			printf("ҳ����"); std::cout << ret->get_pages() << '\n';
			printf("�۸�"); std::cout << ret->get_price() << '\n';
			printf("������ "); std::cout << ret->get_description() << '\n';
			puts("\n���� C ������ ���� B ����");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_name_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '3') {
			Search_book_author_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("��������Ҫ��ѯ�����ߣ�");
			std::cin >> action;
			std::vector<int> ret = tourist.search_book_author(action);
			for (int i : ret) {
				Book* u = Admin.print_one_book(i, (login_statu == 0));
				std::cout << std::setw(50) << u->get_name() << ' ';
				std::cout << std::setw(50) << u->get_publisher() << '\n';
			}
			puts("\n���� C ������ ���� B ����");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_author_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '4') {
			Search_book_ISBN_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("��������Ҫ��ѯ��ISBN��");
			ll isbn = 0;
			std::cin >> isbn;
			int idx = tourist.search_book_ISBN(isbn);
			Book* ret = Admin.print_one_book(idx, (login_statu == 0));
			if (ret == nullptr) {
				puts("����");
				Sleep(1000);
				goto Start_page_2;
			}
			printf("���ߣ� "); std::cout << ret->get_author() << '\n';
			printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
			printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
			printf("ҳ����"); std::cout << ret->get_pages() << '\n';
			printf("�۸�"); std::cout << ret->get_price() << '\n';
			printf("������ "); std::cout << ret->get_description() << '\n';
			puts("\n���� C ������ ���� B ����");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_ISBN_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '5') {
			Search_book_publisher_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("��������Ҫ��ѯ�ĳ����磡");
			std::cin >> action;
			std::vector<int> ret = tourist.search_book_publisher(action);
			for (int i : ret) {
				Book* u = Admin.print_one_book(i, (login_statu == 0));
				std::cout << std::setw(50) << u->get_name() << ' ';
				std::cout << std::setw(50) << u->get_author() << '\n';
			}
			puts("\n���� C ������ ���� B ����");
			std::cin >> action;
			if (action[0] == 'C') goto Search_book_publisher_tourist;
			else goto Start_page_2;
		}
		else if (action[0] == '6') {
			Show_news_tourist:
			Tourist_up_screen(tourist, current_date.year, current_date.month, current_date.day);
			puts("1.���Ĵ���ǰʮ��ͼ��");
			puts("2.���Ĵ���ǰʮ�Ķ���");
			puts("3.���³���ǰʮ��ͼ��");
			puts("�����Ӧ���/��ĸ�Խ��룬 ���� B ������һ��");
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
				puts("����");
				Sleep(1000);
				goto Start_page_2;
			}
			puts("���� B ������һ��");
			std::cin >> action;
			goto Show_news_tourist;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("����");
			goto Start_page_2;
		}
	}
	else if (action[0] == 'R') {
		system("cls");
		printf("��ѡ�� ע��(r) ���� ��¼(l)\n");
		reader* login_reader = nullptr;
		std::cin >> action;
		char asc = getchar();
		if (action[0] == 'r') {
			Register:
			system("cls");
			reader* new_reader = new reader;
			new_reader->create_account(Admin.get_reader_numbers(1));
			printf("�����ɹ���\n");
			printf("����ǰ���û���Ϊ�� ");
			std::cout << new_reader->get_reader_name() << '\n';
			printf("����ǰ������Ϊ�� 123456\n");
			printf("�뼰ʱ�޸������û��������룡5�����ת��ͼ��ҳ��\n");
			Admin.record(new_reader, 1);
			login_reader = new_reader;
			login_statu = 2;
			Sleep(5000);
		}
		else if (action[0] == 'l') {
			Login_reader:
			string login_name, act;
			system("cls");
			printf("�����������û�����\n");
			std::cin >> login_name;
			if (!Admin.check_reader_exit(login_name, 1)) {
				printf("�û��������ڣ���ѡ��ע��(r)  ��������(i)  �˳�(e)\n");
				std::cin >> act;
				if (act[0] == 'r') goto Register;
				else if (act[0] == 'i') goto Login_reader;
				else goto Main_page;
			}
			login_reader = Admin.print_one_reader(login_name, 1);
			int tried = 0;
			while (++tried <= 3) {
				if (tried == 1) puts("���������룺");
				else puts("�������������룺");
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
					puts("���ѳɹ���¼������ݣ����ߣ�");
					break;
				}
				else {
					puts("��¼ʧ�ܣ�");
					Sleep(1000);
					system("cls");
				}
			}
			if (login_statu == -1) {
				puts("���Ժ����ԣ�");
				Sleep(1000);
				goto Main_page;
			}
		}
		Start_page_3:
		Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
		puts("1.�鿴ͼ��");
		puts("2.����/�黹ͼ��");
		puts("3.�鿴��ʷ��¼");
		puts("4.�޸��˻���Ϣ");
		puts("5.�鿴������Ϣ");
		std::vector<int> _rt = login_reader->book_need_return(reader::TIME{ current_date.year, current_date.month, current_date.day }, (login_statu == 2));
		if (_rt.size()) {
			puts("-------------------------------------------------");
			puts("��ǰ����δ�黹��ͼ�飡�뼰ʱ�黹��");
			for (int i : _rt) std::cout << login_reader->get_book_name_index(i, (login_statu == 2)) << '\n';
			puts("-------------------------------------------------");
		}
		std::cin >> action;
		if (action[0] == '1') {
			See_book_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.��ѯ����ͼ����Ϣ(20��һҳ)");
			puts("2.��ѯͼ��(����)");
			puts("3.��ѯͼ��(����)");
			puts("4.��ѯͼ��(ISBN)");
			puts("5.��ѯͼ��(������)");
			puts("�����Ӧ���/��ĸ�Խ��룬���� B ������һ��");
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
				printf("�� %d ҳ�� �� %d ҳ\n", tot_page_r + 1, all + 1);
				puts("���� L ������һҳ������ R ������һҳ, ���� B ������һ��");
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
					puts("����");
					Sleep(1000);
					goto Roll_page_r;
				}
			}
			else if (action[0] == '2') {
				Search_book_name_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ��������");
				std::cin >> action;
				int idx = login_reader->search_book_name(action, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				if (ret == nullptr) {
					puts("����");
					Sleep(1000);
					goto See_book_reader;
				}
				printf("ISBN�ţ� "); std::cout << ret->get_ISBN() << '\n';
				printf("���ߣ� "); std::cout << ret->get_author() << '\n';
				printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
				printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
				printf("ҳ����"); std::cout << ret->get_pages() << '\n';
				printf("�۸�"); std::cout << ret->get_price() << '\n';
				printf("������ "); std::cout << ret->get_description() << '\n';
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_name_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '3') {
				Search_book_author_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ�����ߣ�");
				std::cin >> action;
				std::vector<int> ret = login_reader->search_book_author(action, (login_statu == 2));
				for (int i : ret) {
					Book* u = login_reader->print_one_book(i, (login_statu == 2));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_publisher() << '\n';
				}
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_author_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '4') {
				Search_book_ISBN_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ��ISBN��");
				ll isbn = 0;
				std::cin >> isbn;
				int idx = login_reader->search_book_ISBN(isbn, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				if (ret == nullptr) {
					puts("����");
					Sleep(1000);
					goto See_book_reader;
				}
				printf("���ߣ� "); std::cout << ret->get_author() << '\n';
				printf("�����磺 "); std::cout << ret->get_publisher() << '\n';
				printf("�������ڣ� "); std::cout << ret->get_published_date() << '\n';
				printf("ҳ����"); std::cout << ret->get_pages() << '\n';
				printf("�۸�"); std::cout << ret->get_price() << '\n';
				printf("������ "); std::cout << ret->get_description() << '\n';
				puts("\n���� C ������ ���� B ����");
				std::cin >> action;
				if (action[0] == 'C') goto Search_book_ISBN_reader;
				else goto See_book_reader;
			}
			else if (action[0] == '5') {
				Search_book_publisher_reader:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ��ѯ�ĳ����磡");
				std::cin >> action;
				std::vector<int> ret = login_reader->search_book_publisher(action, (login_statu == 2));
				for (int i : ret) {
					Book* u = login_reader->print_one_book(i, (login_statu == 2));
					std::cout << std::setw(50) << u->get_name() << ' ';
					std::cout << std::setw(50) << u->get_author() << '\n';
				}
				puts("\n���� C ������ ���� B ����");
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
				puts("����");
				Sleep(1000);
				goto Start_page_3;
			}
		}
		else if (action[0] == '2') {
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.����ͼ��");
			puts("2.�黹ͼ��");
			puts("�����Ӧ���/��ĸ�Խ��룬���� B ������һ��");
			std::cin >> action;
			if (action[0] == '1') {
				Borrow_book:
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ���ĵ�ͼ�����ƣ�");
				std::cin >> action;
				int idx = 0, days = 0;
				idx = login_reader->search_book_name(action, (login_statu == 2));
				if (idx == 0) {
					puts("�����ڸ��飡");
					Sleep(1000);
					goto Borrow_book;
				}
				puts("��������ϣ�����ĵ�ʱ��(������14�죬��������)��");
				std::cin >> days;
				if (days < 0 || days > 14) {
					puts("����ʱ�䲻����Ҫ��");
					Sleep(1000);
					goto Borrow_book;
				}
				login_reader->borrow_book(idx, reader::TIME{ current_date.year, current_date.month, current_date.day }, reader::TIME{ 0, 0, days }, (login_statu == 2));
				Book* ret = login_reader->print_one_book(idx, (login_statu == 2));
				ret->add_heat();
				puts("���ĳɹ���");
			}
			else if (action[0] == '2') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������Ҫ�黹��ͼ�����ƣ�");
				std::cin >> action;
				int idx = login_reader->search_book_name(action, (login_statu == 2));
				login_reader->return_book(idx, (login_statu == 2));
				puts("�黹�ɹ���");
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("����");
				Sleep(1000);
				goto Start_page_3;
			}
			Sleep(2000);
			goto Start_page_3;
		}
		else if (action[0] == '3') {
			Search_info_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.�鿴���е�ǰ���ļ�¼");
			puts("2.�鿴ָ��ʱ���ڵĽ��ļ�¼");
			puts("3.�鿴���н�����ʷ");
			puts("4.�鿴ָ��ʱ���ڵĽ�����ʷ");
			puts("5.�����ʷ��¼");
			puts("�����Ӧ���/��ĸ�Խ��룬���� B ������һ��");
			std::cin >> action;
			std::vector<reader::borrowed_book> ret;
			if (action[0] == '1') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				ret = login_reader->search_borrowed((login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("��ǰ�޽���ͼ��");
				else {
					printf("��ǰ���ĵ�ͼ��Ϊ��\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '2') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������ʼʱ��(��/��/��)����ֹʱ��(��/��/��), ����֮���Կո�ָ�");
				reader::TIME st, et;
				read(st.year), read(st.month), read(st.day);
				read(et.year), read(et.month), read(et.day);
				ret = login_reader->search_borrowed(st, et, (login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("��ǰ�޽���ͼ��");
				else {
					printf("��ǰ���ĵ�ͼ��Ϊ��\n");
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
				if (ret.size() == 0) puts("��ǰ�޽�����ʷ��");
				else {
					printf("�������ĵ�ͼ��Ϊ��\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '4') {
				Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
				puts("��������ʼʱ��(��/��/��)����ֹʱ��(��/��/��), ����֮���Կո�ָ�");
				reader::TIME st, et;
				read(st.year), read(st.month), read(st.day);
				read(et.year), read(et.month), read(et.day);
				ret = login_reader->search_history(st, et, (login_statu == 2));
				puts("");
				if (ret.size() == 0) puts("��ǰ�޽�����ʷ��");
				else {
					printf("�������ĵ�ͼ��Ϊ��\n");
					for (int i = 0; i < ret.size(); ++i) {
						printf("%d/%d/%d ", ret[i].borrow.year, ret[i].borrow.month, ret[i].borrow.day);
						std::cout << login_reader->get_book_name_index(ret[i].index, (login_statu == 2)) << '\n';
					}
				}
			}
			else if (action[0] == '5') {
				login_reader->clear_history(login_statu == 2);
				puts("\n��ճɹ���");
			}
			else if (action[0] == 'B') goto Start_page_3;
			else if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("����");
				Sleep(1000);
				goto Start_page_3;
			}
			puts("\n���� C ���������� B ������һ��");
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
			puts("���� C1 �����û���");
			puts("���� C2 ��������");
			puts("���� C3 ���������ʷ");
			puts("���� C4 ɾ���˻�");
			puts("���� B ����");
			std::cin >> action;
			if (action[0] == 'E') {
				login_statu = -1;
				goto Main_page;
			}
			else if (action[0] == 'B') goto Start_page_3;
			string new_things;
			if (action[1] == '1') {
				puts("�������µ��û�����");
				std::cin >> new_things;
				Admin.renew_reader(login_reader->get_reader_name(), new_things, login_reader, (login_statu == 2));
				login_reader->change_name_reader(new_things, (login_statu == 2));
				puts("�޸ĳɹ���");
			}
			else if (action[1] == '2') {
				puts("�������µ����룺");
				std::cin >> new_things;
				login_reader->change_password(new_things, (login_statu == 2));
				puts("�޸ĳɹ���");
			}
			else if (action[1] == '3') {
				login_reader->clear_history((login_statu == 2));
				puts("��ճɹ���");
			}
			else if (action[1] == '4') {
				Admin.delete_account(Admin.print_one_reader(login_reader->get_reader_name(), (login_statu == 2)), (login_statu == 2));
				puts("ɾ���ɹ���2����Զ��˳�");
				Sleep(2000);
				login_statu = -1;
				goto Main_page;
			}
			else {
				puts("����");
				goto Start_page_3;
			}
			puts("���� C ���������� B ������һ��");
			std::cin >> action;
			if (action[0] == 'C') goto Change_info_reader;
			else goto Start_page_3;
		}
		else if (action[0] == '5') {
			Show_news_reader:
			Reader_up_screen(login_reader, current_date.year, current_date.month, current_date.day);
			puts("1.���Ĵ���ǰʮ��ͼ��");
			puts("2.���Ĵ���ǰʮ�Ķ���");
			puts("3.���³���ǰʮ��ͼ��");
			puts("�����Ӧ���/��ĸ�Խ��룬 ���� B ������һ��");
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
				puts("����");
				Sleep(1000);
				goto Start_page_3;
			}
			puts("���� B ������һ��");
			std::cin >> action;
			goto Show_news_reader;
		}
		else if (action[0] == 'E') {
			login_statu = -1;
			goto Main_page;
		}
		else {
			puts("����");
			Sleep(1000);
			goto Start_page_3;
		}
	}
	else {
		puts("����");
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