#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1920, 1080);
    GLGraphWidget *m_glWidget = new GLGraphWidget(this);
    ui->gridLayout->addWidget(m_glWidget, 0, 0);

    m_spamer = new Spamer;
    connect(m_spamer, SIGNAL(signalPoints(QPointF,QPointF)), m_glWidget, SLOT(m_slotDrawGraph(QPointF,QPointF)));
    m_spamer->start(50, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void signalPoint(QPointF pt);
