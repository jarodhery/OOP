/***********************************************************************
// OOP244 Menu Module
// File	Menu.h
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

#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__
#include <iostream>

const unsigned int MAX_MENU_ITEMS = 20;

namespace seneca {
    class Menu;

    class MenuItem {
    private:
        char* m_content;
        MenuItem(const char* itemContent = nullptr);
        ~MenuItem();
        MenuItem(const MenuItem&) = delete;
        MenuItem& operator=(const MenuItem&) = delete;
        operator bool() const;
        operator const char* () const;
        void display(std::ostream& os) const;

        friend class Menu;
    };



    class Menu {
    private:
        MenuItem* m_title;
        MenuItem* m_items[MAX_MENU_ITEMS];
        int itemCount;

    public:
        Menu(const char* menuTitle = nullptr);
        ~Menu();
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
        void titleDisplay(std::ostream& os) const;
        void display(std::ostream& os) const;
        unsigned int run() const;
        Menu& operator<<(const char* menuitemContent);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        const char* operator[](unsigned int index) const;
        unsigned int operator~() const;
        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
    };


}
#endif // SENECA_MENU_H__