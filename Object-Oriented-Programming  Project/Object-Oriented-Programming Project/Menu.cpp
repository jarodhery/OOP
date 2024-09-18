/***********************************************************************
// OOP244 Menu Module
// File	Menu.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name Hery Chen Jarod Jian Kang      Date 7/1/2024            Reason Menu.cpp
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <iomanip>

namespace seneca
{
    MenuItem::MenuItem(const char* item) 
    {
        if (item && item[0] != '\0') 
        {
            m_content = new char[strlen(item) + 1];
            strcpy(m_content, item);
        }
        else 
        {
            m_content = nullptr;
        }
    }

    MenuItem::~MenuItem() 
    {
        delete[] m_content;
    }

    MenuItem::operator bool() const 
    {
        return m_content != nullptr;
    }

    MenuItem::operator const char* () const 
    {
        return m_content;
    }

    void MenuItem::display(std::ostream& os) const 
    {
        if (*this) 
        {
            os << m_content;
        }
    }

    Menu::Menu(const char* menuTitle) : m_title(nullptr), itemCount(0) 
    {
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; ++i) 
        {
            m_items[i] = nullptr;
        }
        if (menuTitle) 
        {
            m_title = new MenuItem(menuTitle);
        }
    }

    Menu::~Menu() 
    {
        delete m_title;
        for (int i = 0; i < itemCount; ++i) 
        {
            delete m_items[i];
        }
    }

    void Menu::titleDisplay(std::ostream& os) const 
    {
        if (m_title) 
        {
            m_title->display(os);
        }
    }

    void Menu::display(std::ostream& os) const {
        titleDisplay(os);
        os << std::endl;
        for (int i = 0; i < itemCount; ++i) {
            os << " " << std::setw(2) << std::right << i + 1 << "- ";
            m_items[i]->display(os);
            os << std::endl;
        }
        os << " 0- Exit" << std::endl;
        os << "> ";
    }

    unsigned int Menu::run() const 
    {
        unsigned int selection;
        bool validation = false;
        display(std::cout);
        while (!validation) 
        {
            std::cin >> selection;
            if (std::cin.fail() || selection > itemCount) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Selection, try again: ";
            }
            else 
            {
                validation = true;
            }
        }
        return selection;
    }

    Menu& Menu::operator<<(const char* menuitem) 
    {
        if (itemCount < MAX_MENU_ITEMS) 
        {
            m_items[itemCount++] = new MenuItem(menuitem);
        }
        return *this;
    }

    Menu::operator int() const 
    {
        return itemCount;
    }

    Menu::operator unsigned int() const 
    {
        return itemCount;
    }

    Menu::operator bool() const 
    {
        return itemCount > 0;
    }

    const char* Menu::operator[](unsigned int index) const 
    {
        return *m_items[index % itemCount];
    }

    unsigned int Menu::operator~() const 
    {
        return run();
    }

    std::ostream& operator<<(std::ostream& os, const Menu& menu) 
    {
        menu.titleDisplay(os);
        return os;
    }
}
