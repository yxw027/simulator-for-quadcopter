#include <QtGui>

//#include "scope/plot.h"


#include "glwidget.h"
#include "mainwindow.h"


MainWindow::MainWindow()
{
    glWidget = new GLWidget;
/*
    port = new AbstractSerial();
    port->setDeviceName("COM1");
    if (port->open(AbstractSerial::ReadOnly)) {
        if (!port->setBaudRate(AbstractSerial::BaudRate115200)) {
            qDebug() << "Set baud rate " <<  AbstractSerial::BaudRate115200 << " error.";
            goto err;
        };

        if (!port->setDataBits(AbstractSerial::DataBits8)) {
            qDebug() << "Set data bits " <<  AbstractSerial::DataBits8 << " error.";
            goto err;
        }

        if (!port->setParity(AbstractSerial::ParityNone)) {
            qDebug() << "Set parity " <<  AbstractSerial::ParityNone << " error.";
            goto err;
        }

        if (!port->setStopBits(AbstractSerial::StopBits1)) {
            qDebug() << "Set stop bits " <<  AbstractSerial::StopBits1 << " error.";
            goto err;
        }

        if (!port->setFlowControl(AbstractSerial::FlowControlOff)) {
            qDebug() << "Set flow " <<  AbstractSerial::FlowControlOff << " error.";
            goto err;
        }
    }
*/
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //plot = new Plot;

    serialButton = new QPushButton(tr("connect"), centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(serialButton);
    //setLayout(mainLayout);
    centralWidget->setLayout(mainLayout);



    createMenus();
    setWindowTitle(tr("simulator-for-quadcopter"));
}

QSize MainWindow::sizeHint() const
{
    return QSize(600, 200);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
//    helpMenu = menuBar()->addMenu(tr("&Help"));
}
