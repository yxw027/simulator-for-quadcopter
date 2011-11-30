#include "serialpacket.h"

SerialPacket:SerialPacket()
{
    m_checksum = 0;
}

SerialPacket::~SerialPacket()
{
}

void SerialPacket::setPacketDescriptor(QString &packetDescriptor)
{
    m_packetDescriptor = packetDescriptor;
}

QString SerialPacket::getPacketDescriptor()
{
    return m_packetDescriptor;
}

void SerialPacket::computeChecksum()
{
}

int SerialPacket::packetSize()
{
    int size = 0;
    return size;
}

int SerialPacket::checksum() const
{
    computeChecksum();

    return m_checksum;
}
