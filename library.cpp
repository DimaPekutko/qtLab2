#include "library.h"

Library::Library()
{
    qDebug() << "Library!!!";
    //initialize();
}

void Library::initialize() {
    qDebug() << "WTF???";
    file = nullptr;
    fileStream = nullptr;
    myBooks = nullptr;
    length = 0;
    myBooks = new Book*[length];
    file = new QFile(fileName);
    fileStream = new QTextStream(file);
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
    }
    QStringList fieldsList;
    while (!fileStream->atEnd()) {
        QString line = fileStream->readLine();
        fieldsList = line.split('$');
        Book *book = new Book();
        book->setBook(fieldsList[0].toInt(),fieldsList[1],fieldsList[2],fieldsList[3].toInt(),fieldsList[4],fieldsList[5].toInt());
        if(!length) {
            myBooks[0] = book;
        }
        else {
            Book **copy = new Book*[length+1];
            for(int i = 0; i < length; i++) {
                copy[i] = myBooks[i];
            }
            copy[length] = book;
            delete[] myBooks;
            myBooks = nullptr;
            myBooks = new Book*[length+1];
            for(int i = 0; i < length+1; i++) {
                myBooks[i] = copy[i];
            }
            delete[] copy;
        }
        length++;
    }

    file->close();
}

void Library::addBook(Book *book) {
    Book **copy = new Book*[length+1];
    for(int i = 0; i < length; i++) {
        copy[i] = myBooks[i];
        qDebug() << myBooks[i]->getAuthor();
    }
    copy[length] = book;
    delete[] myBooks;
    myBooks = nullptr;
    myBooks = new Book*[length+1];
    for(int i = 0; i < length+1; i++) {
        myBooks[i] = copy[i];
    }
    delete[] copy;
    length++;

    int id = book->getId();
    QString author = book->getAuthor();
    QString name = book->getName();
    int year = book->getYear();
    QString publishingHouse = book->getPublishingHouse();
    int pageCount = book->getPageCount();

    QString fileStr = "";
    fileStr.append(QString::number(id));
    fileStr.append('$');
    fileStr.append(author);
    fileStr.append('$');
    fileStr.append(name);
    fileStr.append('$');
    fileStr.append(QString::number(year));
    fileStr.append('$');
    fileStr.append(publishingHouse);
    fileStr.append('$');
    fileStr.append(QString::number(pageCount));
    fileStr.append('\n');

    if (file->open(QIODevice::WriteOnly | QIODevice::Append)) {
        fileStream->operator <<(fileStr);
    }
    file->close();

}
void Library::deleteBook(int id) {
    Book **copy = new Book*[length-1];
    for(int i = 0; i < length; i++) {
        if(myBooks[i]->getId() == id)
            continue;
        copy[i] = myBooks[i];
        qDebug() << myBooks[i]->getAuthor();
    }
    delete[] myBooks;
    myBooks = nullptr;
    myBooks = new Book*[length-1];
    for(int i = 0; i < length; i++) {
        myBooks[i] = copy[i];
    }
    delete[] copy;
    length--;

    QStringList fileDataList;
    QStringList fieldsList;
    if(file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        while(!fileStream->atEnd())
        {
            QString line = fileStream->readLine();
            line.append('\n');
            fileDataList.append(line);
        }
    }
    file->close();

    for(int i = 0; i < fileDataList.length(); i++) {
        fieldsList = fileDataList[i].split('$');
        if(fieldsList[0] == QString::number(id)) {
            fileDataList.removeAt(i);
        }
    }
    if (file->open(QIODevice::WriteOnly)) {
        for(int i = 0; i < fileDataList.length(); i++) {
            fileStream->operator <<(fileDataList[i]);
        }
    }
    file->close();

}
void Library::editBook(int id,QString author,QString name,int year,QString publishingHouse,int pageCount) {
    for(int i = 0; i < length; i++) {
        if(myBooks[i]->getId() == id) {
            myBooks[i]->setBook(id, author, name, year, publishingHouse, pageCount);
            break;
        }
    }

    QStringList fileDataList;
    QStringList fieldsList;
    if(file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        while(!fileStream->atEnd())
        {
            QString line = fileStream->readLine();
            line.append('\n');
            fileDataList.append(line);
        }
    }
    file->close();

    for(int i = 0; i < fileDataList.length(); i++) {
        fieldsList = fileDataList[i].split('$');
        if(fieldsList[0] == QString::number(id)) {
            fileDataList[i] = "";
            fileDataList[i].append(QString::number(id));
            fileDataList[i].append('$');
            fileDataList[i].append(author);
            fileDataList[i].append('$');
            fileDataList[i].append(name);
            fileDataList[i].append('$');
            fileDataList[i].append(QString::number(year));
            fileDataList[i].append('$');
            fileDataList[i].append(publishingHouse);
            fileDataList[i].append('$');
            fileDataList[i].append(QString::number(pageCount));
            fileDataList[i].append('\n');
        }
    }
    if (file->open(QIODevice::WriteOnly)) {
        for(int i = 0; i < fileDataList.length(); i++) {
            fileStream->operator <<(fileDataList[i]);
        }
    }
    file->close();
}
void Library::sortPerYear() {
    for(int i = length-1; i >= 0; i--) {
        for(int j = length-1; j >= i; j--) {
            if(myBooks[j]->getYear() > myBooks[i]->getYear()) {
                std::swap(myBooks[i], myBooks[j]);
            }
        }
    }
}
void Library::setFileName(QString name) {
    fileName = name;
}
Book* Library::getBook(int id) {
    for(int i = 0; i < length; i++) {
        if(myBooks[i]->getId() == id) {
            return myBooks[i];
        }
    }
}
Book** Library::getAllBooks() {
    return myBooks;
}
QList <Book*> Library::findBooksFromWords(QStringList keyWords) {
    QList <Book*> resultList;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j< keyWords.length(); j++) {
            if(myBooks[i]->getAuthor().contains(keyWords[j])) {
                if(!resultList.contains(myBooks[i])) {
                    resultList.append(myBooks[i]);
                    break;
                }
            }
            if(myBooks[i]->getName().contains(keyWords[j])) {
                if(!resultList.contains(myBooks[i])) {
                    resultList.append(myBooks[i]);
                    break;
                }
            }
            if(QString::number(myBooks[i]->getYear()).contains(keyWords[j])) {
                if(!resultList.contains(myBooks[i])) {
                    resultList.append(myBooks[i]);
                    break;
                }
            }
            if(myBooks[i]->getPublishingHouse().contains(keyWords[j])) {
                if(!resultList.contains(myBooks[i])) {
                    resultList.append(myBooks[i]);
                    break;
                }
            }
            if(QString::number(myBooks[i]->getPageCount()).contains(keyWords[j])) {
                if(!resultList.contains(myBooks[i])) {
                    resultList.append(myBooks[i]);
                    break;
                }
            }
        }
    }
    return resultList;
}
