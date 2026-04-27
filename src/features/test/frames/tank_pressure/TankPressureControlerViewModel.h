#ifndef TANKPRESSURECONTROLERVIEWMODEL_H
#define TANKPRESSURECONTROLERVIEWMODEL_H

#include <QObject>
#include "src/core/Protocols/Messages.h"

class UdpChannel;
class TestBenchModel;
class PressureTanksModel;
class Timer;
enum class BBSTATUS{ON, OFF};

class TankPressureControlerViewModel : public QObject{
    Q_OBJECT
public:
    explicit TankPressureControlerViewModel(
        Timer* timer,
        UdpChannel* udpReceiver,
        TestBenchModel* TestBenchM,
        PressureTanksModel* tankModel,
        QObject* parent = nullptr);
    void setTankName(const QString& tankName);
    void setSensor(
        const QString& sensorName,
        const QString& unit);
    void setPressureDefaultValue(
        const double& value);
    void setPressureRange(
        const std::array<double, 2>& range);
    void initialise();

    QString tankName();
    std::array<double, 2> pressureRange();
    QString sensorName();
    double pressureSetting();
    BBSTATUS BBControlStatus();
    double sensorValue();
    QString sensorUnit();
private :
    Timer* m_timer;
    UdpChannel* m_udpChannel = nullptr;
    TestBenchModel* m_testBenchM = nullptr;
    PressureTanksModel* m_tankM = nullptr;
    size_t m_valueID = NULL;
    QString m_tankName = "";
    QString m_sensorName = "";
    QString m_sensorUnit = "bar";
    std::array<double, 2> m_pressureRange = {1,20};
    double m_pressureSetting = 16;
    BBSTATUS m_BBControl = BBSTATUS::OFF;
public slots:
    //Sensor data display handling :
    void onSensorDataReceived(); //connected to udpReceiver

    //BB enabling handling :
    void onBBCommandSent(); //connected to the View
    void onBBCommandACK(const AckBB& ack); //connected to udpReceiver

    //Pressure setting handling :
    void onPressureSettingSelected(const double& value); //connected to the View
    void onPressurSettingSent(); //connected to the View
signals:
    void sensorDataChanged();//Sensor data display handling
    void BBControlStatusChanged();//BB enabling handling
    void pressureSettingChanged();//Pressure setting handling
};

#endif //TANKPRESSURECONTROLERVIEWMODEL_H
