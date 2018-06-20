#include "stdafx.h"
#include "Library.h"


Library::Library()
{
}


Library::~Library()
{
}

void Library::load_books(string file_name)
{
	ifstream in(file_name);
	string line;
	list<Book> *books = new list<Book>();

	if (!in.bad()) {
		while (getline(in, line)) {
			vector<string> tokens = split(line, ':');
			if (tokens.size() == 5) {
				int lent = atoi(tokens.at(4).c_str());
				if (lent == 0) books->push_back(Book(atoi(tokens.at(0).c_str()), tokens.at(1), tokens.at(2), tokens.at(3), false));
				else books->push_back(Book(atoi(tokens.at(0).c_str()), tokens.at(1), tokens.at(2), tokens.at(3), true));
			}
		}
	}
	in.close();
	this->books = books;
}

bool Library::save_library(string file_name)
{
	ofstream out(file_name, ofstream::out);

	if (!out.bad())
	{
		for (auto it = (*books).begin(); it != (*books).end(); it++) {
			out << (*it).convert_to_file_format();
		}
		out.close();
		return true;
	}
	else return false;

}

void Library::sort_books(string by)
{
	if (by.compare("title") == 0) books->sort(cmp_by_title);
	if (by.compare("author") == 0) books->sort(cmp_by_author);
	if (by.compare("date") == 0) books->sort(cmp_by_release_date);
}

Book * Library::search_by_title(string title)
{
	for (auto it = books->begin(); it != books->end(); it++) {
		if ((*it).get_title() == title)
			return &*it;
	}
	return NULL;
}

Book * Library::search_by_author(string author)
{
	for (auto it = books->begin(); it != books->end(); it++) {
		if ((*it).get_author() == author)
			return &*it;
	}
	return NULL;
}

Book * Library::get_book_by_id(int book_id)
{
	for (auto it = books->begin(); it != books->end(); it++) {
		if ((*it).get_id() == book_id) return &*it;
	}
	return NULL;
}

ostream & operator<<(ostream & out, const Library & b)
{
	auto books = b.get_books();
	for (auto it = books->begin(); it != books->end(); it++) {
		out << *it << endl;
	}
	return out;
}
