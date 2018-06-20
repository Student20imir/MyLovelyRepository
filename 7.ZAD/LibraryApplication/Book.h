#pragma once
#include <string>

using namespace std;
class Book
{
public:
	Book(int id, string title, string author, string release_date, bool is_lent) { this->id = id; this->title = title; this->author = author; this->release_date = release_date; this->lent = is_lent; }
	string convert_to_file_format();
	string get_title() const { return title; }
	string get_author() const { return author; }
	string get_release_date() const { return release_date; }
	bool is_lent() const { return lent; }
	void set_lent(bool lent) { this->lent = lent; }
	int get_id() const { return id; }
	string get_title() { return title; }
	string get_author() { return author; }
	string get_release_date() { return release_date; }
	~Book();

	friend ostream & operator<< (ostream &out, const Book &b);

private:
	int id;
	string title;
	string author;
	string release_date; //yyyy-mm-dd
	bool lent;

};

