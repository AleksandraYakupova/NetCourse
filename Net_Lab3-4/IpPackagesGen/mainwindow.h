#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include "udppackage.h"
#include "ippackage.h"

struct TCPHeader
{

    unsigned short source_port : 16;
    unsigned short dest_port : 16;
    unsigned int sequence_number : 32;//используется для сегментации
    unsigned short header_length : 4;
    unsigned short reserved : 6;
    unsigned short flags : 6;
    unsigned short windown_size : 16;
    unsigned short check_sum : 16;
    unsigned short urgent_pointer : 16;
    unsigned int options : 32;

};

/*
struct IPPackage
{
    IPHeader header;
    UDPPackage data;
};
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void generatePackage();

private:
    bool getIPAddresses(unsigned int&, unsigned int&);
    bool getPorts(unsigned short&, unsigned short&);
    unsigned int parseIPAddress(QString);
    void printPackageInfo();
    QLineEdit *lEditSndAddr;
    QLineEdit *lEditRcvAddress;
    QLineEdit *lEditSndPort;
    QLineEdit *lEditRcvPort;
    QLabel *lblErrorMsg;
    Ui::MainWindow *ui;
    UDPPackage udpPckg;
    IPPackage ipPckg;
};

#endif // MAINWINDOW_H
