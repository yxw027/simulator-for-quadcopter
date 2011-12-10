#include "mainwindow.h"
#include "glwidget.h"
#include "plot.h"

#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_panner.h>

MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator for Quadcopter"));
    plot = new Plot(this);
    centralWidget = new QWidget(this);
    setCentralWidget(plot);
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
    m_panner->setMouseButton(Qt::LeftButton);
    //glWidget = new GLWidget(centralWidget);

    createMenu();
    createToolBar();

    statusBar();
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

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    m_newAction = fileMenu->addAction(tr("New"));
    m_newAction->setStatusTip(tr("Create a new file"));
    connect(m_newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    fileMenu->addAction(m_newAction);

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
}
