#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_About_triggered();

    void on_FInd_triggered();

    void on_replace_triggered();

    void on_NewFIle_triggered();

    void on_openFile_triggered();

    void on_saveFile_triggered();

    void on_saveAs_triggered();

    void on_textEdit_textChanged();

    void on_Undo_triggered();

    void on_Redo_triggered();

    void on_Cut_triggered();

    void on_Copy_triggered();

    void on_Paste_triggered();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_redoAvailable(bool b);

    void on_textEdit_undoAvailable(bool b);

    void on_AutoEnter_triggered();

    void on_FontFormat_triggered();

    void on_FontBackground_triggered();

    void on_FontColor_triggered();

    void on_ToolBar_triggered();

    void on_StatusBar_triggered();

    void on_All_triggered();

    void on_actionExit_triggered();

    void on_textEdit_cursorPositionChanged();

private:
    Ui::MainWindow *ui;

    QLabel StatusCursorLabel;
    QLabel StatusLabel;

    QString FilePath;

    bool textChange;

    bool userEditComfirm();
};
#endif // MAINWINDOW_H
