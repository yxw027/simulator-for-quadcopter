#include "sensordata.h"

#include <QReadWriteLock>
#include <QMutex>
#include <QVector>


class SensorData::PrivateData
{
public:
    PrivateData()
    {
    }

    inline void append(const QPointF &point)
    {
        values.append(point);

        // adjust the bounding rectangle
        if (boundingRect.width() < 0 || boundingRect.height() < 0)
            boundingRect.setRect(point.x(), point.y(), 0.0, 0.0);
        else {
            boundingRect.setRight(point.x());
            if (point.y() > boundingRect.bottom())
                boundingRect.setBottom(point.y());
            if (point.y() < boundingRect.top())
                boundingRect.setTop(point.y());
        }
    }

    QReadWriteLock lock;
    QMutex mutex;
    QVector<QPointF> values;
    QVector<QPointF> pendingValues;
    QRectF boundingRect;
};

SensorData::SensorData()
{
    p_data = new PrivateData();
}

SensorData::~SensorData()
{
    delete p_data;
}

SensorData& SensorData::instance()
{
    static SensorData instance;

    return instance;
}

void SensorData::append(const QPointF &point)
{
    p_data->mutex.lock();
    p_data->pendingValues += point;

    const bool isLocked = p_data->lock.tryLockForWrite();
    if (isLocked) {
        const int numValues = p_data->pendingValues.size();
        const QPointF *pendingValues = p_data->pendingValues.data();

        for (int i = 0; i < numValues; i++)
            p_data->append(pendingValues[i]);

        p_data->pendingValues.clear();

        p_data->lock.unlock();
    }
    p_data->mutex.unlock();
}

int SensorData::size() const
{
    return p_data->values.size();
}

QPointF SensorData::value(int index) const
{
    return p_data->values[index];
}

QRectF SensorData::boundingRect() const
{
    return p_data->boundingRect;
}

void SensorData::lock()
{
    p_data->lock.lockForRead();
}

void SensorData::unlock()
{
    p_data->lock.unlock();
}
