#include "mainwindow.h"
#include "plot.h"

#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QApplication>

#include <QHBoxLayout>

MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator for Quadcopter"));

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    createMenu();
    createActions();

    plot = new Plot(this);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(plot);
    centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simulator"),
        tr("<h2>Simulator v0.1</h2>"
           "<p>Copyright &copy; 2011 Open Robotics."
           "<p>Simulator is a cross-platform tool for building quadcopter."));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
}

void MainWindow::createActions()
{
    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcut(tr("Alt+F4"));
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(m_exitAction);

    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show the application about infomation"));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu->addAction(m_aboutAction);

    m_aboutQtAction = new QAction(tr("About &Qt"), this);
    m_aboutQtAction->setStatusTip(tr("Show the Qt library's about information"));
    connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    helpMenu->addAction(m_aboutQtAction);    
}