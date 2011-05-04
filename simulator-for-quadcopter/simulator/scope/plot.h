#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotGrid;
class QwtPlotCurve;


class Plot : public QwtPlot {
    Q_OBJECT

public:
    enum SensorData {
        Accel_X,
        Accel_Y,
        Accel_Z,

        Gyro_X,
        Gyro_Y,
        Gyro_Z
    };

public:
    Plot(QWidget *parent = 0);

private:
    QwtPlotGrid *grid;
    QwtPlotCurve *curve;
};

#endif // PLOT_H
