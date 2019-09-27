#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include <QTcpSocket>
//class QTextEdit;
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QListWidget>
#include <QHBoxLayout>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QAbstractSocket>
//class QLineEdit;

class Client : public QWidget
{
    Q_OBJECT
public:
    //Client(QString host, int port, QString name, QWidget* pwgt = 0);
    Client(QWidget* pwgt = 0);
    bool connectToServer(QString host, int port, QString name, QString &error);
signals:
    void connectionFailed();
    void connectionSucceeded();
private:
    QTcpSocket* socket;
    QTextEdit* dialog;//здесь показываются вводимые пользователями сообщения
    QLineEdit* msgField;//поле для ввода сообщений
    quint16 nextBlockSize;
    //QListWidget *usersNamesList;
    QListView *usersNamesListView;
    QStringListModel *model;
    QString name;//имя клиента
    QStringList usersNamesList;//имена всех участников чата
    QString errorMsg;
    bool isConnectedSuccessfully;
public slots:
    void sendMsgToServer();//отправляет сообщение серверу
    //void sendNameToServer();//отправляет серверу имя
    void readFromServer();
    //void setErrorMsg();
    void setErrorMsg(QAbstractSocket::SocketError er);
    void sendNameToServer();//для отправки имени после установления соединения

};

#endif // CLIENT_H
