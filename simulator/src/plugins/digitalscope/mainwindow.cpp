#include "mainwindow.h"
#include "glwidget.h"
#include "plot.h"

#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QDockWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>
#include <QComboBox>
#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>

#include <qextserialport.h>

MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator for Quadcopter"));
    plot = new Plot(this);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
/*
    m_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
                plot->canvas());
    m_picker->setStateMachine(new QwtPickerDragPointMachine());
    m_picker->setRubberBandPen(QColor(Qt::green));
    m_picker->setTrackerPen(QColor(Qt::white));
    connect(m_picker, SIGNAL(moved(const QPoint &)), SLOT(pickerMoved(const QPoint &)));
*/
    m_panner = new QwtPlotPanner(plot->canvas());
    m_panner->setMouseButton(Qt::MidButton);
    glWidget = new GLWidget(centralWidget);

    m_zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft, plot->canvas());
    m_zoomer->setTrackerMode(QwtPlotZoomer::ActiveOnly);
    m_zoomer->setTrackerPen(QColor(Qt::white));
    m_zoomer->setRubberBand(QwtPlotZoomer::RectRubberBand);
    m_zoomer->setRubberBandPen(QColor(Qt::green));
    createMenu();
    createActions();
    createToolBar();

    QHBoxLayout *serialLayout = new QHBoxLayout();
    m_combobox = new QComboBox();
    m_combobox->addItem(tr("COM1"));
    m_combobox->addItem(tr("COM2"));
    m_serialConnection = new QPushButton(tr("Connect"), this);
    connect(m_serialConnection, SIGNAL(clicked()), this, SLOT(serialConnection()));
    serialLayout->addStretch();
    serialLayout->addWidget(m_combobox);
    serialLayout->addWidget(m_serialConnection);
    m_connected = false;

    statusBar()->showMessage(tr("Ready"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(plot);
    mainLayout->addLayout(serialLayout);
    centralWidget->setLayout(mainLayout);
    //m_serialSamplingThread.start();

}

MainWindow::~MainWindow()
{
}

void MainWindow::newFile()
{
}

void MainWindow::exit()
{

}

void MainWindow::pickerMoved(const QPoint &pos)
{
    QString info;
    
    info.sprintf("x=%d, y=%d", pos.x(), pos.y());
    statusBar()->showMessage(info, 200);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simulator"),
        tr("<h2>Simulator v0.1</h2>"
           "<p>Copyright &copy; 2011 Open Robotics."
           "<p>Simulator is a cross-platform tools for building quadcopter."));
}
/*
void enableZoomMode(bool on)
{
    m_zoomer[0]->setEnable(on);
    m_zoomer[0]->zoom(0);
}
*/
void MainWindow::zoomIn()
{/*
    m_zoomFactor += 1;
    m_zoomer->zoom(m_zoomFactor);*/
}

void MainWindow::zoomOut()
{/*
    m_zoomFactor -= 1;
    m_zoomer->zoom(m_zoomFactor);*/
}

void MainWindow::serialConnection()
{
    if (m_connected) {
        m_connected = false;
        m_serialConnection->setText(tr("Connect"));
        m_combobox->setEnabled(true);
        closeSerialPort(m_combobox->currentText());
    } else {
        m_connected = true;
        m_serialConnection->setText(tr("Disconnect"));
        m_combobox->setEnabled(false);
        openSerialPort(m_combobox->currentText());
    }
}

void MainWindow::createActions()
{
    //m_zoomAction = viewMenu->addAction(tr("Zoom"));
    //m_zoomAction->setStatusTip(tr(""));
    //connect(m_zoomAction, SIGNAL(toggled(bool)), m_zoomer, setEnabled(bool));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    m_newAction = new QAction(QIcon(":/images/filenew.png"), tr("New"), this);
    m_newAction->setStatusTip(tr("Create a new file"));
    connect(m_newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    fileMenu->addAction(m_newAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    toolsMenu = menuBar()->addMenu(tr("Tools"));
    m_zoomInAction = new QAction(QIcon(":/images/zoomin.png"), tr("Zoom In"), this);
    m_zoomInAction->setStatusTip(tr("Zoom in"));
    connect(m_zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    m_zoomOutAction = new QAction(QIcon(":/images/zoomout.png"), tr("Zoom Out"), this);
    m_zoomOutAction->setStatusTip(tr("Zoom out"));m_zoomOutAction->setEnabled(false);
    connect(m_zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
    toolsMenu->addAction(m_zoomInAction);
    toolsMenu->addAction(m_zoomOutAction);

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcut(tr("Alt+F4"));
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(m_exitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show the application about infomation"));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu->addAction(m_aboutAction);

    m_aboutQtAction = new QAction(tr("About &Qt"), this);
    m_aboutQtAction->setStatusTip(tr("Show the Qt library's about information"));
    connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    helpMenu->addAction(m_aboutQtAction);
}

void MainWindow::createToolBar()
{
    m_fileToolBar = new QToolBar(tr("File"), this);
    addToolBar(Qt::TopToolBarArea, m_fileToolBar);
    m_fileToolBar->addAction(m_newAction);

    m_viewToolBar = new QToolBar(tr("View"), this);
    addToolBar(Qt::BottomToolBarArea, m_viewToolBar);
    m_viewToolBar->addAction(m_zoomInAction);
    m_viewToolBar->addAction(m_zoomOutAction);

    QDockWidget *m_leftDockWidget = new QDockWidget(tr("IMU Viewer"), this, 0);
    m_leftDockWidget->setWidget(glWidget);
    addDockWidget(Qt::LeftDockWidgetArea, m_leftDockWidget);
    viewMenu->addAction(m_leftDockWidget->toggleViewAction());
}

void MainWindow::openSerialPort(const QString& name)
{
    port = new QextSerialPort(name, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD115200);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    if (port->open(QIODevice::ReadOnly) == true) {
        connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        qDebug() << port->portName() << "Connected";
    } else {
        qDebug() << port->portName() << "failed to open:" << port->errorString();
    }
}

void MainWindow::closeSerialPort(const QString& name)
{

}

void MainWindow::onReadyRead()
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    if (a > 32) {
        bytes.resize(a);
        port->read(bytes.data(), bytes.size());
    //qDebug() << "bytes read:" << bytes.size();
    //qDebug() << "bytes:" << bytes;
        qDebug() << bytes;
    }
}
