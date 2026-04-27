#include "TankPressureSettingsIndicatorViewModel.h"
#include "../PressureTanksModel.h"
#include <QDebug>


TankPressureSettingsIndicatorViewModel::TankPressureSettingsIndicatorViewModel(
    PressureTanksModel* model,
    QObject* parent) : QObject(parent){
    m_model = model;
    connect(
        m_model, &PressureTanksModel::pressureSettingChanged,
        this, &TankPressureSettingsIndicatorViewModel::onPressureSettingChanged);
}

void TankPressureSettingsIndicatorViewModel::setTankName(const QString& name){
    m_tankName = name;
}

void TankPressureSettingsIndicatorViewModel::setParameters(
    const QString& unit,
    const QString& mention){
    m_valueUnit = unit;
    m_valueMention = mention;
}
QString TankPressureSettingsIndicatorViewModel::getTankName(){
    return m_tankName;
}
QString TankPressureSettingsIndicatorViewModel::getValueUnit(){
    return m_valueUnit;
}
QString TankPressureSettingsIndicatorViewModel::getValueMention(){
    return m_valueMention;
}
void TankPressureSettingsIndicatorViewModel:: initialise(){
    emit PressureSettingChanged();
}

void TankPressureSettingsIndicatorViewModel::onPressureSettingChanged(){
    m_tankPressureSettingValue = m_model->getPressureSetting(m_tankName);
    emit PressureSettingChanged();
}
int TankPressureSettingsIndicatorViewModel::getPressureSetting(){
    return m_tankPressureSettingValue;
}
