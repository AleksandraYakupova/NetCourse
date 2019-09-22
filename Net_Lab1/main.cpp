#include <server.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server(2424);
    server.show();
    return a.exec();
}
