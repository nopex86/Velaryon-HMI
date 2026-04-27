#include "ValveSwitchWidget.h"
#include "../ActuatorSwitchViewModel.h"

// Create, place valve object & connect it to sendCommand
ValveSwitch::ValveSwitch(
    ActuatorSwitchViewModel* vm,
    QWidget* parent) :
    ActuatorSwitchWidget(vm, parent){
    display();
    if (vm->status() == "OPEN"){
        vm->setDefaultStatus("NO");
    }
    else if (vm->status() == "CLOSED"){
        vm->setDefaultStatus("NC");
    }
    vm->setStatusTexts({"OPEN", "CLOSED", "FAULTY"});
    m_enableButton->setText("Open");
    m_disableButton->setText("Close");
}
