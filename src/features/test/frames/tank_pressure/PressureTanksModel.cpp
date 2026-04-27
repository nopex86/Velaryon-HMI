#include "PressureTanksModel.h"

PressureTanksModel::PressureTanksModel(
    QObject* parent) :
    QObject(parent){}

double PressureTanksModel::getPressureSetting(
    const QString& tankName){
    return m_PressureSettings[tankName];
}
void PressureTanksModel::setPressureSetting(
    const QString& tankName,
    const double& value){
    m_PressureSettings[tankName] = value;
    emit pressureSettingChanged();
}
