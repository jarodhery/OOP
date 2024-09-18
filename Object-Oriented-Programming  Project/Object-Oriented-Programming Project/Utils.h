/***********************************************************************
// OOP244 Utils Module
// File	Utils.h
// Version 
// Date	
// Author	
// Description
//
// Revision History
// -----------------------------------------------------------
// Name Hery Chen Jarod Jian Kang           Date 7/20/2024           Reason
// 
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SENECA_UTILS_H__
#define SENECA_UTILS_H__

#include <iostream>

namespace seneca
{
	class Utils
	{
	public:
		Utils() = delete;

		// This function checks if the next character in the input stream is the specified character. If it is, the character is extracted from the stream.
		static void getChar(std::istream& is, char ch);

		// We made this function in order to checks if the next character in the input stream is a digit. If it is the failbit state flag is set for the stream. Otherwise, the next character is extracted from the stream.
		static void getChar(std::istream& is);

		// This function reads an integer from the input stream within a specified range. If the input is invalid or out of range, it is prompted with the provided message.
		static int getInt(std::istream& is, int min, int max, const char* message = nullptr);

		//This function copies a string from the source to the destination. The destination memory is dynamically allocated and the previous memory is deleted.
		static void copyStr(char*& des, const char* obj);

		// This function reads input from the stream until the specified delimiter is encountered. The input is stored in a dynamically allocated C-string.
		static char* readInput(std::istream& is, char delimeter = '\n');
	};
}

#endif // SENECA_UTILS_H__
