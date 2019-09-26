#include "server.h"
#include <QTcpSocket>

Server::Server(int port, QWidget *pwgt)
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Server cannot listen";//выводим ошибку
        tcpServer->close();
    }

    connect(tcpServer, &QTcpServer::newConnection,
            this, &Server::slotNewConnection);

    //для проверки полученных сообщений от клиента
    receivedMsgField = new QTextEdit;
    receivedMsgField->setReadOnly(true);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(receivedMsgField);
    setLayout(vBoxLayout);

}

void Server::slotNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();//получаем сокет клиента
    clients.push_back(clientSocket);//добавляем в список подключений
    connect(clientSocket, &QTcpSocket::disconnected,
            [clientSocket, this] () {
        int index = this->clients.indexOf(clientSocket);
        this->clients.removeAt(index);//удаляем клиента из списка
        clientSocket->deleteLater(); //удаляем сокет при отсоединении
    });
    connect(clientSocket, &QTcpSocket::readyRead, //если новые данные поступили
    //connect(clientSocket, &QTcpSocket::bytesWritten, //так как размер сообщений будет небольшим
            this, &Server::readClient); //то будем читать все данные целиком
            //[clientSocket]() {
        //int a = 0;
    //});
}

void Server::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    QByteArray msg(clientSocket->readAll());//читаем все сообщение
    //для проверки выводим его в receivedMsgField
    receivedMsgField->setText(msg);
    sendToClients(msg); //отправляем всем подключенным клиентам


    //QDataStream in(clientSocket);
    /*forever {

        if(!nextBlockSize) {//если размер след блока данных неизвестен
            in >> nextBlockSize;//получаем размер след блока
        }
        if(clientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }
        QByteArray msg;
        in >> msg;//получаем передаваемое сообщение
        receivedMsgField->setText(msg);
    }*/

    //Используем блокирующие сокеты

}

void Server::sendToClients(QByteArray msg)
{
    for (int i = 0; i < clients.size(); ++i)
    {
        QTcpSocket *clientSocket = clients.at(i);
        clientSocket->write(msg);
    }
}
