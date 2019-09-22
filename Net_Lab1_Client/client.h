#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include <QTcpSocket>
//class QTextEdit;
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
//class QLineEdit;

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(QString host, int port, QWidget* pwgt = 0);
private:
    QTcpSocket* socket;
    QTextEdit* dialog;//здесь показываются вводимые пользователями сообщения
    QLineEdit* msgField;//поле для ввода сообщений
public slots:
    void sendToServer();//отправляет сообщение серверу

};

#endif // CLIENT_H
