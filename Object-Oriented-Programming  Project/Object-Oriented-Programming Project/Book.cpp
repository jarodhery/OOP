#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "Utils.h"
#include "Book.h"

using namespace std;
namespace seneca
{
	Book::Book() {
	}


	char Book::type()const
	{
		return 'B';
	}

	ostream& Book::write(ostream& os)const
	{
		Publication::write(os);

		if (conIO(os))
		{
			os << " ";

			os.setf(ios::left);
			if (strlen(authorName) > SENECA_AUTHOR_WIDTH)
			{
				for (int i = 0; i < SENECA_AUTHOR_WIDTH; i++)
				{
					os << authorName[i];
				}
			}
			else
			{
				os.width(SENECA_AUTHOR_WIDTH);
				os << authorName;
			}
			os << "|";
			os.unsetf(ios::left);
		}

		else
		{
			os << "\t" << authorName;
		}

		return os;
	}

	istream& Book::read(istream& is) {
		char author[256 + 1];
		setDefault();
		Publication::read(is);
		if (conIO(is)) {
			Utils::getChar(is, '\n');
			cout << "Author: ";
			is.getline(author, 256 + 1);
		}
		else {
			Utils::getChar(is, '\t');
			is.get(author, 256 + 1);
		}
		if (is) {
			Utils::copyStr(authorName, author);
		}
		else {
			setDefault();
		}
		return is;
	}

	void Book::set(int member_id)
	{
		Publication::set(member_id);
		Publication::resetDate();

	}

	Book::Book(const Book& obj) {
		operator=(obj);
	}
	Book& Book::operator=(const Book& obj) {
		if (this != &obj && obj) { 
			Publication::operator=(obj);
			Utils::copyStr(authorName, obj.authorName);
		}
		return *this;
	}
	Book::~Book() {
		delete[] authorName;
		authorName = nullptr;
	}

	void Book::setDefault() {
		delete[] authorName;
		authorName = nullptr;
		Publication::setDefault();
	}

	bool Book::conIO(std::ios& io)const {
		return Publication::conIO(io);
	}
	Book::operator bool()const {
		return (authorName && authorName[0] && Publication::operator bool());
	}

}