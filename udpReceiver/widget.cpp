#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label->adjustSize();//调整字符显式不全。
//    ui->label->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    receiver = new QUdpSocket(this);
    receiver->bind(45454, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        ui->label->setText(datagram);
//        ui->label->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    }
}
