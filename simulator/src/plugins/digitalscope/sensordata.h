#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QRectF>


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

    class PrivateData;
    PrivateData *p_data;
};

#endif // SENSORDATA_H
