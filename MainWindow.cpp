#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GLGraphWidget *m_glWidget = new GLGraphWidget(this);
    ui->gridLayout->addWidget(m_glWidget, 0, 0);
//    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//    this->setWindowState(Qt::WindowFullScreen);
//    this->showFullScreen();

    m_spamer = new Spamer;
    connect(m_spamer, SIGNAL(m_signalPoints(QPointF,QPointF)), m_glWidget, SLOT(m_slotDrawGraph(QPointF,QPointF)));
    connect(m_spamer, SIGNAL(m_signalSpamingIsComplete()),     m_glWidget, SLOT(m_slotSaveScreenShot()));

    m_spamer->start(1, 2, m_glWidget->rect());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
    QMainWindow::keyPressEvent(event);
}
