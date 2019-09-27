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
    sendCurrClientsNamesToNewClient(clientSocket);//отправляем список имен текущих участников
    connect(clientSocket, &QTcpSocket::disconnected,
            [clientSocket, this] () {
        //отправляем всем имя отключившегося клиента
        this->sendClientName(clientsNames[clientSocket]);
        int index = this->clients.indexOf(clientSocket);
        this->clients.removeAt(index);//удаляем клиента из списка
        clientsNames.take(clientSocket);//а также из контейнера имен
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

    QDataStream in(clientSocket);
    QByteArray msg;
    quint8 i;
    nextBlockSize = 0;
    bool msgWasSent = false;
    forever {
        if (!nextBlockSize) {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (clientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }
        in >> i >> msg;
        if (i) msgWasSent = true;
        nextBlockSize = 0;
    }


    //QByteArray msg(clientSocket->readAll());//читаем все сообщение
    //для проверки выводим его в receivedMsgField
    if (!msgWasSent) { //если новый клиент отправил свое имя
        QString newClientName(msg);
        if (bannedClients.indexOf(newClientName) != -1) {//если есть такой в списке забаненных
            sendBanMsgAndDisconnect(clientSocket);
        }
        clientsNames[clientSocket] = msg;
        receivedMsgField->append("Name: ");
        sendClientName(msg);//отправляем всем участникам чата имя нового клиента
    }
    else {
        QString senderName = clientsNames[clientSocket];
        sendMsgToClients(msg, senderName); //отправляем всем подключенным клиентам
    }
    receivedMsgField->append(msg);
}

void Server::sendMsgToClients(QByteArray msg, QString senderName)
{
    QByteArray block;
    //Запаковываем сюда также время отправки
    QTime sendingTime(QTime::currentTime());
    QDataStream out(&block, QIODevice::ReadWrite);
    out << quint16(0) << quint8(1) << msg << sendingTime << senderName;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.size(); ++i)
    {
        QTcpSocket *clientSocket = clients.at(i);
        clientSocket->write(block);
        //clientSocket->write(sendingTime);
    }

    banClient(clients.at(0));
}


//отправляет всем имя соединившегося или отсоединившегося участника
void Server::sendClientName(QString clientName)
{
    QByteArray nameToSend = clientName.toUtf8();//Получаем введенное сообщение
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out << quint16(0) << quint8(0) << nameToSend;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.size(); ++i)
    {
        QTcpSocket *clientSocket = clients.at(i);
        clientSocket->write(block);
        //clientSocket->write(sendingTime);
    }
}

//Отправляет новому клиенту имена текущих участников чата
void Server::sendCurrClientsNamesToNewClient(QTcpSocket *newClientSocket)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out << quint16(0) << quint8(2);//2 - отправка имен текущих участников чата
    QMapIterator<QTcpSocket*, QString> i(clientsNames);
    int numberOfClients = clientsNames.size();
    if (!numberOfClients) return;//если участников нет, ничего не отправляем
    out << quint8(clientsNames.size());//значала запаковываем размер (количество клиентов)
    while(i.hasNext()) {
        i.next();
        out << i.value();
    }
    newClientSocket->write(block);
    newClientSocket->flush();
}

void Server::banClient(QTcpSocket *client)
{
    QString clientName = clientsNames[client];
    bannedClients.push_back(clientName);//добавляем в список забанненных
    sendBanMsgAndDisconnect(client);//сообщаем ему об этом
}

void Server::sendBanMsgAndDisconnect(QTcpSocket *client)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out << quint16(0) << quint8(3);//3 - сообщение о бане
    QString banMsg("Вы забанены и больше не можете отправлять сообщения");
    out << banMsg;
    client->write(block);
    client->flush();

    //Отсоединяем от сервера
}
