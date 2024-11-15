#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = nullptr, QTextEdit *textEdit = nullptr);
    ~Replace();

private slots:
    void on_findNext_clicked();

    void on_replace_clicked();

    void on_replaceAll_clicked();

private:
    Ui::Replace *ui;

    QTextEdit *pTextEdit;
};

#endif // REPLACE_H
