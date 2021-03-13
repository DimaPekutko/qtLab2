#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>

#include "editwindow.h"
#include "library.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_view_btn_clicked();

    void on_clear_view_btn_clicked();

    void on_delete_selected_clicked();

    void on_add_btn_clicked();

    void on_edit_btn_clicked();

    void on_sort_btn_clicked();

    void on_key_word_btn_clicked();

    void on_key_word_input_textChanged();

    void on_choose_btn_clicked();

private:
    Ui::MainWindow *ui;
    //bool isDarkTheme = false;
    Library *library;
    QListWidget *viewList;
};
#endif // MAINWINDOW_H
