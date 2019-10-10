#include "udppackage.h"

UDPPackage::UDPPackage()
{

}

void UDPPackage::fillPackage(unsigned short sourcePort,
                             unsigned short destPort,
                             QByteArray _data,
                             unsigned int sourceAddr,
                             unsigned int destAddr)
{
    header.source_port = sourcePort;
    header.dest_port = destPort;
    data = _data;
    header.length = sizeof (header) + data.length();
}

QByteArray UDPPackage::createPseudoHeader(unsigned int sourceAddr,
                                          unsigned int destAddr,
                                          unsigned short length)
{
}
