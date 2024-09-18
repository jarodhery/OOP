#ifndef BOOK_H
#define BOOK_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Lib.h"
#include "Publication.h"

namespace seneca
{
	class Book : public Publication
	{
	private:
		char* authorName{};


	public:
		Book();
		Book(const Book& obj);
		Book& operator=(const Book& obj);
		virtual ~Book();

		void setDefault();
		void set(int member_id);
		char type()const;
		bool conIO(std::ios& io)const;

		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
		operator bool()const;


	};

}

#endif