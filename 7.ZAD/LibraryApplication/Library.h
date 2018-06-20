#pragma once
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include "Book.h"
#include "Utils.h"

class Library
{
public:
	Library();
	~Library();
	void load_books(string file_name);
	bool save_library(string file_name);
	void sort_books(string by);
	Book* search_by_title(string title);
	Book* search_by_author(string author);
	Book * get_book_by_id(int book_id);
	bool is_loaded() { if (books) return true; else return false; }
	list<Book> *get_books() const { return books; }

	friend ostream & operator<< (ostream &out, const Library &b);
private:
	
	list<Book> *books;
};

