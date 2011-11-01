#include "curvedata.h"
#include "sensordata.h"

const SensorData& CurveData::values() const
{
//    return SensorData::getInstance();
}

SensorData& CurveData::values()
{
//    return SensorData::getInstance();
}

QPointF CurveData::sample(size_t i) const
{
//    return SensorData::getInstance().value(i);
}

size_t CurveData::size() const
{
//    return SensorData::getInstance().size();
}

QRectF CurveData::boundingRect() const
{
//    return SensorData::getInstance().boundingRect();
}
