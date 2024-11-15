#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AboutDialog.h"
#include "search.h"
#include "replace.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QPlainTextEdit>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textChange = false;

    StatusLabel.setMaximumHeight(150);
    StatusLabel.setText("length: " + QString::number(0) + "   lines: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&StatusLabel);

    StatusCursorLabel.setMaximumWidth(150);
    StatusCursorLabel.setText("Ln :" + QString::number(0) + "   Col: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&StatusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("胡攀"));
    ui->statusbar->addPermanentWidget(author);

    ui->Copy->setEnabled(false);
    ui->Cut->setEnabled(false);
    ui->Undo->setEnabled(false);
    ui->Redo->setEnabled(false);

    on_AutoEnter_triggered();
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
    Search s(this, ui->textEdit);
    s.exec();
}


void MainWindow::on_replace_triggered()
{
    Replace r(this, ui->textEdit);
    r.exec();
}


void MainWindow::on_NewFIle_triggered()
{

    if(!userEditComfirm()){
        return;
    }

    FilePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本"));

    textChange = false;
}


void MainWindow::on_openFile_triggered()
{
    if(!userEditComfirm()){
        return;
    }


    QString fileName = QFileDialog::getOpenFileName(
        this,
        "打开文件夹",
        ".",
        tr("Text file (*.txt) ;; All (*.*))")
    );
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"错误", "打开文件失败");
        return;
    }

    FilePath = fileName;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(fileName).absoluteFilePath());

    textChange = false;

}


void MainWindow::on_saveFile_triggered()
{
    if(FilePath == ""){
        on_saveAs_triggered();
        return;
    }
    QFile file(FilePath);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        //如果保存失败，就另保存
        on_saveAs_triggered();
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(FilePath).absoluteFilePath());
    textChange = false;
}


void MainWindow::on_saveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "保存文件",
        ".",
        tr("Text file (*.txt) ;; All (*.*))")
        );

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "错误", "打开保存文件夹失败");
        return;
    }

    FilePath = fileName;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(FilePath).absoluteFilePath());
    textChange = false;
}


void MainWindow::on_textEdit_textChanged()
{
    if(!textChange){
        this->setWindowTitle("*" + this->windowTitle());
        this->textChange = true;
    }

    // 更新状态栏
    int len = ui->textEdit->toPlainText().length();
    int lines = ui->textEdit->document()->lineCount();
    StatusLabel.setText("length: " + QString::number(len) + "   lines: "+QString::number(lines));

}

bool MainWindow::userEditComfirm()
{
    /*
        检测用户是否更改过文件
        如果更改了，就要提示是否保存内容，如果没有就保存
    */
    if(textChange){
        QString path = "";
        if(FilePath==""){
            path = "无标题.txt";
        }else{
            path = FilePath;
        }

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("是否保存？");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到：") + "/" + path + "/?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);

        int r = msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_saveFile_triggered();
            break;
        case QMessageBox::No:
            textChange = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }

    return true;
}


void MainWindow::on_Undo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_Redo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_Cut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_Copy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_Paste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->Copy->setEnabled(b);
    ui->Cut->setEnabled(b);
}


void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->Redo->setEnabled(b);
}


void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->Undo->setEnabled(b);
}


void MainWindow::on_AutoEnter_triggered()
{
    QTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if(mode == QTextEdit::NoWrap){
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
        ui->AutoEnter->setChecked(false);
    }else{
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        ui->AutoEnter->setChecked(true);
    }
}


void MainWindow::on_FontFormat_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);

    if(ok){
        ui->textEdit->setFont(font);
    }
}


void MainWindow::on_FontBackground_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择字体颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QTextEdit { background-color: %1;}").arg(color.name()));
    }
}


void MainWindow::on_FontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择字体颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QTextEdit { color: %1;}").arg(color.name()));
    }

}


void MainWindow::on_ToolBar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->ToolBar->setChecked(!visible);
}


void MainWindow::on_StatusBar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->StatusBar->setChecked(!visible);
}


void MainWindow::on_All_triggered()
{
    ui->textEdit->selectAll();
}


void MainWindow::on_actionExit_triggered()
{
    if(userEditComfirm()){
        exit(0);
    }
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    int pos = ui->textEdit->textCursor().position();
    QString text = ui->textEdit->toPlainText();
    int col = 0;
    int ln = 0;
    int flg = -1;

    for(int i = 0; i<pos;i++){
        if(text[i]=='\n'){
            ln++;
            flg = i;
        }
    }

    flg ++;
    col = pos - flg;
    StatusCursorLabel.setText("Ln :" + QString::number(ln+1) + "   Col: "+QString::number(col+1));

}

