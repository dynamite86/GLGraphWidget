/*************************************************************************
File encoding: UTF-8.

Модуль для генерации и отправки сигналов.
Автор: dynamite, 2015.
*************************************************************************/

#include "SpamGenerator.h"

Spamer::Spamer(QObject *parent) : QObject(parent){}
Spamer::~Spamer(){}

bool Spamer::start(const int minDelay, const int maxDelay)
{
    m_spamerThread = new SpamerThreadedProcessing(NULL);
    if(!m_spamerThread->initSpaming(minDelay, maxDelay))
    {
        delete m_spamerThread;
        return false;
    }
    QThread *threadForProcessing = new QThread;
    m_spamerThread->moveToThread(threadForProcessing);

    connect(threadForProcessing, SIGNAL(started()),                     m_spamerThread,      SLOT(m_spamingStart()));
    connect(threadForProcessing, SIGNAL(finished()),                    threadForProcessing, SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(signalSpamingIsComplete()),     m_spamerThread,      SLOT(deleteLater()));
    connect(m_spamerThread,      SIGNAL(signalSpamingIsComplete()),     threadForProcessing, SLOT(quit()));
    connect(m_spamerThread,      SIGNAL(signalPoints(QPointF,QPointF)), this,                SIGNAL(signalPoints(QPointF,QPointF)));

    threadForProcessing->start();
    return true;
}

void SpamerThreadedProcessing::m_spamingStart()
{
    QPointF pt1;
    QPointF pt2;
    srand(QTime().msecsTo(QTime::currentTime()));

    for(qreal x = 0; x < 10000000000000000; x+=1)
    {
        pt2.setX(x);
        pt2.setY(qSin(qDegreesToRadians(x)));
        signalPoints(pt1, pt2);
        pt1 = pt2;
        Sleep((rand()%m_maxDelay + m_minDelay));
    }
    signalSpamingIsComplete();
}

SpamerThreadedProcessing::SpamerThreadedProcessing(QObject *parent) : QObject(parent){}

SpamerThreadedProcessing::~SpamerThreadedProcessing(){}

bool SpamerThreadedProcessing::initSpaming(int minDelay, int maxDelay)
{
    m_minDelay = minDelay;
    m_maxDelay = maxDelay;
    return true;
}

