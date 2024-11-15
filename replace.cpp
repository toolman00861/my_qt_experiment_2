#include "replace.h"
#include "ui_replace.h"
#include <QMessageBox>

Replace::Replace(QWidget *parent, QTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::Replace)
{
    ui->setupUi(this);
    this->pTextEdit = textEdit;
}

Replace::~Replace()
{
    delete ui;
}

void Replace::on_findNext_clicked()
{
    QString target = ui->searchText->text();
    QString text = pTextEdit->toPlainText();

    // 定义当前指针
    QTextCursor cur = pTextEdit->textCursor();
    int index = -1;

    // 是否区分大小写
    Qt::CaseSensitivity findMode = Qt::CaseSensitive;
    if(ui->caseSensitivive->isChecked()){
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


void Replace::on_replace_clicked()
{
    QString target = ui->searchText->text();
    QString text = pTextEdit->toPlainText();
    QString replaceText = ui->replaceText->text();

    if( (pTextEdit!=nullptr) && (target!="") && (replaceText!="")){
        QString selectText = pTextEdit->textCursor().selectedText();
        if( selectText==target){
            on_findNext_clicked();
        }
    }
}


void Replace::on_replaceAll_clicked()
{
    QString target = ui->searchText->text();
    QString text = pTextEdit->toPlainText();
    QString replaceText = ui->replaceText->text();

    // 是否区分大小写
    Qt::CaseSensitivity findMode = Qt::CaseSensitive;
    if(ui->caseSensitivive->isChecked()){
        findMode = Qt::CaseSensitive;
    }else{
        findMode = Qt::CaseInsensitive;
    }

    // 替换文本并更新
    if( (pTextEdit!=nullptr) && (target!="") && (replaceText!="")){
        text.replace(target, replaceText, findMode);
        pTextEdit->clear();
        pTextEdit->setText(text);
    }

}

