#include "TankPressureControlerFrameFactory.h"
#include "TankPressureControlerViewModel.h"

TankPressureControlFrame* makeTankPressureControlFrame(
    AppViewModel* appVM, TpcFrameConfig config, QWidget* parent){
    TpcDeps deps = {
        .makeTankPressureControlerVM = [appVM](QObject* parent){
            return appVM->create<TankPressureControlerViewModel>(parent);}
    };
    return new TankPressureControlFrame(deps, config, parent);
}

