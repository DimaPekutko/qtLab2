#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

class Library
{
public:
    Library();
    void initialize();
    void addBook(Book *book);
    void deleteBook(int id);
    void editBook(int id,QString author,QString name,int year,QString publishingHouse,int pageCount);
    void sortPerYear();
    void setFileName(QString name);
    Book* getBook(int id);
    Book ** getAllBooks();
    QList <Book*> findBooksFromWords(QStringList keyWords);
    int length;
private:
    QString fileName = "";
    Book **myBooks;
    QFile *file;
    QTextStream *fileStream;
};

#endif // LIBRARY_H
