#include "GlowPlugSwitchWidget.h"
#include "../ActuatorSwitchViewModel.h"

// Create, place valve object & connect it to sendCommand
GlowPlugSwitch::GlowPlugSwitch(
    ActuatorSwitchViewModel* vm,
    QWidget* parent) :
ActuatorSwitchWidget(vm, parent){
    display();
    vm->setStatusTexts({"ON", "OFF", "FAULTY"});
    vm->setStatus("OFF");
}
