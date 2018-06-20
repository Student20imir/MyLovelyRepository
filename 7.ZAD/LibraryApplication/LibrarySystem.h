#pragma once
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include "Librarian.h"
#include "Reader.h"
#include "Book.h"
#include <vector>
#include <iostream>
#include "Library.h"

using namespace std;

class LibrarySystem
{
public:
	LibrarySystem();
	~LibrarySystem();

	list<Librarian> *load_librarians(string file_name);
	list<Reader> *load_readers(string file_name);	
	bool login_librarian(string login, string password);
	void logout_librarian();	
	bool lend_book(int library_card_number, int book_id);
	bool return_book(int library_card_number, int book_id);
	bool save_readers(string file_name);

	bool user_interface();

private:
	list<Librarian> *librarians;
	Librarian* logged_librarian;
	list<Reader> *readers;
	Library library;
	
	Reader * get_reader_by_card_number(int card_number);
	
	string books_file_name;
	string readers_file_name;


};

