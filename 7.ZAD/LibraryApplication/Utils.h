#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>   // transform()
#include <cctype>      // toupper(), tolower()
#include <functional>  // ptr_fun()
#include "Book.h"

using namespace std;


namespace {
	vector<string> split(const string& s, char delimiter) //https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string
	{
		vector<string> tokens;
		string token;
		istringstream tokenStream(s);
		while (getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	bool cmp(string s1, string s2) {
		transform(s1.begin(), s1.end(), s1.begin(), ptr_fun <int, int>(tolower));
		transform(s2.begin(), s2.end(), s2.begin(), ptr_fun <int, int>(tolower));
		int cmp_value = s1.compare(s2);

		if (cmp_value > 0) return false;
		else return true;
	}

	bool cmp_by_title(const Book &b1, const Book &b2) {
		return cmp(b1.get_title(), b2.get_title());
	}

	bool cmp_by_author(const Book &b1, const Book &b2) {
		return cmp(b1.get_author(), b2.get_author());
	}

	bool cmp_by_release_date(const Book &b1, const Book &b2) {
		return cmp(b1.get_release_date(), b2.get_release_date());
	}
}