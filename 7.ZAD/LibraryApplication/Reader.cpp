#include "stdafx.h"
#include "Reader.h"


Reader::~Reader()
{
}

string Reader::convert_to_file_format()
{
	string reader;
	reader.append(name).append(":").append(surname).append(":").append(to_string(library_card)).append(":");
	if (books_ids.size() > 0) {
		for (auto it = books_ids.begin(); it != books_ids.end(); it++) {
			reader.append(to_string((*it))).append(";");
		}
	}
	else reader.append(";");
	reader.append("\n");
	return reader;
}

ostream & operator<<(ostream & out, const Reader & b)
{
	out << "Imie: " << b.get_name() << " Nazwisko: " << b.get_surname() << " Numer karty: " << b.get_library_card_number();
	list<int> books_ids = b.get_books_ids();
	if (books_ids.size() > 0) {
		out << " Wypozyczone: ";
		for (auto it = books_ids.begin(); it != books_ids.end(); it++) {
			out << (*it) << ", ";
		}
	}
	return out;
}
