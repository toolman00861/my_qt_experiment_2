#include "search.h"
#include "ui_search.h"
#include <QMessageBox>

Search::Search(QWidget *parent, QTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::Search)
{
    ui->setupUi(this);
    this->pTextEdit = textEdit;
}

Search::~Search()
{
    delete ui;
}

void Search::on_findNext_clicked()
{
    QString target = ui->searchText->text();
    QString text = pTextEdit->toPlainText();

    // 定义当前指针
    QTextCursor cur = pTextEdit->textCursor();
    int index = -1;

    // 是否区分大小写
    Qt::CaseSensitivity findMode = Qt::CaseSensitive;
    if(ui->caseSensitive->isChecked()){
        findMode = Qt::CaseSensitive;
    }else{
        findMode = Qt::CaseInsensitive;
    }

    //区分从下往上还是从上往下搜索
    if(ui->findUp->isChecked()){
        index = text.lastIndexOf(target, cur.position() - text.length() - 1, findMode);
    }else{
        index = text.indexOf(target, cur.position(), findMode);
    }

    if(index>=0){
        if(ui->findUp->isChecked()){
            cur.setPosition(index + target.length());
            cur.setPosition(index, QTextCursor::KeepAnchor);
        }else{
            cur.setPosition(index);
            cur.setPosition(index + target.length(), QTextCursor::KeepAnchor);
        }

        //保存当前游标位置
        pTextEdit->setTextCursor(cur);
    }else{
        QMessageBox::warning(this, "提示", "未找到");
    }
}

