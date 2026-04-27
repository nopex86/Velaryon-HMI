#ifndef GLOWPLUGSWITCHWIDGET_H
#define GLOWPLUGSWITCHWIDGET_H

#include "../ActuatorSwitchWidget.h"

class ActuatorSwitchViewModel;

class GlowPlugSwitch : public ActuatorSwitchWidget
{
    Q_OBJECT
public :
    explicit GlowPlugSwitch(
        ActuatorSwitchViewModel* vm,
        QWidget* parent = nullptr);
};

#endif // GLOWPLUGSWITCHWIDGET_H
