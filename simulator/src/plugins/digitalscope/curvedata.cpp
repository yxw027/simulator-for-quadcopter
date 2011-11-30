#include "curvedata.h"
#include "sensordata.h"

const SensorData& CurveData::values() const
{
    return SensorData::instance();
}

SensorData& CurveData::values()
{
    return SensorData::instance();
}

QPointF CurveData::sample(size_t i) const
{
    return SensorData::instance().value(i);
}

size_t CurveData::size() const
{
    return SensorData::instance().size();
}

QRectF CurveData::boundingRect() const
{
    return SensorData::instance().boundingRect();
}
