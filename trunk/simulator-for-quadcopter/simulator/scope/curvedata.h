#ifndef CURVEDATA_H
#define CURVEDATA_H

#include <qwt_series_data.h>

class SensorData;

class CurveData : public QwtSeriesData<QPointF> {
public:
    const SensorData& values() const;
    SensorData& values();

    virtual QPointF sample(size_t i) const;
    virtual size_t size() const;

    virtual QRectF boundingRect() const;
};

#endif // CURVEDATA_H
