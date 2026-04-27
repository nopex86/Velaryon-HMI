/******************************************************************************************
**                                                                                       **
**   TestTab generates the main content for the "Test" tab in the user interface.        **
**   This tab includes several control frames such as tank pressure control, TVC,        **
**   sequence selection, emergency control and logs.                                     **
**   Any test (cold flows, hotfires,...) will be done mostly through this tab.           **
**                                                                                       **
******************************************************************************************/
#include <QWidget>
#include <QTabWidget>
#include <QFont>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QSlider>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTimer>

#include "TestTabView.h"
#include "frames/emergency_controls/EmergencyControlsWidget.h"
#include "frames/emergency_controls/EmergencyControlsViewModel.h"
#include "frames/ActuatorControlWidget.h"
#include "frames/countdown_clock/CountdownClockWidget.h"
#include "frames/countdown_clock/CountDownClockViewModel.h"
#include "frames/test_launcher/TestLaunchWidget.h"
#include "frames/test_launcher/TestLauncherViewModel.h"
#include "frames/tank_pressure/TankPressureControlFrameWidget.h"
#include "frames/TvcControlWidget.h"
#include "frames/terminal/LogTerminalWidget.h"
#include "frames/terminal/LogTerminalViewModel.h"

TestTab::TestTab(const TestTabDeps& deps, QWidget* parent) :QWidget(parent){
    //------------------------------------------------------------------------
    // Create test tab and retrieve existing tabs
    // QWidget* engine_tab = tabwidget->widget(0);
    // QWidget* cooling_tab = tabwidget->widget(1);
    QFont font = QFont("Arial", 10, QFont::Bold);
    QFont font2 = QFont("Arial", 10, QFont::Bold);

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->setContentsMargins(0, 0, 0, 0); // pas de marges
    mainlayout->setSpacing(0);                   // pas d'espace entre les 2

    QVBoxLayout *controlLayout = new QVBoxLayout();
    controlLayout->setContentsMargins(0, 0, 0, 0); // pas de marges
    controlLayout->setSpacing(0);                   // pas d'espace entre les 2

    QHBoxLayout *controlLayout2 = new QHBoxLayout();
    controlLayout2->setContentsMargins(0, 0, 0, 0); // pas de marges
    controlLayout2->setSpacing(0);                   // pas d'espace entre les 2

    QVBoxLayout *controlLayout3 = new QVBoxLayout();
    controlLayout3->setContentsMargins(0, 0, 0, 0); // pas de marges
    controlLayout3->setSpacing(0);                   // pas d'espace entre les 2

    LogTerminalViewModel* LogTerminalVM= deps.makeLogTerminalVM(this);
    logTerminalFrame* logTerminal = new logTerminalFrame(LogTerminalVM, this);

    CountdownClockViewModel* countdownClockVM = deps.makeCountdownClockVM(this);
    CountdownClock* clock = new CountdownClock(countdownClockVM, this);

    EmergencyControlsViewModel* emergencyControlsVM = deps.makeEmergencyControlsVM(this);
    EmergencyControls* emergencyControls = new EmergencyControls(emergencyControlsVM, this);

    TestLauncherViewModel* TestLauncherVM = deps.makeTestLauncherVM(this);
    TestLauncher* lauchSection = new TestLauncher(TestLauncherVM, this);

    actuatorControlFrame* actuatorControlSection = new actuatorControlFrame(this, font);
    tvcControlFrame* tvcControlSection = new tvcControlFrame(this, font); //(work must be done for proper display and code efficiency)

    TankPressureControlFrame* tankPressureControlSection = deps.TpcFrame;

    controlLayout3->addWidget(tvcControlSection, 75);
    controlLayout3->addWidget(clock, 25);

    controlLayout2->addWidget(tankPressureControlSection, 50);
    controlLayout2->addWidget(actuatorControlSection, 20);
    controlLayout2->addLayout(controlLayout3, 30);

    controlLayout->addLayout(controlLayout2, 45);
    controlLayout->addWidget(lauchSection, 30);
    controlLayout->addWidget(emergencyControls, 25);

    mainlayout->addLayout(controlLayout, 55);
    mainlayout->addWidget(logTerminal, 45);
};

