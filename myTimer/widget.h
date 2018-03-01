#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

    int id1, id2, id3;

private slots:
    void timerUpdate();

protected:
    void timerEvent(QTimerEvent *);
};

#endif // WIDGET_H
