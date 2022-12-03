#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
}

SearchForm::~SearchForm()
{
    delete ui;
}
