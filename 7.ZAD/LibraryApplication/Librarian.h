#pragma once
#include <string>

using namespace std;
class Librarian
{
public:
	Librarian(int id, string login, string password) { this->id = id; this->login = login; this->password = password; }
	~Librarian();
	string get_login() { return login; }
	string get_password() { return password; }

private:
	int id;
	string login;
	string password;

};

