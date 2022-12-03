#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "ui_searchform.h"
#include <QTime>
#include <QString>
#include <QDateTime>
#include <QChar>
#include <windows.h>
#include <stdio.h>
#include "note.h"
#include "searchwindow.h"
//#include "ui_searchwindow.h"
#include <QMap>
#include <dialog.h>
#include <stdlib.h>

void MainWindow::UpdateList() {
    ui->listWidget->clear();
    QSqlQuery query = QSqlQuery(db);
    if (!query.exec("select * from data")) {
        qDebug() << "Failed db connection";
    }
    QListWidgetItem* i;
    while (query.next()) {
    QString s = query.record().value(0).toString() + " " + query.record().value(1).toString() + " "  + query.record().value(2).toString() + " " +  query.record().value(5).toString() + " " + query.record().value(3).toString();
    QListWidgetItem* i = new QListWidgetItem(s);
    ui->listWidget->addItem(i);}
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("data.db");
    db.setUserName("root");
    db.setPassword("1");

    if (!db.open()) {
        qDebug () << "db connection failed";
    }
    else {
        qDebug () << "db connection succes";
    }
    this->controller = new NoteControler(db);
    this->UpdateList();

}

void MainWindow::ShowSelectNote(int id)
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select * from data where id=?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug("invalid query");
    }
    while (query.next()) {
    auto dt = QDateTime::fromString(query.record().value(3).toString());
    Note note = Note(query.record().value(1).toString(), //name
                     query.record().value(2).toString(), //author
                     dt, //create_time
                     query.record().value(4).toString(),
                     query.record().value(5).toString().split(" "));
    ui->lineEdit_3->setText(note.name);
    ui->lineEdit_4->setText(dt.toString());
    ui->lineEdit->setText(note.tags.join(" "));
    ui->lineEdit_2->setText(note.author);
    ui->textEdit->setText(note.text);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}


void MainWindow::on_pushButton_clicked()
{
    this->searchw = new SearchWindow(this->db);
    this->setWindowTitle("Поиск заметки");
    this->searchw->show();
    this->searchw->setAttribute(Qt::WA_DeleteOnClose);
    connect(searchw, SIGNAL(SearchSignal(int)), this, SLOT(SearchSlot(int)));
}
void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->listWidget->selectedItems().isEmpty()) {
        auto text = ui->listWidget->currentItem()->text();
        if (!controller->Delete(ui->listWidget->currentItem()->text().split(" ")[0].toInt())) {
            qDebug("delete failed");
        }
        this->UpdateList();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    QDateTime dt = QDateTime::currentDateTime();
    auto note = new Note(
                ui->lineEdit_3->text(), //name
                ui->lineEdit_2->text(), //author
                dt, // create time
                ui->textEdit->toPlainText(), // text
                ui->lineEdit->text().split(" ") //tags
                );

    if (note->text == "") {
        Dialog d;
        d.setWindowTitle("Ошибочка вышла");
        d.exec();
        return;
    }
    QStringList current_item_text_split;
    if (note->author == "") {
        wchar_t buffer[256];
        unsigned long size = 256;
        GetComputerName( buffer, &size );
        std::wstring ws(buffer);
        std::string str(ws.begin(), ws.end());
        note->author = QString::fromUtf8(str);
    }
    if (note->tags.size() == 1) {
        QMap<QString, int> most_used_words;
        auto splited_text = note->text.split(" ");
        for (int i=0; i<splited_text.size(); i++) {
            if (splited_text[i].size() > 3)
            {
            most_used_words[splited_text[i]] = 0; }
        }
        for (int i=0; i<splited_text.size(); i++) {
            if (splited_text[i].size() > 3)
            {
            most_used_words[splited_text[i]]++;
            }
        }
        QString mx;
        int mxvalue=0;
        for (int i=0; i<splited_text.size(); i++) {
            if (most_used_words[splited_text[i]] > mxvalue)
            {
            mx = splited_text[i];
            mxvalue = most_used_words[splited_text[i]];
            }
        }
        note->tags.append(mx);
    }
    if (note->name == "") {
        note->name = note->text.split(" ")[0];
    }
    if (!ui->listWidget->selectedItems().isEmpty()) {
    auto current_item_text_split = ui->listWidget->currentItem()->text().split(" ");
    if (current_item_text_split[1] == note->name) {
        if (!controller->Update(*note, current_item_text_split[0].toInt())){
            qDebug() << "Update not succesful";};
    }
    else
    {

        if(!controller->Serialize(*note)) {
            qDebug() << "Serialize not succesful";}

    }}
    else {
        if(!controller->Serialize(*note)) {
            qDebug() << "Serialize not succesful";}

    }
    delete note;
    this->UpdateList();

}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    auto text = ui->listWidget->currentItem()->text();
    QString id_s = "";
    int j=0;
    while (text[j] != QChar(' ')) {
        id_s += text[j];
        j++;
    }
    ShowSelectNote(id_s.toInt());
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
}

void MainWindow::SearchSlot(int id)
{
    ShowSelectNote(id);
}
