#include "mainwindow.h"
#include "glwidget.h"
#include "plot.h"

#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>

MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator for Quadcopter"));

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    glWidget = new GLWidget(centralWidget);
    //plot = new Plot(this);
    createMenu();
    createToolBar();

    m_statusBar = statusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::newFile()
{
    m_statusBar->showMessage(tr("New file"));
}

void MainWindow::exit()
{

}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    m_newAction = fileMenu->addAction(tr("New"));
    connect(m_newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = helpMenu->addAction(tr("About"));
}

void MainWindow::createToolBar()
{
}
