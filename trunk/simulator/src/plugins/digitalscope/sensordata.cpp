#include "sensordata.h"

SensorData::SensorData()
{
    //instance = new SensorData();
}

SensorData::~SensorData()
{
    //delete instance;
}

SensorData& SensorData::instance()
{
    static SensorData instance;

    return instance;
}

void SensorData::append(const QPointF &pos)
{/*
    m_mutex.lock();
    
    const bool isLocked = m_lock.tryLockForWrite();
    if (isLocked) {
        //const int numValues = d_data->pendingValues.size();
        const QPointF *pendingValues = d_data->pendingValues.data();

        for (int i = 0; i < numValues; i++)
            d_data->append( pendingValues[i] );

        d_data->pendingValues.clear();

        d_data->lock.unlock();
    }
    m_mutex.unlock();*/
}

int SensorData::size() const
{
    return m_values.size();
}

QPointF SensorData::value(int index) const
{
    return m_values[index];
}

QRectF SensorData::boundingRect() const
{
    return QRectF(-1.0, -2.0, 2.0, 2.0); // fix me
}

void SensorData::lock()
{
    m_lock.lockForRead();
}

void SensorData::unlock()
{
    m_lock.unlock();
}
