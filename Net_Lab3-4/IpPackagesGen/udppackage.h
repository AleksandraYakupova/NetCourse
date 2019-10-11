#ifndef UDPPACKAGE_H
#define UDPPACKAGE_H
#include <QByteArray>
#include <QObject>

struct UDPHeader
{
    unsigned short source_port : 16;
    unsigned short dest_port : 16;
    unsigned short length : 16;
    unsigned short checksum : 16;
};

class UDPPackage : public QObject
{
    Q_OBJECT

public:
    UDPPackage();
    void fill(unsigned short, unsigned short, QByteArray,
                     unsigned int, unsigned int);
    QByteArray createPseudoHeader(unsigned int, unsigned int, unsigned short);
    unsigned short calculateCheckSum();
private:
    UDPHeader header;
    QByteArray data;
    QByteArray pseudoHeader;
};

#endif // UDPPACKAGE_H
