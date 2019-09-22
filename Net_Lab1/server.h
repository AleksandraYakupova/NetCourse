#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
class Server : public QWidget
{
    Q_OBJECT
private:
    QTcpServer* tcpServer;
    quint16 nextBlockSize;//размер след блока данных от клиента
    QTextEdit* receivedMsgField;//для проверки полученного сообщения
public:
    Server(int port, QWidget *pwgt = 0);
public slots:
    void slotNewConnection();
    void readClient();//здесь читаем данные от клиента
};

#endif // SERVER_H
