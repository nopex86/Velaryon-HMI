#include "TankPressureControlerViewModel.h"
#include <QDebug>
#include "src/features/communication/udp/UdpChannel.h"
#include "../../TestBenchModel.h"
#include "PressureTanksModel.h"
#include "src/core/Protocols/Messages.h"
#include "src/features/communication/udp/codecs/UdpCodec.h"
#include "src/services/Timer/Timer.h"

TankPressureControlerViewModel::TankPressureControlerViewModel(
    Timer* timer,
    UdpChannel* udpChannel,
    TestBenchModel* TestBenchM,
    PressureTanksModel* tankModel,
    QObject* parent):
    QObject(parent),
    m_timer(timer),
    m_udpChannel(udpChannel), m_testBenchM(TestBenchM)
{
    m_tankM = tankModel;
    connect(udpChannel, &UdpChannel::AckBBReceived,
            this, &TankPressureControlerViewModel::onBBCommandACK);
    connect(m_timer, &Timer::timeout,
            this, &TankPressureControlerViewModel::onSensorDataReceived);
}

QString TankPressureControlerViewModel::tankName(){
    return m_tankName;
}
std::array<double, 2> TankPressureControlerViewModel::pressureRange(){
    return m_pressureRange;
}
QString TankPressureControlerViewModel::sensorName(){
    return m_sensorName;
}
double TankPressureControlerViewModel::pressureSetting(){
    return m_pressureSetting;
}
BBSTATUS TankPressureControlerViewModel::BBControlStatus(){
    return m_BBControl;
}
double TankPressureControlerViewModel::sensorValue(){
    if (m_valueID == NULL){
        m_testBenchM->getStatusID(m_sensorName.toStdString(), &m_valueID);
    }
    double value;
    if (!m_testBenchM->getStatus(m_valueID, &value)) {
        return 0;
    }
    return value;
}
QString TankPressureControlerViewModel::sensorUnit(){
    return m_sensorUnit;
}

void TankPressureControlerViewModel::setTankName(
    const QString& tankName) {
    m_tankName = tankName;
}
void TankPressureControlerViewModel::setSensor(
    const QString& sensorName,
    const QString& unit){
    m_sensorName = sensorName;
    m_sensorUnit = unit;
}
void TankPressureControlerViewModel::setPressureRange(
    const std::array<double, 2>& range){
    m_pressureRange = range;
}
void TankPressureControlerViewModel::setPressureDefaultValue(
    const double& value){
    m_pressureSetting = value;
    m_tankM->setPressureSetting(m_tankName, value);
}
void TankPressureControlerViewModel::initialise(){
    emit sensorDataChanged();
    emit BBControlStatusChanged();
    emit pressureSettingChanged();
}

//Sensor data display handling :
void TankPressureControlerViewModel::onSensorDataReceived(){
    emit sensorDataChanged();
}

//BB enabling handling :
void TankPressureControlerViewModel::onBBCommandSent(){
        BBControlCommand command;
        command.tankName = m_tankName;
        command.activated = (
            m_BBControl==BBSTATUS::ON ?
            false : true);
        if (m_udpChannel != nullptr){
            m_udpChannel->sendData(command);
        }
}
void TankPressureControlerViewModel::onBBCommandACK(
    const AckBB& ack){
    if (ack.tank == ProtocolCodec::tankID[m_tankName]){
        m_BBControl = (
            ack.enlabled == 0 ?
            BBSTATUS::OFF : BBSTATUS::ON);
        emit BBControlStatusChanged();
    }
}

//Pressure setting handling :
void TankPressureControlerViewModel::onPressureSettingSelected(
    const double& value){
    m_pressureSetting = value;
    m_tankM->setPressureSetting(m_tankName, value);
    emit pressureSettingChanged();
}
void TankPressureControlerViewModel::onPressurSettingSent(){
    SetPressureCommand command;
    command.pressure = m_pressureSetting;
    command.tankName = m_tankName;
    if (m_udpChannel != nullptr){
        m_udpChannel->sendData(command);
    }
}

