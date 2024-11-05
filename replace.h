#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = nullptr);
    ~Replace();

private:
    Ui::Replace *ui;
};

#endif // REPLACE_H
