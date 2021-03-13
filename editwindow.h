#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QDebug>

#include "library.h"
#include "book.h"

namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    void setLibrary(Library *library, bool editMode=false, Book *book=nullptr);
    ~EditWindow();

private slots:
    void on_main_btn_clicked();

private:
    Ui::EditWindow *ui;
    Library *library;
    Book *selectedBook = nullptr;
    bool editMode = false;
};

#endif // EDITWINDOW_H
