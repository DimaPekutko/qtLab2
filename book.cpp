#include "book.h"

Book::Book() {

}

void Book::setBook(int id, QString author, QString name, int year, QString publishingHouse, int pageCount) {
    this->id = id;
    this->author = author;
    this->name = name;
    this->year = year;
    this->publishingHouse = publishingHouse;
    this->pageCount = pageCount;
}


int Book::getId() {
    return id;
}

QString Book::getAuthor() {
    return author;
}
QString Book::getName() {
    return name;
}
QString Book::getPublishingHouse() {
    return publishingHouse;
}
int Book::getYear() {
    return year;
}
int Book::getPageCount(){
    return pageCount;
}
