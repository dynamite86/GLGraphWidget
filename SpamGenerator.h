/*************************************************************************
File encoding: UTF-8.

Модуль для генерации и отправки сигналов.
Автор: dynamite, 2015.
*************************************************************************/

#ifndef SPAMER_H
#define SPAMER_H

#include <QtCore>
#include <windows.h>

class SpamerThreadedProcessing : public QObject
{
    Q_OBJECT

private:
    int m_minDelay;
    int m_maxDelay;

private slots:
    void m_spamingStart();

public:
    explicit SpamerThreadedProcessing(QObject *parent = 0);
    ~SpamerThreadedProcessing();

    bool initSpaming(int minDelay, int maxDelay);

signals:
    void signalPoints(QPointF pt1, QPointF pt2);
    void signalSpamingIsComplete();
};

class Spamer : public QObject
{
    Q_OBJECT

private:
    SpamerThreadedProcessing *m_spamerThread;

public:
    explicit Spamer(QObject *parent = 0);
    ~Spamer();

public slots:
    bool start(const int minDelay, const int maxDelay);

signals:
    void signalPoints(QPointF pt1, QPointF pt2);
    void signalSpamingIsComplete();
};

#endif // SPAMER_H
