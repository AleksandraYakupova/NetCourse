#ifndef SERVER_H
#define SERVER_H
#include <windows.h>
#include <QTcpServer>
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include<QTime>
class Server : public QWidget
{
    Q_OBJECT
private:
    QTcpServer* tcpServer;
    quint16 nextBlockSize;//размер след блока данных от клиента
    QTextEdit* receivedMsgField;//для проверки полученного сообщения
    QVector <QTcpSocket *> clients;//все подключенные клиенты
    QVector <QString> bannedClients;//забаненные клиенты
    QMap<QTcpSocket*, QString> clientsNames;
    void banClient(QTcpSocket *client);
    void sendBanMsgAndDisconnect(QTcpSocket *client);

public:
    Server(int port, QWidget *pwgt = 0);
public slots:
    void slotNewConnection();
    void readClient();//здесь читаем данные от клиента
    void sendMsgToClients(QByteArray msg, QString senderName);//отправляем сообщение всем клиентам
    void sendClientName(QString clientName);//отправляем всем участникам имя нового клиента
    void sendCurrClientsNamesToNewClient(QTcpSocket *newClientSocket);
};

#endif // SERVER_H
