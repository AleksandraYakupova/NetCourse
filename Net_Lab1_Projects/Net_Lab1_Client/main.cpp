#include <QApplication>
#include <client.h>
#include <logindialog.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client *client = new Client();
    LoginDialog *dialog = new LoginDialog(client);
    dialog->show();
    QString ip;
    QString port;
    QString userName;
    /*QObject::connect(dialog, &QDialog::accepted,
            [dialog] () {
        Client client("localhost", 2424, dialog->getName());
        client.show();

    });*/

    if (dialog->exec() == QDialog::Accepted)
    {
        //Client client("localhost", 2424, dialog->getName());
        //client.connectToServer("localhost", 2424, dialog->getName());
        client->show();
        int a2 = 0;
    }
    return a.exec();
}

void dialogIsFinished()
{

}
