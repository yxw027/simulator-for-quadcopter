#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotGrid;
class QwtPlotCurve;


class Plot : public QwtPlot {
    Q_OBJECT

public:
    Plot(QWidget *parent = 0);

protected:
    virtual void timerEvent(QTimerEvent *e);

private:
    QwtPlotGrid *grid;
    QwtPlotCurve *curve;
};

#endif // PLOT_H
