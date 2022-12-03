#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QListWidgetItem>
#include "notecontroler.h"
#include "searchwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void ShowSelectNote(int id);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_4_clicked();
    void SearchSlot(int id);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    NoteControler* controller;
    SearchWindow* searchw;
    void UpdateList();
};
#endif // MAINWINDOW_H
