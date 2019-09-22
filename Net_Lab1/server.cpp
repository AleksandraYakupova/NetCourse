#include "server.h"
#include <QTcpSocket>

Server::Server(int port, QWidget *pwgt)
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        //выводим ошибку
        tcpServer->close();
    }

    connect(tcpServer, &QTcpServer::newConnection,
            this, &Server::slotNewConnection);

}

void Server::slotNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();//получаем сокет клиента
    connect(clientSocket, &QTcpSocket::disconnected,
            [clientSocket] () {
        clientSocket->deleteLater();
    });

}
