#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "Utils.h"

using namespace std;
namespace seneca {

	ostream& Publication::write(ostream& os)const
	{
		if (conIO(os)) {
			os << "| " << m_shelfId << " | ";
			if (strlen(m_title) > SENECA_TITLE_WIDTH)
			{
				for (int i = 0; i < SENECA_TITLE_WIDTH; i++) os << m_title[i];
			}
			else
			{
				os.setf(ios::left);
				os.fill('.');
				os.width(SENECA_TITLE_WIDTH);
				os << m_title;
				os.fill(' ');
				os.unsetf(ios::left);
			}
			os << " | ";
			if (m_membership != 0) os << m_membership;
			else os << " N/A ";
			os << " | " << m_date << " |";
		}
		else
		{
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" <<
				m_title << "\t" << m_membership << "\t" << m_date;
		}
		return os;
	}
	istream& Publication::read(istream& istr) {
		setDefault();
		char* title;
		char shelfId[SENECA_SHELF_ID_LEN + 1];
		int lib = 0;
		Date date;
		int member = 0;
		if (conIO(istr)) {
			cout << "Shelf No: ";
			istr.getline(shelfId, SENECA_SHELF_ID_LEN + 1, '\n');
			if (strlen(shelfId) < SENECA_SHELF_ID_LEN) istr.setstate(ios::failbit);
			cout << "Title: ";
			title = Utils::readInput(istr);
			cout << "Date: ";
			date.read(istr);
		}
		else {
			istr >> lib;
			Utils::getChar(istr, '\t');
			istr >> shelfId;
			Utils::getChar(istr, '\t');
			title = Utils::readInput(istr, '\t');
			istr >> member;
			Utils::getChar(istr, '\t');
			date.read(istr);
		}
		if (!date) istr.setstate(ios::failbit);
		if (istr) {
			Utils::copyStr(m_title, title);
			strcpy(m_shelfId, shelfId);
			set(member);
			setRef(lib);
			m_date = date;
		}
		delete[] title;
		return istr;
	}

	Publication::Publication() 
	{
		setDefault();
	}
	void Publication::setDefault() 
	{
		delete[] m_title;
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		m_date.setToToday();
	}


	Publication::~Publication() 
	{
		delete[] m_title;
	}

	Publication::Publication(const Publication& obj)
	{
		operator=(obj);
	}
	Publication& Publication::operator=(const Publication& obj)
	{
		if (this != &obj && obj) {
			Utils::copyStr(m_title, obj.m_title);
			strcpy(m_shelfId, obj.m_shelfId);
			m_membership = obj.m_membership;
			m_libRef = obj.m_libRef;
			m_date = obj.m_date;
		}
		return *this;
	}

	void Publication::setRef(int value) 
	{
		m_libRef = value;
	}
	void Publication::resetDate() 
	{
		m_date.setToToday();
	}
	// Queries
	char Publication::type()const 
	{
		return 'P';
	}
	bool Publication::onLoan()const 
	{
		return m_membership != 0;
	}
	Date Publication::checkoutDate()const 
	{
		return m_date;
	}
	bool Publication::operator==(const char* title)const 
	{
		return strstr(m_title, title) != nullptr;
	}
	Publication::operator const char* ()const 
	{
		return m_title;
	}
	int Publication::getRef()const 
	{
		return m_libRef;
	}

	bool Publication::conIO(ios& io)const 
	{
		return (&io == &cin || &io == &cout);
	}

	void Publication::set(int member_id)
	{
		if (member_id == 0) {
			m_membership = member_id;
		}
		else
		{
			if (member_id >= 10000 && member_id <= 99999) m_membership = member_id;
		}
	}

	Publication::operator bool()const {
		return (m_title && m_title[0] != '\0' && m_shelfId[0] != '\0');
	}
}









