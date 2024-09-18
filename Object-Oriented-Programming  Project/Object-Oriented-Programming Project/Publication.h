#ifndef _PUBLICATION_H
#define _PUBLICATION_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Stremable.h"
#include "Lib.h"
#include "Date.h"
namespace seneca {
	class Publication : public Streamable {
		char* m_title{};
		char m_shelfId[SENECA_SHELF_ID_LEN + 1]{};
		int m_membership;
		int m_libRef;
		Date m_date;
	public:
		Publication();

		// Rule of three
		Publication(const Publication& obj);
		Publication& operator=(const Publication& obj);
		virtual ~Publication();

		// Modifiers
		virtual void setDefault();
		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();

		// Queries
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;

		// Pure virtual function implement
		bool conIO(std::ios& io)const;
		operator bool()const;
		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& istr);
	};

}
#endif
