#include "ActuatorSwitchViewModel.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "src/features/test/TestBenchModel.h"
#include "src/services/Timer/Timer.h"
#include <QDebug>

ActuatorSwitchViewModel::ActuatorSwitchViewModel(
    Timer* timer,
    UdpChannel* udpChannel,
    TestBenchModel* testBenchM,
    QObject* parent):
    QObject(parent), m_timer(timer), m_udpChannel(udpChannel), m_testBenchM(testBenchM)
{
    connect(m_timer, &Timer::timeout,
            this, &ActuatorSwitchViewModel::updateStatus);

}

void ActuatorSwitchViewModel::setName(const QString& name){m_name = name;}
void ActuatorSwitchViewModel::setStatus(const QString& status){
    if (status == m_statusTexts[0]){
        m_statusColor = "green";
    }
    else if (status == m_statusTexts[1]){
        m_statusColor = "red";
    }
    else {
        m_statusColor = "lightgray";
    }
    m_status = status;
    emit statusChanged();
}
void ActuatorSwitchViewModel::setDefaultStatus(const QString& status){m_defaultStatus = status;}
void ActuatorSwitchViewModel::setStatusTexts(const QStringList& list){
    m_statusTexts = list;
    setStatus(status());
}

QString ActuatorSwitchViewModel::name(){return m_name;}
QString ActuatorSwitchViewModel::status(){return m_status;}
QString ActuatorSwitchViewModel::statusColor(){return m_statusColor;}
QString ActuatorSwitchViewModel::defaultStatus(){return m_defaultStatus;}

void ActuatorSwitchViewModel::initialise(){
    emit statusChanged();
}

void ActuatorSwitchViewModel::updateStatus(){
    if (m_statusID == NULL){
        m_testBenchM->getStatusID(m_name.toStdString(), &m_statusID);
    }
    double status;
    if (!m_testBenchM->getStatus(m_statusID, &status)) {
        return;
    }

    if (status == 0){
        setStatus(m_statusTexts[1]);
    }
    else if (status == 1){
        setStatus(m_statusTexts[0]);
    }
    else {
        setStatus(m_statusTexts[2]);
    }
    emit statusChanged();
}

void ActuatorSwitchViewModel::enable(){
    ValveCommand command;
    command.valveName = m_name;
    command.closed = true;
    m_udpChannel->sendData(command);
}
void ActuatorSwitchViewModel::disable(){
    ValveCommand command;
    command.valveName = m_name;
    command.closed = false;
    m_udpChannel->sendData(command);
}
