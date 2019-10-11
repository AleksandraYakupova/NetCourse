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
    //Генерируем ip пакет
    ipPckg.fill(sourceAddr, destAddr, udpPckg);

    ui->lblErrorMsg->setText("");
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
    QString ipPckgInfo = QString("<p><b>Internet Protocol Version 4</b></p>"
                                 "<p>Version: %1</p>"
                                 "<p>Header Length: %2 bytes (%3)</p>"
                                 "<p>Service type: 0x%4 </p>"
                                 "<p>Total Length: %5 bytes </p>"
                                 "<p>Identification: 0x%6 </p>"
                                 "<p>Flags: %7 </p>"
                                 "<p>Fragment Offset: %8 </p>"
                                 "<p>Time to live: %9 </p>"
                                 "<p>Protocol: UDP (%10) </p>"
                                 "<p>Check Sum: 0x%11 </p>"
                                 "<p>Source: %12 </p>"
                                 "<p>Destination: %13 </p>")
                  .arg(ipPckg.header.ver_number)
                  .arg(ipPckg.header.header_lenght * 4)
                  .arg(ipPckg.header.header_lenght)
                  .arg(ipPckg.header.service_type, 2, 16, QChar('0'))
                  .arg(ipPckg.header.total_length)
            .arg(ipPckg.header.id, 0, 16)
            .arg(ipPckg.header.flags, 3, 2, QChar('0'))
            .arg(ipPckg.header.fragment_offset)
            .arg(ipPckg.header.life_time)
            .arg(ipPckg.header.protocol)
            .arg(ipPckg.header.checksum, 0, 16)
            .arg(lEditSndAddr->text())
            .arg(lEditRcvAddress->text());


    QString udpPckgInfo = QString("<p><b>User Datagram Protocol</b></p>"
                           "<p>Source Port: %1</p>"
                           "<p>Destination Port: %2</p>"
                           "<p>Length: %3 bytes</p>"
                           "<p>Checksum: 0x%4 </p>"
                           "<p>Data: %5 </p>")
            .arg(udpPckg.header.source_port)
            .arg(udpPckg.header.dest_port)
            .arg(udpPckg.header.length)
            .arg(udpPckg.header.checksum, 0, 16)
            .arg(QString(udpPckg.data));

    ipPckgInfo += udpPckgInfo;
    tEditPckgInfo->setHtml(ipPckgInfo);
    QTextCursor cursor = tEditPckgInfo->textCursor();
    tEditPckgInfo->selectAll();
    tEditPckgInfo->setFontPointSize(12);
    tEditPckgInfo->setTextCursor( cursor );
}

MainWindow::~MainWindow()
{
    delete ui;
}
