#include "stdafx.h"
#include "LibrarySystem.h"


LibrarySystem::LibrarySystem()
{
}


LibrarySystem::~LibrarySystem()
{
}

list<Librarian> * LibrarySystem::load_librarians(string file_name)
{
	ifstream in(file_name);
	string line;
	list<Librarian> *librarians = new list<Librarian>();
	
	if (!in.bad()) {
		while (getline(in, line)) {
			vector<string> tokens = split(line, ':');
			if (tokens.size() == 3) {
				librarians->push_back(Librarian(atoi(tokens.at(0).c_str()), tokens.at(1), tokens.at(2)));
			}
		}
	}
	in.close();
	return librarians;
}

list<Reader> *LibrarySystem::load_readers(string file_name)
{
	ifstream in(file_name);
	string line;
	list<Reader> *readers = new list<Reader>();


	if (!in.bad()) {
		while (getline(in, line)) {
			vector<string> tokens = split(line, ':');
			if (tokens.size() == 4) {
				list<int> books_ids;
				if (tokens.at(3) != ";") {
					vector<string> ids = split(tokens.at(3), ';');
					for (auto it = ids.begin(); it != ids.end(); it++) {
						books_ids.push_back(atoi((*it).c_str()));
					}
				}

				readers->push_back(Reader(tokens.at(0), tokens.at(1), atoi(tokens.at(2).c_str()), books_ids));
			}			
		}	
		readers_file_name = file_name;
	}
	else {
		delete readers;
	}
	in.close();
	return readers;
}

bool LibrarySystem::login_librarian(string login, string password)
{
	if (librarians != NULL && logged_librarian == NULL) {
		for (auto it = librarians->begin(); it != librarians->end(); it++) {
			if ((*it).get_login() == login && (*it).get_password() == password) {
				logged_librarian = &*it;
				return true;
			}
		}		
	}
	return false;
}

void LibrarySystem::logout_librarian()
{
	logged_librarian = NULL;
}



bool LibrarySystem::lend_book(int library_card_number, int book_id)
{
	Reader *reader = get_reader_by_card_number(library_card_number);
	if (!reader) return false;
	Book *book = library.get_book_by_id(book_id);
	if (!book) return false;
	if (book->is_lent()) return false;
	book->set_lent(true);
	reader->add_book_id(book_id);
	library.save_library(books_file_name);
	save_readers(readers_file_name);
	return true;
}

bool LibrarySystem::return_book(int library_card_number, int book_id)
{
	Reader *reader = get_reader_by_card_number(library_card_number);
	if (!reader) return false;
	Book *book = library.get_book_by_id(book_id);
	if (!book) return false;
	if (!book->is_lent()) return false;
	book->set_lent(false);
	reader->remove_book_id(book_id);
	library.save_library(books_file_name);
	save_readers(readers_file_name);
	return true;
}

bool LibrarySystem::save_readers(string file_name)
{
	ofstream out(file_name, ofstream::out);

	if (!out.bad())
	{
		for (auto it = (*readers).begin(); it != (*readers).end(); it++) {
			out << (*it).convert_to_file_format();
		}
		out.close();
		return true;
	}
	else return false;
}

