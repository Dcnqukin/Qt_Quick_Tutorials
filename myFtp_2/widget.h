#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QFtp>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFile *file;
    QFtp *ftp;

private slots:
    void on_downloadButton_clicked();
    void on_cdToParentButton_clicked();
    void on_connectButton_clicked();
    void ftpCommandFinished(int, bool); 
    void ftpCommandStarted(int);
    void updateDataTransferProgress(qint64, qint64);
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem*, int);
};

#endif // WIDGET_H
