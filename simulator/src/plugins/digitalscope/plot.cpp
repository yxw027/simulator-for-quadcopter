#include "plot.h"
#include "curvedata.h"
#include "sensordata.h"

#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_system_clock.h>
#include <qwt_plot_directpainter.h>

#include <QTimerEvent>
#include <QDebug>

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    // Set title
    setTitle(tr("Sensor Data Window"));

    // Set background
    setCanvasBackground(Qt::white);

    // Set axis
    setAxisTitle(QwtPlot::xBottom, tr("Time(s)"));
    setAxisScale(QwtPlot::xBottom, 0, 10.0);

    setAxisTitle(QwtPlot::yLeft, tr("Sensor Value(v)"));
    setAxisScale(QwtPlot::yLeft, 0, 50.0);

    // Legend
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::RightLegend);

    // Insert grid
    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->enableYMin(true);    
    m_grid->setMajPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    m_grid->setMinPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    m_grid->attach(this);

    // Insert markers
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("y = 0.0"));
    mY->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(25.0);
    mY->attach(this);

    // Insert curves
    m_curve = new QwtPlotCurve(tr("Accelerometer_X"));
    m_curve->setPen(QPen(Qt::red));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    m_curve = new QwtPlotCurve(tr("Accelerometer_Y"));
    m_curve->setPen(QPen(Qt::green));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    m_curve = new QwtPlotCurve(tr("Accelerometer_Z"));
    m_curve->setPen(QPen(Qt::blue));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    m_curve = new QwtPlotCurve(tr("Gyroscope_X"));
    m_curve->setPen(QPen(Qt::blue));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    m_curve = new QwtPlotCurve(tr("Gyroscope_Y"));
    m_curve->setPen(QPen(Qt::blue));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    m_curve = new QwtPlotCurve(tr("Gyroscope_Z"));
    m_curve->setPen(QPen(Qt::blue));
    m_curve->setStyle(QwtPlotCurve::Lines);
    m_curve->setData(new CurveData());
    m_curve->attach(this);

    setAutoFillBackground(true);
    setAutoReplot(false);

    m_directPainter = new QwtPlotDirectPainter(this);
    start();
}

Plot::~Plot()
{
}

bool Plot::eventFilter(QObject *object, QEvent *event)
{
    if (!canvas())
        return false;

    switch (event->type()) {
    case QEvent::MouseMove:
        widgetMouseMoveEvent((QMouseEvent *)event);
        break;
    default:
        break;
    }

    return QwtPlot::eventFilter(object, event);
}

void Plot::widgetMouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPoint pos = mouseEvent->pos();
    
    replot();
}

virtual void paintEvent(QPaintEvent *paintEvent)
{
    Qwt::paintEvent(paintEvent);
}

void Plot::replot()
{
    QwtPlot::replot();
}

void Plot::start()
{
    m_clock.start();
    m_timerId = startTimer(10);   // 0.01-second timer

    emit started();
}

void Plot::pause()
{
    emit paused();
}

void Plot::stop()
{
    stopTimer();
    m_clock.stop();

    emit stopped();
}

void Plot::updateCurve()
{
    CurveData *data = (CurveData *)m_curve->data();

    data->values().lock();

    const int numPoints = data->size();
    if (numPoints > m_paintedPoints) {
        const bool doClip = !canvas()->testAttribute(Qt::WA_PaintOnScreen);
        if (doClip) {

        }
        m_directPainter->drawSeries(m_curve, m_paintedPoints - 1, m_paintedPoints);
        m_paintedPoints += 1;
    }

    data->values().unlock();
}

void Plot::timerEvent(QTimerEvent *te)
{
    if (m_timerId == te->timerId()) {
        updateCurve();
    }
    QwtPlot::timerEvent(te);
}