bool LibrarySystem::user_interface()
{
	if (librarians == NULL) {
		librarians = load_librarians("librarians.txt");
	}
	string login;
	string password;

	bool is_logged = false;

	while (!is_logged) {
		cout << "Witaj w systemie biblioteki, prosze sie zalogowac" << endl;
		cout << "Login: ";
		cin >> login;
		cout << "Haslo: ";
		cin >> password;
		is_logged = login_librarian(login, password);
		if (!is_logged) cout << "Zla nazwa uzytkownika lub haslo" << endl;
	}

	cout << "Logowanie przebieglo pomyslnie" << endl;

	bool exit = false;

	while (!exit) {		
		cout << "[1] Zaladuj czytelnikow" << endl
			<< "[2] Zaladuj ksiegozbior" << endl;
		if (readers != NULL && library.is_loaded()) {
			cout << "[3] Zapisz ksiegozbior" << endl
				<< "[4] Pokaz ksiegozbior" << endl
				<< "[5] Sortuj ksiegozbior" << endl
				<< "[6] Wyszukaj po tytule" << endl
				<< "[7] Wyszukaj po autorze" << endl
				<< "[8] Wypozycz ksiazke" << endl
				<< "[9] Zwroc ksiazke" << endl
				<< "[10] Pokaz czytelnikow" << endl
				<< "[0] Opusc program" << endl;
		}

		int opt;
		cin >> opt;
		getchar();
		string file_name;
		string title;
		string author;
		Book *book;
		int card_number;
		int book_id;
		bool is_sorted;
		switch (opt) {
		case 1:
			readers = NULL;
			while (readers == NULL) {
				cout << "Podaj nazwe pliku: " << endl;				
				getline(cin, file_name);
				this->readers = load_readers(file_name);
			}
			cout << "Ladowanie przebieglo pomyslnie" << endl;
			break;
		case 2:
			while (library.get_books() == NULL) {
				cout << "Podaj nazwe pliku: " << endl;				
				getline(cin, file_name);
				library.load_books(file_name);
			}
			books_file_name = file_name;
			cout << "Ladowanie przebieglo pomyslnie" << endl;
			break;
		case 3:
			library.save_library(books_file_name);
			cout << "Ksiegozbior zostal zapisany" << endl;
			break;
		case 4:
			cout << library;
			break;
		case 5:
			 is_sorted = false;
			while (!is_sorted) {
				cout << "Sortowanie po: " << endl
					<< "[1] tytule" << endl
					<< "[2] autorze" << endl
					<< "[3] dacie wydania" << endl;
				int opt2;
				cin >> opt2;
				getchar();
				switch (opt2) {
				case 1:
					library.sort_books("title");
					is_sorted = true;
					break;
				case 2:
					library.sort_books("author");
					is_sorted = true;
					break;
				case 3:
					library.sort_books("date");
					is_sorted = true;
					break;
				}
				if (!is_sorted) cout << "Zla opcja, wpowadz jeszcze raz" << endl;
			}
			cout << "Ksiegozbior zostal posortowany" << endl;
			break;
		case 6:
			cout << "Wprowadz tytul: ";
			
			getline(cin, title);
			book = library.search_by_title(title);
			if (book != NULL) {
				cout << *book << endl;
			}
			else {
				cout << "Nie znaleziono ksiazki o takim tytule" << endl;
			}
			break;
		case 7:
			cout << "Wprowadz autora: " << endl;
			
			getline(cin, author);
			book = library.search_by_author(author);
			if (book != NULL) {
				cout << *book << endl;
			}
			else {
				cout << "Nie znaleziono ksiazki o takim autorze" << endl;
			}
			break;
		case 8:
			cout << "Podaj numer karty bibliotecznej: " << endl;
			
			cin >> card_number;
			getchar();
			cout << "Podaj id ksiazki: " << endl;
			cin >> book_id;
			getchar();
			if (lend_book(card_number, book_id)) {
				cout << "Ksiazka zostala wypozyczona" << endl;
			}
			else {
				cout << "Podales zle dane lub ksiazka jest juz wypozyczona" << endl;
			}
			break;
		case 9:
			cout << "Podaj numer karty bibliotecznej: " << endl;
			cin >> card_number;
			getchar();
			cout << "Podaj id ksiazki: " << endl;
			
			cin >> book_id;
			getchar();
			if (return_book(card_number, book_id)) {
				cout << "Ksiazka zostala zwrocona" << endl;
			}
			else {
				cout << "Podales zle dane lub ksiazka nie byla wypozyczona" << endl;
			}
			break;
		case 10:
			for (auto it = readers->begin(); it != readers->end(); it++) {
				cout << (*it) << endl;
			}
			break;
		case 0:
			exit = true;
			break;
		}
	}	
	return false;
}

Reader * LibrarySystem::get_reader_by_card_number(int card_number)
{
	for (auto it = readers->begin(); it != readers->end(); it++) {
		if ((*it).get_library_card_number() == card_number) return &*it;
	}
	return NULL;
}
