#include "PidTabFactory.h"
#include "src/mvvm/viewmodels/AppViewModels.h"
#include "src/features/pid/PidViewModel.h"
#include "src/features/pid/misc/initialise_valve/InitialiseValveButtonViewModel.h"
#include "src/features/pid/actuator/ActuatorSwitchViewModel.h"
#include "src/features/pid/sensors/SensorValueIndicatorViewModel.h"
#include "src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorViewModel.h"

PidTab* makePidTab(AppViewModel* appVM, const PidTabConfig& config, QWidget* parent) {
    PidTabDeps deps{
        .pidVM = appVM->create<PidViewModel>(),
        .makeInitialiseValveVM = [appVM](QObject* parent) {
            return appVM->create<InitialiseValveButtonViewModel>(parent);
        },
        .makeActuatorSwitchVM = [appVM](QObject* parent) {
            return appVM->create<ActuatorSwitchViewModel>(parent);
        },
        .makeSensorValueIndicatorVM = [appVM](QObject* parent) {
            return appVM->create<SensorValueIndicatorViewModel>(parent);
        },
        .makeTankPressureSettingsIndicatorVM = [appVM](QObject* parent) {
            return appVM->create<TankPressureSettingsIndicatorViewModel>(
                parent
                );
        }
    };
    return new PidTab(deps, config, parent);
}
