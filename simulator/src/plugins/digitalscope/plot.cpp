#include "plot.h"
#include "curvedata.h"

#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_system_clock.h>
#include <qwt_plot_directpainter.h>


Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    // Set title
    this->setTitle(tr("Sensor Data Window"));

    // Set Background
    this->setCanvasBackground(Qt::white);

    // Set axis
    this->setAxisTitle(QwtPlot::xBottom, tr("Time(s)"));
    this->setAxisScale(QwtPlot::xBottom, 0, 10.0);

    this->setAxisTitle(QwtPlot::yLeft, tr("Sensor Value(v)"));
    this->setAxisScale(QwtPlot::yLeft, 0, 50.0);

    // Legend
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::RightLegend);

    // Insert Grid
    m_grid = new QwtPlotGrid;
    m_grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    m_grid->enableXMin(true);
    m_grid->enableYMin(true);
    m_grid->attach(this);

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
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setData(new CurveData());
    curve->attach(this);

    //curve->setRawSamples();

    this->setAutoFillBackground(true);

    m_directPainter = new QwtPlotDirectPainter(this);
}

Plot::~Plot()
{
}

void Plot::replot()
{
    QwtPlot::replot();
}

void Plot::start()
{
    m_clock.start();
    m_timerId = startTimer(100);
}

void Plot::pause()
{
}

void Plot::stop()
{
}

void Plot::timerEvent(QTimerEvent *event)
{
    if (m_timerId == event->timerId) {
    }
    QwtPlot::timerEvent(event);
}
