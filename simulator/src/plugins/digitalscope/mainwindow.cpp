#include "mainwindow.h"

#include <QMenuBar>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator"));

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    createMenu();
    createToolBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::exit()
{
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    m_newAction = fileMenu->addAction(tr("New"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    m_aboutAction = helpMenu()->addAction(tr("About"));
}

void MainWindow::createToolBar()
{
}