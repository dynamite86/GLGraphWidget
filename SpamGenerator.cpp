/*************************************************************************
File encoding: UTF-8.

Модуль для генерации и отправки сигналов.
Автор: dynamite, 2015.
*************************************************************************/

#include "SpamGenerator.h"

Spamer::Spamer(QObject *parent) : QObject(parent){}
Spamer::~Spamer(){}

bool Spamer::start(const int minDelay, const int maxDelay, const QRect &targetRect)
{
    m_spamerThread = new SpamerThreadedProcessing(NULL);
    if(!m_spamerThread->initSpaming(minDelay, maxDelay, targetRect))
    {
        delete m_spamerThread;
        return false;
    }
    QThread *threadForProcessing = new QThread;
    m_spamerThread->moveToThread(threadForProcessing);

    connect(threadForProcessing, SIGNAL(started()),                       m_spamerThread,      SLOT(m_spamingStart()));
    connect(threadForProcessing, SIGNAL(finished()),                      threadForProcessing, SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(m_signalSpamingIsComplete()),     m_spamerThread,      SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(m_signalSpamingIsComplete()),     threadForProcessing, SLOT(quit()));
    connect(m_spamerThread,      SIGNAL(m_signalPoints(QPointF,QPointF)), this,                SIGNAL(m_signalPoints(QPointF,QPointF)));
    connect(m_spamerThread,      SIGNAL(m_signalSpamingIsComplete()),     this,                SIGNAL(m_signalSpamingIsComplete()));

    threadForProcessing->start();
    return true;
}

void SpamerThreadedProcessing::m_spamingStart()
{
    QPointF pt1;
    QPointF pt2;
    srand(QTime().msecsTo(QTime::currentTime()));

    for(qreal x = 0; x < m_targetRect.width(); x+=0.1)
    {
        pt2.setX(x);
        pt2.setY(qSin(x/50.0)*(m_targetRect.height()/2.0-20));
        m_signalPoints(pt1, pt2);
        pt1 = pt2;
        Sleep((rand()%m_maxDelay + m_minDelay));
    }
    m_signalSpamingIsComplete();
}

SpamerThreadedProcessing::SpamerThreadedProcessing(QObject *parent) : QObject(parent){}

SpamerThreadedProcessing::~SpamerThreadedProcessing(){}

bool SpamerThreadedProcessing::initSpaming(const int minDelay, const int maxDelay, const QRect &targetRect)
{
    m_minDelay   = minDelay;
    m_maxDelay   = maxDelay;
    m_targetRect = targetRect;
    return true;
}

