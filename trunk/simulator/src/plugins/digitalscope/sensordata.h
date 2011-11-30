#ifndef SENSORDATA_H
#define SENSORDATA_H

class QPointF;
#include <QRectF>
#include <QVector>
#include <QReadWriteLock>
#include <QMutex>

class SensorData
{
public:
    enum SensorRawDataChannel {
        Accel_X,
        Accel_Y,
        Accel_Z,
        Gyro_X,
        Gyro_Y,
        Gyro_Z
    };

    static SensorData &instance();

    void append(const QPointF &pos);
    int size() const;
    QPointF value(int index) const;

    QRectF boundingRect() const;

    void lock();
    void unlock();

private:
    SensorData();
//    SensorData(const SensorData &);
//    SensorData &operator=(const SensorData&);

    virtual ~SensorData();

    QVector<QPointF> m_values;
    QRectF m_boundingRect;
    QVector<QPointF> m_sensorValues;
    
    QMutex m_mutex;
    QReadWriteLock m_lock;
};

#endif // SENSORDATA_H
