#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QIntValidator>
#include <client.h>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(Client *client, QWidget *parent = 0);
    QString getName();
    QString getIP();
    int getPort();
public slots:
    void acceptButtonClicked();
    //void acceptDialog();
private:
    QLineEdit *nameFld;//поле для имени участника чата
    QString name;
    QLineEdit *ipFld;
    QString ip;
    QLineEdit *portFld;
    int port;
    QLabel *errorLbl;
    Client *client;
};

#endif // LOGINDIALOG_H
