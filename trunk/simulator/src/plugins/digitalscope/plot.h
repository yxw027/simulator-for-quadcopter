#ifndef PLOT_H
#define PLOT_H

#include "serialsamplingthread.h"

#include <qwt_plot.h>
#include <qwt_system_clock.h>

class QwtPlotGrid;
class QwtPlotCurve;
class QwtPlotDirectPainter;


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
    }
public:
    Plot(QWidget *parent = 0);
    virtual ~Plot();

    virtual bool eventFilter(QObject *object, QEvent *event);

signals:
    void running(bool);
    void started();
    void paused();
    void stopped();

public slots:
    virtual void replot();

    //void running(bool);
    void pause();
    void stop();

protected:
    virtual void timerEvent(QTimerEvent *);
    virtual void widgetMouseMoveEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    QwtPlotGrid *m_grid;
    QwtPlotCurve *m_curve[SENSOR_TYPE_MAX];
    QwtSystemClock m_clock;

    QwtPlotDirectPainter *m_directPainter;

    int m_timerId;
    int m_paintedPoints;
    SerialSamplingThread m_serialSamplingThread;
    void updateCurve(int index);
};

#endif // PLOT_H
