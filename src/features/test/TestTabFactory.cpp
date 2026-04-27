#include "TestTabFactory.h"
#include "frames/tank_pressure/TankPressureControlerFrameFactory.h"
#include "frames/test_launcher/TestLauncherViewModel.h"
#include "frames/emergency_controls/EmergencyControlsViewModel.h"
#include "frames/countdown_clock/CountDownClockViewModel.h"
#include "frames/terminal/LogTerminalViewModel.h"

TestTab* makeTestTab(AppViewModel* appVM, QWidget* parent){
    TpcFrameConfig tpcCfg = {
        .controlers = {
            {
                .tankName = "LOX",
                .tankColor = QColor("#1BA1E2"),
                .sensorName = "PS21",
                .sensorUnit = "bar",
                .defaultPressureValue = 16,
                .pressureRange = {1, 20}
            },
            {
                .tankName = "ETH",
                .tankColor = QColor("#E51400"),
                .sensorName = "PS21",
                .sensorUnit = "bar",
                .defaultPressureValue = 16,
                .pressureRange = {1, 20}
            },
            {
                .tankName = "H2O",
                .tankColor = QColor("#F0A30A"),
                .sensorName = "PS61",
                .sensorUnit = "bar",
                .defaultPressureValue = 4,
                .pressureRange = {1, 10}
            }
        }
    };


    TestTabDeps deps = {
        .TpcFrame = makeTankPressureControlFrame(appVM, tpcCfg, parent),
        .makeTestLauncherVM = [appVM](QObject* parent){
              return appVM->create<TestLauncherViewModel>();},
        .makeEmergencyControlsVM = [appVM](QObject* parent){
              return appVM->create<EmergencyControlsViewModel>();},
        .makeCountdownClockVM = [appVM](QObject* parent){
              return appVM->create<CountdownClockViewModel>();},
        .makeLogTerminalVM = [appVM](QObject* parent){
              return appVM->create<LogTerminalViewModel>();}
    };
    return new TestTab(deps, parent);
}
