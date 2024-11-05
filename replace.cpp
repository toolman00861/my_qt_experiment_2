#include "replace.h"
#include "ui_replace.h"

Replace::Replace(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Replace)
{
    ui->setupUi(this);
}

Replace::~Replace()
{
    delete ui;
}
