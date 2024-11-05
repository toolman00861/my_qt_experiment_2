#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AboutDialog.h"
#include "search.h"
#include "replace.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StatusLabel.setMaximumHeight(150);
    StatusLabel.setText("length: " + QString::number(0) + "   lines: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&StatusLabel);

    StatusCursorLabel.setMaximumWidth(150);
    StatusCursorLabel.setText("Ln :" + QString::number(0) + "   Col: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&StatusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("胡攀"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_About_triggered()
{
    AboutDialog am;
    am.exec();
}


void MainWindow::on_FInd_triggered()
{
    Search s;
    s.exec();
}


void MainWindow::on_replace_triggered()
{
    Replace r;
    r.exec();
}

