#include "sensordata.h"

#include <QPointF>
#include <QRectF>

SensorData::SensorData()
{
    instance = new SensorData();
}

SensorData::~SensorData()
{
    delete instance;
}

SensorData& SensorData::getInstance()
{
    static SensorData instance;

    return instance;
}

void SensorData::append(const QPointF &pos)
{
    mutex.lock();
    pendingValues += pos;

    const bool isLocked = m_lock.tryLockForWrite();
    if (isLocked) {
        const int num = pendingValues.size();
        const QPointF *addr = pendingValues.data();

        // Store the sample data
        for (int i = 0; i < num; i++)
            m_values.append(addr[i]);

        // Clear the pendingValues
        pendingValues.clear();

        m_lock.unlock();
    }

    mutex.unlock();
}

int SensorData::size() const
{
    return m_values.size();
}

QPointF SensorData::value(int index) const
{
    return m_values[index];
    // return QPointF(x, y);
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
