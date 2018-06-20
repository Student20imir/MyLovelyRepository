#pragma once
#include <string>
#include <list>

using namespace std;
class Reader
{
public:
	Reader(string name, string surname, int library_card, list<int> books_ids) { this->name = name; this->surname = surname; this->library_card = library_card; this->books_ids = books_ids; }
	~Reader();
	int get_library_card_number() const { return library_card; }
	void add_book_id(int book_id) { books_ids.push_back(book_id); }
	void remove_book_id(int book_id) { books_ids.remove(book_id); }
	string convert_to_file_format();
	string get_name() const { return name; }
	string get_surname() const { return surname; }
	list<int> get_books_ids() const { return books_ids; }
	friend ostream & operator<< (ostream &out, const Reader &b);

private:
	string name;
	string surname;
	int library_card;
	list<int> books_ids;
};

