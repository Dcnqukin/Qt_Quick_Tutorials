#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startRequest(QUrl url);

private:
    Ui::MainWindow *ui;

    QNetworkReply *reply;
    QUrl url;
    QFile *file;
    QNetworkAccessManager *manager;

private slots:
    void on_pushButton_clicked(); //下载按钮的单击事件槽函数
    void httpFinished(); //完成下载后的处理
    void httpReadyRead(); //接收到数据时的处理
    void updateDataReadProgress(qint64, qint64); //更新进度条
};

#endif // MAINWINDOW_H
