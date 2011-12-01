#ifndef _SERIALPACKET_H
#define _SERIALPACKET_H

#include <QString>

class SerialPacket
{
public:
    SerialPacket();
    ~SerialPacket();
    
    void setPacketDescriptor(QString &packetDescriptor);
    QString getPacketDescriptor();

    int checksum();
    int packetSize();

private:
    QString m_packetDescriptor;
    int m_checksum;

    void computeChecksum();    
};

#endif // _SERIALPACKET_H
