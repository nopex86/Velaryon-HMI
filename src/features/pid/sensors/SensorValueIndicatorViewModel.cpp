#include <QDebug>
#include "SensorValueIndicatorViewModel.h"
#include "src/features/test/TestBenchModel.h"
#include "src/services/Timer/Timer.h"

SensorValueIndicatorViewModel::SensorValueIndicatorViewModel(
        Timer* timer,
        TestBenchModel* testBenchM,
        QObject* parent
    ):
    QObject(parent), m_timer(timer), m_testBenchM(testBenchM)
{
    connect(
        m_timer, &Timer::timeout,
        this, [this]{
            emit sensorValueChanged();
        });
}
void SensorValueIndicatorViewModel::setName(const QString& name){
    m_sensorName = name;
}
void SensorValueIndicatorViewModel::setParameters(
    const QString& unit,
    const QString& mention){
    m_valueUnit = unit;
    m_valueMention = mention;
}
QString SensorValueIndicatorViewModel::sensorName(){
    return m_sensorName;
}
QString SensorValueIndicatorViewModel::valueUnit(){
    return m_valueUnit;
}
QString SensorValueIndicatorViewModel::valueMention(){
    return m_valueMention;
}
bool SensorValueIndicatorViewModel::sensorValue(double& value){
    if (m_valueID == NULL){
        m_testBenchM->getStatusID(m_sensorName.toStdString(), &m_valueID);
    }
    if (!m_testBenchM->getStatus(m_valueID, &value)) {
        return false;
    }
    m_sensorValue = value;
    return true;
}
