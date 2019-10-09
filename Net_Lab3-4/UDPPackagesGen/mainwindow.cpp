#include <winsock2.h>
#include "stdio.h"
#include <QDebug>
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

#pragma comment(lib,"ws2_32.lib") //For winsock
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1) //this removes the need of mstcpip.h

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    sniffInfo = new QTextEdit;
    sniffInfo->setReadOnly(true);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(sniffInfo);
    widget->setLayout(vBoxLayout);
    sniffInfo->setText("HI");


    SOCKET sniffer;
    struct in_addr addr;//IPv4 адрес

    WSADATA wsa;
    //initiates use of the Winsock DLL by a process
    if (WSAStartup(MAKEWORD(2, 0), &wsa) !=  0) {
        sniffInfo->append("WSAStartup failed");
        qDebug() << "WSAStartup failed";
    }

    sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);//создаем RAW сокет
    if (sniffer == INVALID_SOCKET) {
        sniffInfo->append("WSAStartup failed");
        qDebug() << "Failed to create socket";
    }

    char hostName[100];
    if (gethostname(hostName, sizeof(hostName)) == SOCKET_ERROR) {
        sniffInfo->append("Failed to get host name");
        qDebug() << WSAGetLastError();
    }
    qDebug() << hostName;

    struct hostent *hostInfo;//структура хранит информацию о хосте (имя, адрес и т.д.)
    hostInfo = gethostbyname(hostName);
    if (hostInfo == NULL) {
        sniffInfo->append("Failed to get host info");
        qDebug() << WSAGetLastError();
    }

    for (int i = 0; hostInfo->h_addr_list[i] != NULL; ++i) {
        memcpy(&addr, hostInfo->h_addr_list[i], sizeof(struct in_addr));
        QString addrStr(inet_ntoa(addr));
        sniffInfo->append("Address: " + addrStr);
        qDebug() << "Address: " <<  inet_ntoa(addr);
    }

    int j = 1;

    //j - буфер
    //if (WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 0, 0, ))
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    //delete ui;
}
