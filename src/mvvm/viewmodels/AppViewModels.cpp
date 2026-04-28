#include "AppViewModels.h"
#include "src/features/test/frames/emergency_controls/EmergencyControlsViewModel.h"
#include "src/features/test/frames/countdown_clock/CountDownClockViewModel.h"
#include "src/features/test/frames/test_launcher/TestLauncherViewModel.h"
#include "src/features/test/frames/terminal/LogTerminalViewModel.h"
#include "src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorViewModel.h"
#include "src/features/test/frames/tank_pressure/TankPressureControlerViewModel.h"
#include "src/mvvm/viewmodels/AppViewModels.h"
#include "src/features/graphics/plot/PlotViewModel.h"
#include "src/services/AppServices.h"
#include "src/features/test/frames/tank_pressure/PressureTanksModel.h"
#include "src/features/test/TestBenchModel.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "src/services/Logger/Logger.h"
#include "src/services/TXTManager/TxtParser.h"
#include "src/features/communication/udp/ui/UdpChannelParametersViewModel.h"
#include "src/features/file_export/ui/ExportMenuViewModel.h"
#include "src/services/Timer/Timer.h"
#include "src/features/pid/misc/initialise_valve/InitialiseValveButtonViewModel.h"
#include "src/features/pid/sensors/SensorValueIndicatorViewModel.h"
#include "src/features/pid/actuator/ActuatorSwitchViewModel.h"
#include "src/features/pid/PidViewModel.h"
#include "src/mvvm/models/AppModels.h"
#include "src/features/overlay/debug_display/DebugDisplayViewModel.h"

AppViewModel::AppViewModel(
    AppServices* services,
    AppModels* models,
    QObject* parent) :
    QObject(parent)
{
    LogTerminalViewModel* logTerminalVM = new LogTerminalViewModel(
        services->create<Logger>(),
        services->create<UdpChannel>(),
        this);
    registerFactory<LogTerminalViewModel>([logTerminalVM](QObject*){
        return logTerminalVM;
    });

    DebugDisplayViewModel* debugDisplayVM = new DebugDisplayViewModel(services->create<Timer>(), this);
    debugDisplayVM->displayVariable("log rate (Hz)", [services]{
        return services->create<UdpChannel>()->loggRateHz();
    });
    debugDisplayVM->displayVariable("frame loss rate (Hz)", [services]{
        return services->create<UdpChannel>()->frameLossRateHz();
    });
    registerFactory<DebugDisplayViewModel>([debugDisplayVM](QObject* p){
        return debugDisplayVM;
    });

    TestLauncherViewModel* TestLauncherVM = new TestLauncherViewModel(
        services->create<UdpChannel>(),
        services->create<TxtParser>(),
        models->create<TestBenchModel>(),
        services->create<FileSystem>(),
        services->create<Logger>(),
        this);
    registerFactory<TestLauncherViewModel>([TestLauncherVM](QObject*){
        return TestLauncherVM;
    });

    EmergencyControlsViewModel* EmergencyControlsVM = new EmergencyControlsViewModel(
        services->create<UdpChannel>(),
        models->create<TestBenchModel>(),
        this);
    registerFactory<EmergencyControlsViewModel>([EmergencyControlsVM](QObject*){
        return EmergencyControlsVM;
    });

    CountdownClockViewModel* CountdownClockVM = new CountdownClockViewModel(
        services->create<UdpChannel>(), this);
    registerFactory<CountdownClockViewModel>([CountdownClockVM](QObject*){
        return CountdownClockVM;
    });

    PidViewModel* PidVM = new PidViewModel(
        models->create<TestBenchModel>(),
        this);
    registerFactory<PidViewModel>([PidVM](QObject*){
        return PidVM;
    });


    InitialiseValveButtonViewModel* InitialiseValveButtonVM = new InitialiseValveButtonViewModel(
        services->create<UdpChannel>(),
        this);
    registerFactory<InitialiseValveButtonViewModel>([InitialiseValveButtonVM](QObject*){
        return InitialiseValveButtonVM;
    });

    registerFactory<TankPressureControlerViewModel>([services, models](QObject* p){
        return new TankPressureControlerViewModel(
            services->create<Timer>(),
            services->create<UdpChannel>(),
            models->create<TestBenchModel>(),
            models->create<PressureTanksModel>(),
            p);
    });

    registerFactory<PlotViewModel>([models, services](QObject* p){
        return new PlotViewModel(
            services->create<Timer>(),
            models->create<TestBenchModel>(),
            p);
    });

    registerFactory<ActuatorSwitchViewModel>([models, services](QObject* p){
        return new ActuatorSwitchViewModel(
            services->create<Timer>(),
            services->create<UdpChannel>(),
            models->create<TestBenchModel>(),
            p);
    });

    registerFactory<SensorValueIndicatorViewModel>([models, services](QObject* p){
        return new SensorValueIndicatorViewModel(
            services->create<Timer>(),
            models->create<TestBenchModel>(),p);
    });

    registerFactory<TankPressureSettingsIndicatorViewModel>([models](QObject* p){
        return new TankPressureSettingsIndicatorViewModel(
            models->create<PressureTanksModel>(),p);
    });

    registerFactory<UdpChannelParametersViewModel>([services](QObject* p){
        return new UdpChannelParametersViewModel(
            services->create<UdpChannel>(),
            p
            );
    });

    registerFactory<ExportMenuViewModel>([services](QObject* p){
        return new ExportMenuViewModel(
            services->create<FileSystem>(),
            services->create<CSVLogger>(), p);
    });
}




