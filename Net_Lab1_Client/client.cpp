#include "client.h"


Client::Client(QString host, int port, QWidget* pwgt)
    :QWidget (pwgt)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    msgField = new QLineEdit;
    sendToServer();
    /*dialog = new QTextEdit;
    dialog->setReadOnly(true);//поле только для чтения

    QPushButton* sendBtn = new QPushButton("&Send");
    connect(sendBtn, &QPushButton::clicked,
            this, &Client::sendToServer);//по нажатию на кнопку отправляем сообщение на сервер

    //Layout
    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(dialog);
    vBoxLayout->addWidget(msgField);
    vBoxLayout->addWidget(sendBtn);
    setLayout(vBoxLayout);*/
}

void Client::sendToServer()
{
    //QString msgToSend;
    /*
    QByteArray msgToSend;
    QDataStream out(&msgToSend, QIODevice::WriteOnly);
    //out << quint16(0) << msgField->text();//пока записываем данные без размера блока
    QString str("Hello");
    out << quint16(0) << str;
    out.device()->seek(0);//переходим снова в начало
    out << quint16(msgToSend.size() - sizeof(quint16));//и записываем размер блока
    */

    //socket->write(qPrintable(msgToSend));//write принимает только const char*
    QByteArray msgToSend("Hello");
    socket->write(msgToSend);
    socket->flush();
    msgField->setText("");//очищаем поле ввода
}
