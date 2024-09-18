#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include "LibApp.h"
#include "Publication.h"
#include "PublicationSelector.h"

using namespace std;

namespace seneca {

    LibApp::LibApp(const char* filename)
        : m_changed(false),
        m_mainMenu("Seneca Library Application:\n1- Add New Publication\n2- Remove Publication\n3- Checkout publication from library\n4- Return publication to library\n0- Exit"),
        m_exitMenu("Changes have been made to the data, what would you like to do?\n1- Save changes and exit\n2- Cancel and go back to the main menu\n0- Exit without saving"),
        m_Publication_Type("Choose the type of publication:\n1- Book\n2- Publication\n0- Exit")
    {
        strcpy(m_filename, filename);

        for (int i = 0; i < SENECA_LIBRARY_CAPACITY; i++) {
            PPA[i] = nullptr;
        }

        NOLP = 0;
        LLRN = 0;

        load();
    }

    bool LibApp::confirm(const char* message) {
        int choice;
        cout << message << endl;
        cout << "1- Yes\n0- No\n> ";
        cin >> choice;
        return choice == 1;
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream infile(m_filename);

        char type;
        int i = 0;

        while (i < SENECA_LIBRARY_CAPACITY && infile >> type) {
            infile.ignore();
            if (type == 'P') {
                PPA[i] = new Publication;
            }
            else if (type == 'B') {
                PPA[i] = new Book;
            }

            if (PPA[i]) {
                infile >> *PPA[i];
                NOLP++;
                LLRN = PPA[i]->getRef();
            }
            i++;
        }
        infile.close();
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream outfile(m_filename);

        for (int i = 0; i < NOLP; i++) {
            if (PPA[i] && PPA[i]->getRef() != 0) {
                outfile << *PPA[i] << endl;
            }
        }
        outfile.close();
    }

    int LibApp::search(int select) {
        int lib_ref = 0;
        char search_title[256];
        int selection_type;
        bool found = false;

        cout << m_Publication_Type << endl;
        cout << "> ";
        cin >> selection_type;
        cin.ignore();

        if (selection_type == 0) {
            cout << "Aborted!" << endl;
            return 0;
        }

        cout << "Publication Title: ";
        cin.getline(search_title, 256);

        PublicationSelector selector("Select one of the following found matches:", 10);

        for (int i = 0; i < NOLP; i++) {
            if (PPA[i] && strstr(static_cast<const char*>(*PPA[i]), search_title)) {
                if ((selection_type == 1 && PPA[i]->type() == 'B') ||
                    (selection_type == 2 && PPA[i]->type() == 'P')) {
                    if ((select == 1) ||
                        (select == 2 && PPA[i]->onLoan()) ||
                        (select == 3 && !PPA[i]->onLoan())) {
                        selector << *PPA[i];
                        found = true;
                    }
                }
            }
        }

        if (!found) {
            cout << "No matches found!" << endl;
            return 0;
        }

        selector.sort();
        lib_ref = selector.run();

        if (lib_ref > 0) {
            cout << *getPub(lib_ref) << endl;
        }
        else {
            cout << "Aborted!" << endl;
        }

        return lib_ref;
    }

    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < NOLP; i++) {
            if (PPA[i] && PPA[i]->getRef() == libRef) {
                return PPA[i];
            }
        }
        return nullptr;
    }

    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int ref = search(2);
        if (ref > 0) {
            if (confirm("Return Publication?")) {
                Date today;
                int days = today - getPub(ref)->checkoutDate();

                if (days > SENECA_MAX_LOAN_DAYS) {
                    double fine = (days - SENECA_MAX_LOAN_DAYS) * 0.50;
                    cout << fixed << setprecision(2) << "Please pay $" << fine << " penalty for being " << (days - SENECA_MAX_LOAN_DAYS) << " days late!" << endl;
                }

                getPub(ref)->set(0);
                cout << "Publication returned" << endl;
                m_changed = true;
            }
        }
    }

    void LibApp::newPublication() {
        if (NOLP < SENECA_LIBRARY_CAPACITY) {
            cout << "Adding new publication to the library" << endl;
            int pubType;
            Publication* pub = nullptr;

            cout << m_Publication_Type << endl;
            cout << "> ";
            cin >> pubType;
            cin.ignore();

            if (pubType == 1) {
                pub = new Book;
            }
            else if (pubType == 2) {
                pub = new Publication;
            }
            else {
                cout << "Aborted!" << endl;
                return;
            }

            cin >> *pub;

            if (confirm("Add this publication to the library?")) {
                LLRN++;
                pub->setRef(LLRN);
                PPA[NOLP++] = pub;
                m_changed = true;
                cout << "Publication added" << endl;
            }
            else {
                cout << "Aborted!" << endl;
                delete pub;
            }
        }
        else 
        {
            cout << "Library is at its maximum capacity!" << endl;
        }
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int ref = search(1);
        if (ref > 0 && confirm("Remove this publication from the library?")) {
            getPub(ref)->setRef(0);
            m_changed = true;
            cout << "Publication removed" << endl;
        }
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int ref = search(3);
        if (ref > 0 && confirm("Check out publication?")) {
            int memberID;
            do {
                cout << "Enter Membership number: ";
                cin >> memberID;
                if (memberID < 10000 || memberID > 99999) {
                    cout << "Invalid membership number, try again: ";
                    cin.clear();
                    cin.ignore(2000, '\n');
                }
            } while (memberID < 10000 || memberID > 99999);

            getPub(ref)->set(memberID);
            m_changed = true;
            cout << "Publication checked out" << endl;
        }
    }

    void LibApp::run() {
        bool exit = false;
        int choice;

        do {
            cout << m_mainMenu << endl;
            cout << "> ";
            cin >> choice;

            switch (choice) {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            case 0:
                if (m_changed) {
                    cout << m_exitMenu << endl;
                    cout << "> ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        save();
                        exit = true;
                        break;
                    case 2:
                        exit = false;
                        break;
                    case 0:
                        if (confirm("This will discard all the changes. Are you sure?")) {
                            exit = true;
                        }
                        break;
                    }
                }
                else {
                    exit = true;
                }
                break;
            }
        } while (!exit);

        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }

    LibApp::~LibApp() {
        for (int i = 0; i < NOLP; i++) {
            if (PPA[i]) {
                delete PPA[i];
            }
        }
    }

}
