#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qwt_system_clock.h>

class QwtPlotGrid;
class QwtPlotCurve;

class Plot : public QwtPlot
{
    Q_OBJECT
public:
    enum {
        SENSOR_ACCL_X,
        SENSOR_ACCL_Y,
        SENSOR_ACCL_Z,
        SENSOR_GYRO_X,
        SENSOR_GYRO_Y,
        SENSOR_GYRO_Z,
        SENSOR_TYPE_MAX
    };
public:
    Plot(QWidget *parent = 0);
    virtual ~Plot();


public slots:
    void showCurve(QwtPlotItem *item, bool on);

protected:
    virtual void timerEvent(QTimerEvent *);

private:
    QwtPlotGrid *m_grid;
    QwtPlotCurve *m_curve[SENSOR_TYPE_MAX];
    QwtSystemClock m_clock;

    int m_timerId;
};

#endif // PLOT_H
