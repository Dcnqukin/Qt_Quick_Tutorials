#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QAction *openAction = new QAction(tr("&Open"), this);
//    QIcon icon(":/myImages/images/fileopen.png");//use Resources File
//    openAction->setIcon(icon);
//    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
//    ui->menu_F->addAction(openAction);
    ui->setupUi(this);

    isUntitled = true;
    curFile = tr("Untitled.txt");
    setWindowTitle(curFile);

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn = new QPushButton(tr("查找下一个"),findDlg);
    QVBoxLayout  *layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText())); //面试题 信号与槽之间的关联。使用connect().

    //ui->statusBar->showMessage(tr("欢迎使用Qt"), 2000);
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150, 20);
    statusLabel->setFrameShape(QFrame::WinPanel);
    statusLabel->setFrameShadow(QFrame::Sunken);
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText(tr("欢迎使用Qt"));

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(
                tr("<a href=\"https://www.github.com/Dcnqukin\">github.com/Dcnqukin</a>"));
    permanent->setTextFormat(Qt::RichText);
    permanent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if (maybeSave()){
        isUntitled = true;
        curFile = tr("Untitled.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave()
{
    if(ui->textEdit->document()->isModified()){

        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        //box.setIcon(QMessageBox::warning);//QMessageBox::warning是函数，注意大小写。
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + tr(" 尚未保存， 是否保存？"));
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("取消"),
                                            QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        else if(box.clickedButton() == cancelBut)
            return false;
    }
    return true;
}

bool MainWindow::save()
{
    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), curFile);
    if(fileName.isEmpty()) return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)){

        QMessageBox::warning(this, tr("多文档编辑器"), tr("无法写入文件 %1: /n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUntitled = false;

    curFile = QFileInfo(fileName).canonicalFilePath();// find the standard path of file
    setWindowTitle(curFile);
    return false;
}

void MainWindow::on_action_New_triggered()
{
    newFile();
}

void MainWindow::on_action_Save_triggered()
{
    save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    saveAs();
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("多文档编辑器"),
                                   tr("无法读取文件 %1: \n%2.")
                                   .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::on_action_Open_triggered()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this);

        if(!fileName.isEmpty()){
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_Close_triggered()
{
    if(maybeSave()){
        ui->textEdit->setVisible(false);
    }
}


void MainWindow::on_action_Exit_triggered()
{
    on_action_Close_triggered();
    qApp->quit();
}

void MainWindow::on_action_Undo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_Cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_Copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if(!ui->textEdit->find(str, QTextDocument::FindBackward))
    {
        QMessageBox::warning(this, tr("查找"),
                             tr("找不到%1").arg(str)); //%1挺有意思的
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::on_action_Find_triggered()
{
    findDlg->show();
}
