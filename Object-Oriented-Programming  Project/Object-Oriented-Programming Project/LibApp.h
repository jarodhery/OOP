#ifndef SENECA_LIB_APP_H
#define SENECA_LIB_APP_H

#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "Lib.h"
#include "PublicationSelector.h"

namespace seneca
{
	class LibApp {


		bool m_changed;

		char m_filename[256];

		Menu m_mainMenu;

		Menu m_exitMenu;

		Publication* PPA[SENECA_LIBRARY_CAPACITY]; // size of SENECA_LIBRARY_CAPACITY

		int NOLP; // Num of Publication  loaded

		int LLRN; // Last Library Reference Num = read from the data file. will use to assign new library reference num. (incrementer) 

		Menu m_Publication_Type;


		// Member Function

		bool confirm(const char* message);

		Publication* getPub(int libRef);

		void load(); 
		void save();
		int search(int select); 

		void returnPub();

		void newPublication();

		void removePublication(); 

		void checkOutPub(); 

	public:
		LibApp(const char* filename);
		void run();
		~LibApp();

	};




}

#endif