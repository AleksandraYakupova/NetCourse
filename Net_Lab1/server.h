#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QWidget>

class Server : public QWidget
{
    Q_OBJECT
private:
    QTcpServer *tcpServer;
public:
    Server(int port, QWidget *pwgt = 0);
public slots:
    void slotNewConnection();

};

#endif // SERVER_H
