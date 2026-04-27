#include "TankPressureSettingsIndicatorWidget.h"
#include "TankPressureSettingsIndicatorViewModel.h"

TankPressureIndicador::TankPressureIndicador(
    TankPressureSettingsIndicatorViewModel* vm,
    QPoint position,
    QWidget* parent) :
    QLabel(parent){
    m_vm = vm;
    setGeometry(position.x(), position.y(),
                m_size.width(), m_size.height());
    setFont(QFont("Arial", 10, QFont::Bold));
    setAlignment(Qt::AlignCenter);
    setText("no vm");

    connect(
        m_vm, &TankPressureSettingsIndicatorViewModel::PressureSettingChanged,
        this, &TankPressureIndicador::onDataUpdate);
    m_vm->initialise();
};

void TankPressureIndicador::onDataUpdate() {
    QString value = "no data";
    if (m_vm->getPressureSetting() != NULL){
        value = QString::number(m_vm->getPressureSetting());
    }
    setText(QStringLiteral("%1 %2 %3")
        .arg(value,
             m_vm->getValueUnit(),
             m_vm->getValueMention()));
}

QSize TankPressureIndicador::sizeHint() const{
    return m_size;
}
