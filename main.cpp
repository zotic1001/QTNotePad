#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Приложение заметки");

    w.setWindowIconText("11111");
    w.show();
    return a.exec();
}
