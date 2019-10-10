#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QRegExp>
#include <QValidator>
#include <QLineEdit>

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //Layout
    QLineEdit *lEditSourceIPAddr = new QLineEdit();
    QLineEdit *lEditDestIPAddr = new QLineEdit();
    QRegExp rx("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
               "\\1\\.\\1.\\1$");
    QValidator *validator = new QRegExpValidator(rx, this);
    lEditSourceIPAddr->setValidator(validator);
    lEditDestIPAddr->setValidator(validator);
    QPushButton *readyBtn = new QPushButton();
    connect(readyBtn, &QPushButton::clicked, this, &MainWindow::generatePackage);
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(lEditSourceIPAddr);
    layout->addWidget(readyBtn);
    widget->setLayout(layout);

    //ui->setupUi(this);
    IPHeader ipHeader;
    ipHeader.ver_number = 4;
    ipHeader.header_lenght = 5;
    ipHeader.service_type = 0;
    ipHeader.id = 0;
    ipHeader.flags = 2; //010
    ipHeader.fragment_offset = 0;//пакет не фрагментируется, поэтому смещения нет
    ipHeader.life_time = 128;//пакет может пройти 20 узлов
    ipHeader.protocol = 17;//код для UDP пакетов
    QString ip_addr = "168.212.24.120";
    //ipHeader.source_ip_addr
    //ipHeader.dest_ip_addr
    //ipHeader.checksum = ...

}

void MainWindow::generatePackage()
{


}

unsigned int MainWindow::parseIPAddresses()
{
    QString sourceIPStr = lEditSourceIPAddr->text();

}

MainWindow::~MainWindow()
{
    //delete ui;
}
