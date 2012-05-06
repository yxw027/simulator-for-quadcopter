#include "plot.h"
#include "seriesdata.h"

#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>

#include <QTimerEvent>
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
    setAxisScale(QwtPlot::yLeft, -1.0, 1.0);

    // Legend
    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::RightLegend);
    connect(this, SIGNAL(legendChecked(QwtPlotItem*,bool)), this, SLOT(showCurve(QwtPlotItem*,bool)));

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
    mY->setYValue(0.0);
    mY->attach(this);

    // Insert curves
    QwtPlotCurve *curve;

    curve = new QwtPlotCurve(tr("A_X"));
    curve->setPen(QPen(Qt::red));
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curve->setData(new SeriesData());
    curve->attach(this);
    m_curve[SENSOR_ACCL_X] = curve;

    showCurve(m_curve[SENSOR_ACCL_X], true);

    setAutoFillBackground(true);

    m_clock.start();
    m_timerId = startTimer(100);
}

Plot::~Plot()
{
}

void Plot::showCurve(QwtPlotItem *item, bool on)
{
    QwtLegendItem *legendItem;

    item->setVisible(on);
    legendItem = qobject_cast<QwtLegendItem *>(legend()->find(item));

    if (legendItem)
        legendItem->setChecked(on);

    replot();
}

void Plot::timerEvent(QTimerEvent *event)
{
    if (m_timerId == event->timerId()) {
        SeriesData *buffer = (SeriesData *)m_curve[SENSOR_ACCL_X]->data();
        buffer->increaseStartIndex(m_clock.elapsed() / 1000.0);
    }

    replot();
    QwtPlot::timerEvent(event);
}
