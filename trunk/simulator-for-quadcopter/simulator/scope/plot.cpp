#include "plot.h"
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    // Set title
    this->setTitle(tr("Sensor Data Window"));

    // Set Background
    this->setCanvasBackground(Qt::gray);

    // Set axis
    this->setAxisTitle(QwtPlot::xBottom, tr("Time(s)"));
    this->setAxisScale(QwtPlot::xBottom, 0, 10.0);

    this->setAxisTitle(QwtPlot::yLeft, tr("Sensor Value"));
    this->setAxisScale(QwtPlot::yLeft, 0, 50.0);

    // Insert Grid
    grid = new QwtPlotGrid;
    grid->attach(this);

    // Insert markers
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("y = 25.0"));
    mY->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(25.0);
    mY->attach(this);

    // Insert curve
    curve = new QwtPlotCurve(tr("Accl_X"));
    curve->setPen(QPen(Qt::black));
    //curve->setData(new FunctionData(::sin));
    curve->attach(this);
}
