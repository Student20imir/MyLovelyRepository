#include "stdafx.h"
#include "Book.h"




string Book::convert_to_file_format()
{
	string book;
	string status;
	if (lent) status = "1";
	else status = "0";
	book.append(to_string(id)).append(":").append(title).append(":").append(author).append(":").append(release_date).append(":").append(status).append("\n");
	return book;

}

Book::~Book()
{
}

ostream & operator<<(ostream & out, const Book & b)
{
	string status;
	if (b.is_lent()) status = "niedostepna";
	else status = "dostepna";
	out << "ID: " << b.get_id() << " Tytul: " << b.get_title() << " Autor: " << b.get_author() << " Data wydania: " << b.get_release_date()
		<< " Status: " << status;

	return out;
}
