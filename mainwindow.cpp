#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    library = new Library();
    viewList = ui->view_list;
    ui->clear_view_btn->click();

    ui->view_btn->hide();
    ui->clear_view_btn->hide();
    ui->edit_btn->hide();
    ui->delete_selected->hide();
    ui->add_btn->hide();
    ui->sort_btn->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_view_btn_clicked()
{
    ui->clear_view_btn->click();
//    library->initialize();
    Book ** books = library->getAllBooks();
    for(int i = 0; i < library->length; i++) {
        QListWidgetItem *item = new QListWidgetItem();
        QString itemText = "";

        itemText.append(QString::number(books[i]->getId()));
        itemText.append("\t");
        itemText.append(books[i]->getAuthor());
        itemText.append("\t");
        itemText.append(books[i]->getName());
        itemText.append("\t");
        itemText.append(QString::number(books[i]->getYear()));
        itemText.append("\t");
        itemText.append(books[i]->getPublishingHouse());
        itemText.append("\t");
        itemText.append(QString::number(books[i]->getPageCount()));

        item->setText(itemText);
        item->setData(Qt::UserRole, books[i]->getId());
        viewList->addItem(item);
        //viewList->addItem(item);
    }
}


void MainWindow::on_clear_view_btn_clicked()
{
    viewList->clear();
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("id\tAuthor\tName\tYear\tPublish\tPages");
    item->setData(Qt::UserRole, 0);
    item->setBackground(QBrush(Qt::lightGray));
    viewList->addItem(item);
}

void MainWindow::on_delete_selected_clicked()
{
    //QDialog dialog(this);
    if(viewList->selectedItems().count()) {
        int deleteId = viewList->selectedItems()[0]->data(Qt::UserRole).toInt();
        if(!deleteId) // header view list element have id 0
            return;
        library->deleteBook(deleteId);
        ui->view_btn->click();
    }
}

void MainWindow::on_add_btn_clicked()
{
    EditWindow *editWindow = new EditWindow;
    editWindow->setLibrary(library);
    editWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_edit_btn_clicked()
{
    if(viewList->selectedItems().count()) {
        int id = viewList->selectedItems()[0]->data(Qt::UserRole).toInt();
        if(!id) // header view list element have id 0
            return;
        Book *book = library->getBook(id);
        EditWindow *editWindow = new EditWindow;
        editWindow->setLibrary(library, true, book);
        editWindow->show();
    }
}

void MainWindow::on_sort_btn_clicked()
{
    library->sortPerYear();
    ui->view_btn->click();
}

void MainWindow::on_key_word_btn_clicked()
{
    //qApp->quit();
    //QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    QString keyWords = ui->key_word_input->toPlainText();
    QStringList keyWordsList;
    QStringList keyWordsListGood;
    if(keyWords.count()) {
        keyWordsList = keyWords.split(' ');
        for(int i = 0; i < keyWordsList.length(); i++) {
            if(keyWordsList[i].count()) {
                keyWordsListGood.append(keyWordsList[i]);
            }
        }

        QList <Book*> findedList = library->findBooksFromWords(keyWordsListGood);
        ui->clear_view_btn->click();
        if(!findedList.length()) {
            viewList->addItem("\tNo results");
            return;
        }

        for(int i = 0; i < findedList.length(); i++) {
            QListWidgetItem *item = new QListWidgetItem();
            QString itemText = "";

            itemText.append(QString::number(findedList[i]->getId()));
            itemText.append("\t");
            itemText.append(findedList[i]->getAuthor());
            itemText.append("\t");
            itemText.append(findedList[i]->getName());
            itemText.append("\t");
            itemText.append(QString::number(findedList[i]->getYear()));
            itemText.append("\t");
            itemText.append(findedList[i]->getPublishingHouse());
            itemText.append("\t");
            itemText.append(QString::number(findedList[i]->getPageCount()));

            item->setText(itemText);
            item->setData(Qt::UserRole, findedList[i]->getId());
            viewList->addItem(item);
            //viewList->addItem(item);
        }
    }
    else {
        ui->view_btn->click();
        //viewList->addItem("\tNo results");
    }
}

void MainWindow::on_key_word_input_textChanged()
{
    ui->key_word_btn->click();
}

void MainWindow::on_choose_btn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "choose your file", "~");
    if(fileName.count()) {
        if(!fileName.contains(".txt")) {
            QMessageBox::warning(this, "Can not open your file!","File must have txt extension.");
            return;
        }
        ui->label_2->setText(fileName);
        library->setFileName(fileName);

        library->initialize();

        ui->view_btn->show();
        ui->clear_view_btn->show();
        ui->edit_btn->show();
        ui->delete_selected->show();
        ui->add_btn->show();
        ui->sort_btn->show();

        ui->view_btn->click();
    }
}
