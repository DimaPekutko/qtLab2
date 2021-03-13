#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
}

void EditWindow::setLibrary(Library *library, bool editMode, Book* book) {
    this->library = library;
    this->editMode = editMode;
    this->selectedBook = book;
    if(editMode) {
        ui->main_label->setText("Edit book");
        ui->main_btn->setText("Edit book");
        ui->author_input->setText(book->getAuthor());
        ui->name_input->setText(book->getName());
        ui->year_input->setText(QString::number(book->getYear()));
        ui->ph_input->setText(book->getPublishingHouse());
        ui->page_count_input->setText(QString::number(book->getPageCount()));
    }
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::on_main_btn_clicked()
{
    QString author = ui->author_input->toPlainText();
    QString name = ui->name_input->toPlainText();
    QString strYear = ui->year_input->toPlainText();
    QString publishingHouse = ui->ph_input->toPlainText();
    QString strPageCount = ui->page_count_input->toPlainText();

    int id;
    int year = strYear.toInt();
    int pageCount = strPageCount.toInt();

    if(!author.count()) return;
    if(!name.count()) return;
    if(!year) return;
    if(!publishingHouse.count()) return;
    if(!pageCount) return;
    if(author.contains("$") || name.contains("$") || publishingHouse.contains("$")) {
        return;
    }

    if(editMode) {
        id = selectedBook->getId();
        library->editBook(id,author,name,year,publishingHouse,pageCount);
    }
    else {
        int maxId = library->getAllBooks()[library->length-1]->getId();
        qDebug() << "maxid=" << maxId;
        id = maxId+1;
        Book *book = new Book();
        book->setBook(id,author,name,year,publishingHouse,pageCount);
        library->addBook(book);
    }
    this->hide();
    qDebug() << "success";
}
