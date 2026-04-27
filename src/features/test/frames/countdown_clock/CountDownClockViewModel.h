#ifndef COUNTDOWNCLOCKVIEWMODEL_H
#define COUNTDOWNCLOCKVIEWMODEL_H

#include <QObject>

struct CountdownFrame;
class UdpChannel;

class CountdownClockViewModel : public QObject{
    Q_OBJECT
public :
    explicit CountdownClockViewModel(
        UdpChannel* udpChannel,
        QObject* parent = nullptr);
    void initialise();
    int timeRemaining();
private :
    UdpChannel* m_udpChannel = nullptr;
    int m_timeRemaining = 0; //ms
signals :
    void timeRemainingChanged();
public slots :
    void onCountdownReceived(const CountdownFrame& frame);
};


#endif // COUNTDOWNCLOCKVIEWMODEL_H
