#include "Timer.h"
#include <QTime>
Timer::Timer(QObject* parent) : QObject(parent) {
    m_timer.setTimerType(Qt::PreciseTimer);
    m_timer.setInterval(16);
    m_timer.start();
    m_lastRefresh = QTime::currentTime().msec();
    connect(&m_timer, &QTimer::timeout, [this]{
        int now = QTime::currentTime().msec();
        m_periodOfRefresh = now - m_lastRefresh;
        m_lastRefresh = now;
        emit timeout();
    });
}

bool Timer::setFrequecy(int freq){
    m_timer.setInterval(1000/freq);
    return true;
}

bool Timer::setPeriod(int period){
    m_timer.setInterval(period);
    return true;
}

int Timer::frequencyHz(){
    return 1000/m_periodOfRefresh;
}
