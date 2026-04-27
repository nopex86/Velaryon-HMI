#include "CountDownClockViewModel.h"
#include "src/core/Protocols/Messages.h"
#include "src/features/communication/udp/UdpChannel.h"

CountdownClockViewModel::CountdownClockViewModel(
    UdpChannel* udpChannel,
    QObject* parent) :
    QObject(parent){
    m_udpChannel = udpChannel;
    connect(
        m_udpChannel, &UdpChannel::countdownReceived,
        this, &CountdownClockViewModel::onCountdownReceived);
}

void CountdownClockViewModel::initialise(){
    emit timeRemainingChanged();
}

int CountdownClockViewModel::timeRemaining(){
    return m_timeRemaining;
}

void CountdownClockViewModel::onCountdownReceived(const CountdownFrame& frame){
    m_timeRemaining = frame.countdown_ms;
    emit timeRemainingChanged();
}
