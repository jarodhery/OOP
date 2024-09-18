/***********************************************************************
// OOP244 Utils Module
// File	Utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <ctype.h>
#include "Utils.h"
using namespace std;
namespace seneca {
	void Utils::getChar(std::istream& is, char ch) {
		if (is.peek() == ch) is.get();
	}



	void Utils::getChar(std::istream& is) {
		if (isdigit(is.peek())) {
			is.setstate(ios::failbit);
		}
		else {
			is.get();
		}
	}



	int Utils::getInt(std::istream& is, int min, int max, const char* message) {
		int res;
		bool flag = false;
		while (!flag) {
			is >> res;
			if (is && is.peek() == '\n') {
				if (res >= min && res <= max) {
					flag = true;
				}
				else {
					is.ignore(1000, '\n');
					cout << " Try again ";
				}
			}
			else {
				is.clear();
				is.ignore(1000, '\n');
				if (message) cout << message;
			}
		}
		return res;
	}


	void Utils::copyStr(char*& des, const char* obj) {
		delete[] des;
		des = new char[strlen(obj) + 1];
		strcpy(des, obj);
	}


	char* Utils::readInput(istream& is, char delimeter) {
		char* str{};
		string read;
		getline(is, read, delimeter);
		if (is) {
			str = new char[strlen(read.c_str()) + 1];
			strcpy(str, read.c_str());
		}
		return str;
	}
}