#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class QLineEdit;
class QDialog;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);

    bool loadFile(const QString &fileName);

private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Open_triggered();

    void on_action_Close_triggered();

    void on_action_Exit_triggered();

    void on_action_Undo_triggered();

    void on_action_Cut_triggered();

    void on_action_Copy_triggered();

    void on_action_paste_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;
    QString curFile;

    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;


private slots:
    void showFindText();
    void on_action_Find_triggered();
};

#endif // MAINWINDOW_H
