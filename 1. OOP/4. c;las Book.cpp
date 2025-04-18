// File: Book.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    // Default constructor
    Book()
    {
        title = nullptr;
        authors = nullptr;
        publishingYear = 0;
    }

    // Parameterized constructor
    Book(const char *title, const char *authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);

        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);

        this->publishingYear = publishingYear;
    }

    // Copy constructor (Deep Copy)
    Book(const Book &book)
    {
        title = new char[strlen(book.title) + 1];
        strcpy(title, book.title);

        authors = new char[strlen(book.authors) + 1];
        strcpy(authors, book.authors);

        publishingYear = book.publishingYear;
    }

    // Destructor to release memory
    ~Book()
    {
        delete[] title;
        delete[] authors;
    }

    // Setter for title
    void setTitle(const char *title)
    {
        delete[] this->title; // Free existing memory
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    // Setter for authors
    void setAuthors(const char *authors)
    {
        delete[] this->authors; // Free existing memory
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    // Setter for publishingYear
    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    // Getter for title
    char *getTitle() const
    {
        return title;
    }

    // Getter for authors
    char *getAuthors() const
    {
        return authors;
    }

    // Getter for publishingYear
    int getPublishingYear() const
    {
        return publishingYear;
    }

    // Print book details
    void printBook()
    {
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};
