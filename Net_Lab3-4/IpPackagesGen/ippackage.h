#ifndef IPPACKAGE_H
#define IPPACKAGE_H
#include <QObject>
#include "udppackage.h"

struct IPHeader
{
    unsigned short ver_number : 4;
    unsigned short header_lenght : 4;
    unsigned short service_type : 8;
    unsigned short total_length : 16;
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

class IPPackage : public QObject
{
    Q_OBJECT

public:
    IPPackage();
    IPHeader header;
    UDPPackage data;//внутри всегда будет udp пакет
    void fill(unsigned int, unsigned int, UDPPackage);
    unsigned short calculateCheckSum();
};

#endif // IPPACKAGE_H
