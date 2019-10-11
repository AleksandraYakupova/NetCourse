#include "udppackage.h"
#include <QIODevice>
#include <QDataStream>

UDPPackage::UDPPackage()
{

}

void UDPPackage::fill(unsigned short sourcePort,
                             unsigned short destPort,
                             QByteArray _data,
                             unsigned int sourceAddr,
                             unsigned int destAddr)
{
    header.source_port = sourcePort;
    header.dest_port = destPort;
    data = _data;
    header.length = sizeof (header) + data.length();
    //создаем псевдозаголовок для расчета контрольной суммы
    pseudoHeader = createPseudoHeader(sourceAddr, destAddr, header.length);
    header.checksum = calculateCheckSum();//расчитываем контрольную сумму

}

QByteArray UDPPackage::createPseudoHeader(unsigned int sourceAddr,
                                          unsigned int destAddr,
                                          unsigned short length)
{
    QByteArray pseudoHdr;
    QDataStream stream(&pseudoHdr, QIODevice::WriteOnly);
    unsigned char alignZeros {0};
    unsigned char protocol {17};
    stream << sourceAddr << destAddr << alignZeros << protocol << length;
    return pseudoHdr;
}

unsigned short UDPPackage::calculateCheckSum()
{
    unsigned short checkSum {0};//изначально равна 0
    QByteArray words = pseudoHeader;

    //объединяем в один массив псевдозаголовок и udp пакет
    QDataStream stream(&words, QIODevice::Append);
    //stream << pseudoHeader
      stream << header.source_port
           << header.dest_port
           << header.length
           << checkSum
           << data;
    if (data.size() %2 != 0)//если число байтов нечетно
        stream << quint8(0);//дополняем еще байтом, чтобы было четным

    //Проходимся по 16битным словам
    unsigned short word1, word2;
    word1 = words[0];
    word1 <<= 8;
    word1 += words[1];
    for (int i = 1; i < words.size(); i+=2)
    {
        word2 = words[i];
        word2 <<= 8;
        word2 += words[i+1];

        unsigned int wordSum = word2 + word1;//cкладываем два 16битных слова
        if (wordSum >= 0xffff) {
            ++wordSum;
        }
        word1 = wordSum;//у wordSum "подрезаются" верхние биты
        //0001 0011 0001 1000 1101 - 1318D
        //0000 0011 0001 1000 1101 - 318D
    }
    word1 = ~word1;//инвертируем
    checkSum = word1;
    return checkSum;
}

UDPPackage& UDPPackage::operator=( const UDPPackage& other)
{
    header = other.header;
    data = other.data;
    return *this;
}

UDPPackage::UDPPackage(const UDPPackage &other)
{
    header = other.header;
    data = other.data;
}
