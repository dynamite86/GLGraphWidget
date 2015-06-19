#include "GLGraphWidget.h"

GLGraphWidget::GLGraphWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setAutoFillBackground(false);
    m_graphPen = QPen(Qt::green);
    m_graphPen.setWidth(2);
}
GLGraphWidget::~GLGraphWidget(){}

void GLGraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(m_graphPen);
    painter.drawLine(QPointF(m_pt1.x(), m_pt1.y()+event->rect().height()/2.0), QPointF(m_pt2.x(), m_pt2.y()+event->rect().height()/2.0));
    painter.end();
}

void GLGraphWidget::resizeEvent(QResizeEvent *event)
{
    update();
}

void GLGraphWidget::m_slotDrawGraph(QPointF pt1, QPointF pt2)
{
    m_pt1 = pt1;
    m_pt2 = pt2;
    update();
}
