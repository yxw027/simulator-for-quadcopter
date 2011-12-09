#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotGrid;
class QwtPlotCurve;
class QwtSystemClock;
class QwtPlotDirectPainter;


class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot(QWidget *parent = 0);
    virtual ~Plot();

public slots:
    virtual void replot();

    void start();
    void pause();
    void stop();

protected:
    virtual void timerEvent(QTimerEvent *);

private:
    QwtPlotGrid *m_grid;
    QwtPlotCurve *m_curve;
    QwtSystemClock m_clock;
    QwtPlotDirectPainter *m_directPainter;
    
    int m_timerId;
};

#endif // PLOT_H
