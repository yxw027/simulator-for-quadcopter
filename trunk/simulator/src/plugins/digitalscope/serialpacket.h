#ifndef _SERIALPACKET_H
#define _SERIALPACKET_H

class SerialPacket
{
public:
    SerialPacket();
    ~SerialPacket();
    
    void setPacketDescriptor(QString &packetDescriptor);
    QString getPacketDescriptor();


    int checksum() const;
    int packetSize();

private:
    QString m_packetDescriptor;
    uint16 m_checksum;
    
    void computeChecksum();    
};

#endif // _SERIALPACKET_H