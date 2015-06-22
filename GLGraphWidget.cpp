#include "GLGraphWidget.h"

GLGraphWidget::GLGraphWidget(QWidget *parent) : QOpenGLWidget(parent)
{
//    this->setAutoFillBackground(false);

    m_graphPen = QPen(Qt::green);
    m_graphPen.setWidth(1);

    m_axisPen = QPen(Qt::yellow);
    m_axisPen.setWidth(2);
}
GLGraphWidget::~GLGraphWidget(){}

void GLGraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.fillRect(event->rect(), Qt::black);
    painter.setPen(m_axisPen);
    painter.drawLine(QPointF(0, event->rect().height()/2.0), QPointF(event->rect().width(), event->rect().height()/2.0));
    painter.drawLine(QPointF(5, 0), QPointF(5, event->rect().height()));
    painter.setPen(m_graphPen);
    painter.drawLine(QPointF(m_pt1.x(), m_pt1.y()+event->rect().height()/2.0), QPointF(m_pt2.x(), m_pt2.y()+event->rect().height()/2.0));
    painter.end();
}

void GLGraphWidget::resizeEvent(QResizeEvent *event)
{
    this->resize(event->size());
    this->update();
}

void GLGraphWidget::m_slotDrawGraph(QPointF pt1, QPointF pt2)
{
    m_pt1 = pt1;
    m_pt2 = pt2;
    this->update();
}

void GLGraphWidget::m_slotSaveScreenShot()
{
    QImage img(this->size(), QImage::Format_RGB32);
    QPainter painter(&img);
    this->render(&painter);
    img.save(QString("./screenshot_%1.png").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy_hh-mm-ss")), "PNG", 100);
}
