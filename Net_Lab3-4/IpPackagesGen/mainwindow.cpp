#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QRegExp>
#include <QValidator>
#include <QLineEdit>
#include "udppackage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Layout
    //Текстовые поля для ввода ip адресов
    /*lEditSourceIPAddr = new QLineEdit(this);
    lEditDestIPAddr = new QLineEdit(this);
    QPushButton *readyBtn = new QPushButton("Сгенерировать пакет");
    connect(readyBtn, &QPushButton::clicked, this, &MainWindow::generatePackage);
    errorLbl = new QLabel(this);
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(lEditSourceIPAddr);
    layout->addWidget(errorLbl);
    layout->addWidget(readyBtn);
    widget->setLayout(layout);*/

    ui->setupUi(this);
    lEditSndAddr = ui->lEditSndAddr;
    lEditRcvAddress = ui->lEditRcvAddr;
    lblErrorMsg = ui->lblErrorMsg;
    QPushButton *btnGeneratePckg = ui->btnGeneratePckg;

    QRegExp rx("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
               "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
               "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
               "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QValidator *validator = new QRegExpValidator(rx, this);
    lEditSndAddr->setValidator(validator);
    lEditRcvAddress->setValidator(validator);
    lEditSndAddr->setText("8.8.8.8");
    lEditRcvAddress->setText("1.1.1.1");
    ui->lEditRcvPort->setText("10000");
    ui->lEditSndPort->setText("10000");
    //ui->lEditRcvPort->setValidator(portV);
    //ui->lEditSndPort->setValidator(portV);
    connect(btnGeneratePckg, &QPushButton::clicked, this, &MainWindow::generatePackage);

    IPHeader ipHeader;
    ipHeader.ver_number = 4;
    ipHeader.header_lenght = 5;//(количество слов в заголовке)
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
    //ipHeader.total_length =

}

void MainWindow::generatePackage()
{
    unsigned int sourceAddr, destAddr;
    if (!getIPAddresses(sourceAddr, destAddr))//получаем ip адреса отправителя и получателя
        return;                                 //в виде, необходимом для записи в пакет

    //Получаем введенные данные
    QByteArray data = ui->tEditData->toPlainText().toUtf8();
    //Получаем порты
    unsigned short sourcePort, destPort;
    if (!getPorts(sourcePort, destPort))
        return;

    //Генерируем UDP пакет
    udpPckg.fill(sourcePort, destPort, data, sourceAddr, destAddr);

    printPackageInfo();//Выводим
}

bool MainWindow::getIPAddresses(unsigned int& sourceAddr, unsigned int& destAddr)
{
    if (!lEditSndAddr->hasAcceptableInput()) {
        lblErrorMsg->setText("Не корректно задан ip адрес отправителя!");
        return false;
    }
    if (!lEditRcvAddress->hasAcceptableInput()) {
        lblErrorMsg->setText("Не корректно задан ip адрес получателя!");
        return false;
    }
    QString sourceIPStr = lEditSndAddr->text();
    QString destIPStr = lEditRcvAddress->text();
    sourceAddr = parseIPAddress(sourceIPStr);
    destAddr = parseIPAddress(destIPStr);
    return true;
}

bool MainWindow::getPorts(unsigned short& sourcePort, unsigned short& destPort)
{
    QIntValidator *portV = new QIntValidator(1024, 40000, this);
    QString sndPortStr = ui->lEditSndPort->text();
    QString rcvPortStr = ui->lEditRcvPort->text();
    int pos;
    if (portV->validate(sndPortStr, pos) != QIntValidator::Acceptable) {
        lblErrorMsg->setText("Не корректно задан порт отправителя!");
        return false;
    }
    if (portV->validate(rcvPortStr, pos) != QIntValidator::Acceptable) {
        lblErrorMsg->setText("Не корректно задан порт получателя!");
        return false;
    }
    sourcePort = sndPortStr.toUShort();
    destPort = rcvPortStr.toUShort();
    return true;
}

unsigned int MainWindow::parseIPAddress(QString ipAddrStr)
{
   unsigned int ipAddr = 0;
   QStringList addrParts = ipAddrStr.split('.');
   int offset = 24;
   for(auto partStr : addrParts)
   {
       unsigned int part = partStr.toUInt();
       part <<= offset;
       ipAddr += part;
       offset -= 8;
   }
   return ipAddr;
}

void MainWindow::printPackageInfo()
{
    QTextEdit *tEditPckgInfo = ui->tEditPckgInfo;
    QString text = QString("<p><b>User Datagram Protocol</b></p>"
                           "<p>Source Port: <span style=\"color:red; font-family:Georgia, serif\">%1</span></p>"
                           "<p>Destination Port: %2</p>"
                           "<p>Length: %3 bytes</p>"
                           "<p>Checksum: 0x%4 </p>")
            .arg(udpPckg.header.source_port)
            .arg(udpPckg.header.dest_port)
            .arg(udpPckg.header.length)
            .arg(udpPckg.header.checksum, 0, 16);
    tEditPckgInfo->setHtml(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
