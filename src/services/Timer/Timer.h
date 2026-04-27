#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QObject{
    Q_OBJECT
public :
    explicit Timer(QObject* parent = nullptr);
    bool setFrequecy(int freq);
    bool setPeriod(int period);
    int frequencyHz();
private :
    int m_lastRefresh;
    int m_periodOfRefresh;
    QTimer m_timer;
signals:
    void timeout();
};

#endif // TIMER_H
