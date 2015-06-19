#ifndef GLGRAPHWIDGET_H
#define GLGRAPHWIDGET_H

#include <QtCore>
#include <QWidget>
#include <QOpenGLWidget>

#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QFont>
#include <QPen>

class GLGraphWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLGraphWidget(QWidget *parent);
    ~GLGraphWidget();


protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QPen m_graphPen;
    QPointF m_pt1;
    QPointF m_pt2;

private slots:
    void m_slotDrawGraph(QPointF pt1, QPointF pt2);

};

#endif // GLGRAPHWIDGET_H
