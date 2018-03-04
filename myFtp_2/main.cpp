#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
