#include "ippackage.h"
#include <random>
#include <QDataStream>
#include <time.h>

IPPackage::IPPackage()
{

}

void IPPackage::fill(unsigned int sourceAddr,
                     unsigned int destAddr,
                     UDPPackage udpPckg)
{
    header.ver_number = 4;//IPv4
    header.header_lenght = 5;//(количество слов в заголовке)
                               //5, так как опции отсутствуют
    header.service_type = 0;
    //Генерируем рандомный id
    //std::random_device dev;
    //std::mt19937 rng(dev);
    //std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 60000);
    srand ( time(NULL) );
    //header.id = dist6(rng);
    header.id = rand() % 60001;
    header.flags = 2; //010
    header.fragment_offset = 0;//пакет не фрагментируется, поэтому смещения нет
    header.life_time = 128;//пакет может пройти 128 узлов
    header.protocol = 17;//код для UDP пакетов
    header.source_ip_addr = sourceAddr;
    header.dest_ip_addr = destAddr;
    header.checksum = 0;//до подсчета равна 0
    header.checksum = calculateCheckSum();//вычисляем контр сумму

    data = udpPckg;
    header.total_length = sizeof (header) - 4 + sizeof(udpPckg.header) + udpPckg.data.length();
}

unsigned short IPPackage::calculateCheckSum()
{
    unsigned short checkSum {0};//изначально равна 0

    QByteArray words;
    //контрольная сумма расчитывается только по заголовку
    QDataStream stream(&words, QIODevice::Append);
    //Придется засунуть так :(
    stream << header.ver_number
             << header.header_lenght
             << header.service_type
             << header.total_length
             << header.id
             << header.flags
             << header.fragment_offset
             << header.life_time
             << header.protocol
             << header.checksum
             << header.source_ip_addr
             << header.dest_ip_addr;

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
    }
    word1 = ~word1;//инвертируем
    checkSum = word1;
    return checkSum;
}
