#ifndef PUBSELECT_H
#define PUBSELECT_H
#include "Publication.h"

namespace seneca 
{
    class PublicationSelector {
        const int allocationUnit{ 10 };
        const int m_pageSize{ };
        const Publication** m_pub{};
        char m_title[81]{};
        int m_currentPage{ 1 };
        int m_arraySize{};
        int m_noOfPubs{};
        void display(int page)const;
        int getSelectedLibRef()const;
    public:
        PublicationSelector(const char* title = "Select a publication: ", int pageSize = 15);

        ~PublicationSelector();

        PublicationSelector(const PublicationSelector&) = delete;

        PublicationSelector& operator=(const PublicationSelector&) = delete;

        PublicationSelector& operator<<(const Publication* pub);

        PublicationSelector& operator<<(const Publication& pub);

        operator bool()const;

        void reset();

        void sort();

        int run();

    };
}

#endif