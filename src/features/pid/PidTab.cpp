
/******************************************************************************************
**                                                                                       **
**   EngineTab generates the main content for the "Engine cycle" tab in the user         **
**   interface. This tab includes a graphical representation of the Arrax P&ID,          **
**   dynamic sensor values displayed at their position of the P&ID, a table summarizing  **
**   the valve names and their statuses, and a worker thread that updates sensor values. **                                                                             **
**                                                                                       **
******************************************************************************************/
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMap>
#include <QFont>
#include <QFrame>
#include <QThread>
#include <QVector>
#include <QDebug>

#include "PidTab.h"
#include "misc/CloseButtonWidget.h"
#include "misc/Logo.h"
#include "misc/Chrono.h"
#include "misc/initialise_valve/InitialiseValveButtonWidget.h"
#include "misc/initialise_valve/InitialiseValveButtonViewModel.h"
#include "misc/PidBackground.h"
#include "sensors/SensorValueIndicatorWidget.h"
#include "sensors/SensorValueIndicatorViewModel.h"
#include "actuator/StatusTableWidget.h"
#include "actuator/valve/ValveSwitchWidget.h"
#include "actuator/glowPlug/GlowPlugSwitchWidget.h"
#include "actuator/ActuatorSwitchViewModel.h"
#include "src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorWidget.h"
#include "src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorViewModel.h"
#include "PidViewModel.h"
#include "PidLayout.h"

Locker::Locker(QWidget* parent) : QLabel(parent){
    setGeometry(0,0,m_size.width(), m_size.height());
}

QSize Locker::sizeHint() const{
    return m_size;
}

PidTab::PidTab(const PidTabDeps& deps,
    const PidTabConfig& config,
    QWidget* parent) :
    QWidget(parent){
    m_vm = deps.pidVM;

    PidLayout* mainLayout = new PidLayout(this);

    PidBackground* background = new PidBackground(
        config.backgroud.path,
        config.backgroud.size.x(), config.backgroud.size.y(), this);
    mainLayout->addWidget(background, PidLayout::resize);

    m_locker = new Locker(this);
    m_locker->hide();


    // Add logo and close button
    Logo* logo = new Logo(this);
    logo->move(1313, 20);
    mainLayout->addWidget(logo, PidLayout::resize | PidLayout::alignRight);

    CloseButton* closeButton = new CloseButton(this);
    mainLayout->addWidget(closeButton, PidLayout::alignBottom | PidLayout::alignRight);

    Chrono* chrono = new Chrono(this); // Add chrono (timer) to the engine tab
    chrono->move(20,10);
    mainLayout->addWidget(chrono, PidLayout::alignLeft);

    InitialiseValveButtonViewModel* initialiseValveButtonVM = deps.makeInitialiseValveVM(this);
    InitialiseValveButton* initialiseValveButton = new InitialiseValveButton(initialiseValveButtonVM, this);// Button to reconnect the uC and control valves
    initialiseValveButton->move(50, 100);
    mainLayout->addWidget(initialiseValveButton, PidLayout::alignLeft | PidLayout::alignTop);

    StatusTableWidget* statusTable = new StatusTableWidget(
        config.statusTable.position, this);
    mainLayout->addWidget(statusTable, PidLayout::alignCenter|PidLayout::alignTop);

    for (const auto& v : config.valveSwitchs){
        ActuatorSwitchViewModel* ActuatorSwitchVM = deps.makeActuatorSwitchVM(this);
        ActuatorSwitchVM->setName(v.name);
        ActuatorSwitchVM->setStatus(v.status);
        ValveSwitch* valve = new ValveSwitch(
            ActuatorSwitchVM,
            this);
        valve->move(v.position);
        statusTable->addActuator(valve);
        mainLayout->addWidget(valve, PidLayout::alignCenter);
    }

    for (const auto& s : config.sensorValueIndicators){
        SensorValueIndicatorViewModel* sensorValueIndicatorVM =
            deps.makeSensorValueIndicatorVM(this);
        sensorValueIndicatorVM->setName(s.name);
        sensorValueIndicatorVM->setParameters(s.unit, s.mention);
        SensorValueIndicator* indicator = new SensorValueIndicator(
            sensorValueIndicatorVM,
            s.position,
            this);
        mainLayout->addWidget(indicator, PidLayout::alignCenter);
    }

    for (const auto& t : config.tankPressureIndicators){
        TankPressureSettingsIndicatorViewModel* TankPressureSettingsIndicatorVM =
            deps.makeTankPressureSettingsIndicatorVM(this);
        TankPressureSettingsIndicatorVM->setTankName(t.name);
        TankPressureIndicador* indicator = new TankPressureIndicador(
            TankPressureSettingsIndicatorVM,
            t.position,
            this);
        mainLayout->addWidget(indicator, PidLayout::alignCenter);
    }

    for (const auto& g : config.GlowPlugSwitchs){
        ActuatorSwitchViewModel* ActuatorSwitchVM = deps.makeActuatorSwitchVM(this);
        ActuatorSwitchVM->setName(g.name);
        GlowPlugSwitch* glowPlug = new GlowPlugSwitch(
            ActuatorSwitchVM,
            this);
        glowPlug->move(g.position);
        statusTable->addActuator(glowPlug);
        mainLayout->addWidget(glowPlug, PidLayout::alignCenter);
    }
}

void PidTab::onPIDStateChanged(){
    if (m_vm->pidIsLocked()){
        m_locker->show();
        m_locker->raise();
    }
    else{
        m_locker->hide();
    }
}


