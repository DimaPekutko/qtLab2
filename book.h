#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    Book();
    void setBook(int id, QString author, QString name, int year, QString publishingHouse, int pageCount);
    int getId();
    QString getAuthor();
    QString getName();
    QString getPublishingHouse();
    int getYear();
    int getPageCount();
private:
    int id;
    QString author;
    QString name;
    QString publishingHouse;
    int year;
    int pageCount;
};

#endif // BOOK_H
