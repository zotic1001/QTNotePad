#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QMainWindow>

namespace Ui {
class SearchForm;
}

class SearchForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

private:
    Ui::SearchForm *ui;
};

#endif // SEARCHFORM_H
