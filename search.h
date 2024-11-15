#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr, QTextEdit *textEdit = nullptr);
    ~Search();

private slots:
    void on_findNext_clicked();

private:
    Ui::Search *ui;

    QTextEdit *pTextEdit;
};

#endif // SEARCH_H
