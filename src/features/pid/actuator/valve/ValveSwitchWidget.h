#ifndef VALVE_H
#define VALVE_H

#include "../ActuatorSwitchWidget.h"

class ActuatorSwitchViewModel;

class ValveSwitch : public ActuatorSwitchWidget
{
    Q_OBJECT
public :
    explicit ValveSwitch(
        ActuatorSwitchViewModel* vm,
        QWidget* parent = nullptr);
};

#endif // VALVE_H
