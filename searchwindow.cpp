#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QDebug>
#include <QSqlQuery>
SearchWindow::SearchWindow(QSqlDatabase& db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    this->db = db;
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::on_radioButton_clicked(bool checked)
{
    if (checked) {
        this->find_type = 0;
    }
}


void SearchWindow::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        this->find_type = 1;
    }
}


void SearchWindow::on_radioButton_3_clicked(bool checked)
{
    if (checked) {
        this->find_type = 2;
    }
}


void SearchWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QSqlQuery query = QSqlQuery(db);
    if (find_type == 0) {
        query.prepare("select * from data where name=?");
        query.addBindValue(ui->lineEdit->text());
        if (!query.exec()) {
            qDebug() << "Failed db connection";
        }
        while (query.next()) {
        QString s = query.record().value(0).toString() + " " + query.record().value(1).toString() + " "  + query.record().value(2).toString() + " " +  query.record().value(5).toString() + " " + query.record().value(3).toString();
        QListWidgetItem* i = new QListWidgetItem(s);
        ui->listWidget->addItem(i);}
    }
    if (find_type == 1) {
        query.prepare("select * from data where author=?");
        query.addBindValue(ui->lineEdit->text());
        if (!query.exec()) {
            qDebug() << "Failed db connection";
        }
        while (query.next()) {
        QString s = query.record().value(0).toString() + " " + query.record().value(1).toString() + " "  + query.record().value(2).toString() + " " +  query.record().value(5).toString() + " " + query.record().value(3).toString();
        QListWidgetItem* i = new QListWidgetItem(s);
        ui->listWidget->addItem(i);}
    }
    if (find_type == 2) {
        query.prepare("select * from data");

        if (!query.exec()) {
            qDebug() << "Failed db connection";
        }
        while (query.next()) {
        if (query.record().value(5).toString().split(" ").contains(ui->lineEdit->text())
                && query.record().value(5).toString() != "" && ui->lineEdit->text() != ""){
        QString s = query.record().value(0).toString() + " " + query.record().value(1).toString() + " "  + query.record().value(2).toString() + " " +  query.record().value(5).toString() + " " + query.record().value(3).toString();
        QListWidgetItem* i = new QListWidgetItem(s);
        ui->listWidget->addItem(i);}
        }
    }

}


void SearchWindow::on_pushButton_2_clicked()
{
    current_note = ui->listWidget->currentItem()->text().split(" ")[0].toInt();
    emit this->SearchSignal(current_note);
    this->close();
}
