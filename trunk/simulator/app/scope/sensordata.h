#ifndef SENSORDATA_H
#define SENSORDATA_H

class QPointF;
class QRectF;
#include <QVector>
#include <QReadWriteLock>
#include <QMutex>

class SensorData {

public:
    enum SensorRawDataChannel {
        Accel_X,
        Accel_Y,
        Accel_Z,

        Gyro_X,
        Gyro_Y,
        Gyro_Z
    };

public:
    static SensorData& getInstance();

    void append(const QPointF &pos);
    int size() const;
    QPointF value(int index) const;

    QRectF boundingRect() const;

    void lock();
    void unlock();

private:
    SensorData();
    SensorData(const SensorData&);
    SensorData &operator=(const SensorData&);

    virtual ~SensorData();

    QReadWriteLock m_lock;
    QVector<QPointF> m_values;    // fix me
    //QRectF boundingRect;

    QMutex mutex; // protecting pendingValues
    QVector<QPointF> pendingValues;
};

#endif // SENSORDATA_H
