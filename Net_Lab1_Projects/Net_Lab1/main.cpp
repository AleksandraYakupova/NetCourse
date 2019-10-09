#include <server.h>
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString str("2e+308");
    double d = str.toDouble();
    Server server(2424);
    server.show();
    return a.exec();
}
