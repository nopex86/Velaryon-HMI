#include "InitialiseValveButtonViewModel.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "src/core/Protocols/Messages.h"
#include <QThread>

InitialiseValveButtonViewModel::InitialiseValveButtonViewModel(
    UdpChannel* udpChannel,
    QObject* parent) :
    QObject(parent){
    m_udpChannel = udpChannel;
}

void InitialiseValveButtonViewModel::initialiseValve(){
    ValveCommand command;

    // Isolate the GN2 and air tanks to avoid loss
    command.valveName = "SV11";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV21";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV31";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV32";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV51";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV61";
    command.closed = false;
    m_udpChannel->sendData(command);
    QThread::msleep(10);

    command.valveName = "SV62";
    command.closed = false;
    m_udpChannel->sendData(command);

}
