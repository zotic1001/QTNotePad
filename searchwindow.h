#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QWidget>
#include "note.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QSqlDatabase& db, QWidget *parent = nullptr);
    ~SearchWindow();
    Ui::SearchWindow *ui;
    int find_type;
    int current_note;
    QSqlDatabase db;
private slots:

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void SearchSignal(int id);
private:

};

#endif // SEARCHWINDOW_H
