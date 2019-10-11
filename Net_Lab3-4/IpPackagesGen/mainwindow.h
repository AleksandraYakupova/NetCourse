#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

struct IPHeader
{
    unsigned short ver_number : 4;
    unsigned short header_lenght : 4;
    unsigned short service_type : 8;
    unsigned short total_lenght : 16;
    unsigned short id : 16;
    unsigned short flags : 3;
    unsigned short fragment_offset : 13;
    unsigned short life_time : 8;
    unsigned short protocol : 8;
    unsigned short checksum : 16;
    unsigned int source_ip_addr : 32;
    unsigned int dest_ip_addr : 32;
    unsigned int options : 32;

};

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
    bool getIPAddresses(unsigned int&, unsigned int&);
    bool getPorts(unsigned short&, unsigned short&);
    unsigned int parseIPAddress(QString);

private:
    QLineEdit *lEditSndAddr;
    QLineEdit *lEditRcvAddress;
    QLineEdit *lEditSndPort;
    QLineEdit *lEditRcvPort;
    QLabel *lblErrorMsg;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
