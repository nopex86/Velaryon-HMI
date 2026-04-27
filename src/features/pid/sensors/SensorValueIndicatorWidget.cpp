#include "SensorValueIndicatorWidget.h"
#include "SensorValueIndicatorViewModel.h"

SensorValueIndicator::SensorValueIndicator(
    SensorValueIndicatorViewModel* vm,
    const QPoint& position,
    QWidget* parent)
    : QLabel(parent){
    m_vm = vm;

    setGeometry(position.x(),position.y(),
                m_size.width(), m_size.height());
    setFont(m_font);           // Set font style
    setStyleSheet(R"(background-color: #dcdcdc)");       // Set background color
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);   // Align text to the center
    setText("no data");
    connect(
        vm, &SensorValueIndicatorViewModel::sensorValueChanged,
        this, &SensorValueIndicator::onValueChanged);
}

void SensorValueIndicator::onValueChanged(){
    if (isVisible()){
        double value;
        if (!m_vm->sensorValue(value)){
            setText("no data");
        }
        else {
            setText(
                QString::number(value)
                + " " + m_vm->valueUnit()
                + " " + m_vm->valueMention());
        }
    }
}

QSize SensorValueIndicator::sizeHint() const {
    return m_size;
}












