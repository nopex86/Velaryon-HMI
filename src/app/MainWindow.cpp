/*****************************************************************************************
**                                                                                      **
**   createMainWindow generates a main window with a QTabWidget containing four tabs:   **
**   Engine cycle, Cooling cycle, Test, and Graphic.                                    **
**                                                                                      **
**   Each tab focuses on a specific aspect of the project, providing a clear and        **
**   organized way to divide the content.                                               **
**   This approach helps users concentrate on one area at a time.                       **
**                                                                                      **
*****************************************************************************************/
#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QMenuBar>
#include <QShortcut>
#include <QStackedLayout>
#include "src/app/MainWindow.h"
#include "src/features/pid/PidTabFactory.h"
#include "src/features/test/TestTabFactory.h"
#include "src/features/graphics/GraphicTabFactory.h"
#include "src/features/menu_bar/files/FilesMenuFactory.h"
#include "src/features/menu_bar/tools/ToolsMenuFactory.h"
#include "src/features/overlay/OverlayFactory.h"



MainWindow::MainWindow(AppViewModel* appVM, QWidget* parent) : QMainWindow(parent){
    auto* shortcut = new QShortcut(Qt::Key_F10, this);
    connect(shortcut, &QShortcut::activated, this, [this]() {
        menuBar()->setVisible(!menuBar()->isVisible());
        qDebug() << "menuBar is visible ? " << menuBar()->isVisible();
    });
    menuBar()->setVisible(false);
    menuBar()->addMenu(makeFileMenu(appVM, this));
    menuBar()->addMenu(makeToolsMenu(appVM, this));

    QWidget* container = new QWidget(this);

    QStackedLayout* stackedLayout = new QStackedLayout(container);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    QTabWidget* tabWidget = new QTabWidget();
    stackedLayout->addWidget(tabWidget);

    QWidget* overlay = makeOverlay(appVM);
    stackedLayout->addWidget(overlay);

    stackedLayout->setCurrentIndex(1);

    // Customize the tab widget's appearance with a stylesheet
    QString styleSheet = QString(R"(
        QTabWidget::pane { border: 1px solid #000000; }
        QTabBar::tab {
            background-color: #bcbaba; color: black; height: %1px; width: %2px; font-weight: bold;
            border: 1px solid #000000;
        }
        QTabBar::tab:hover { background-color: #a8a8a8; }
        QTabBar::tab:selected { background-color: #d4d4d4; }
    )").arg(40).arg(150);
    tabWidget->setStyleSheet(styleSheet);



    // Add tabs to the tab widget with associated content
    PidTabConfig engCycleCfg{
        .backgroud = {"./pictures/Arrax_engine.png", {1533, 767}},
        .sensorValueIndicators = {
            {"PS11", "bar", "", {562, 547}},
            {"PS12", "bar", "", {1260, 425}},
            {"PS21", "bar", "", {562, 151}},
            {"PS22", "bar", "", {1260, 279}},
            {"PS31", "bar", "", {155, 162}},
            {"PS41", "bar", "", {1325, 265}},
            {"PS42", "bar", "", {1390, 265}},
            {"TS11", "°C", "", {1165, 435}},
            {"TS12", "°C", "", {290, 20}},
            {"TS41", "°C", "", {1325, 434}},
            {"TS42", "°C", "", {1390, 434}},
            {"FM11", "L/s", "", {807, 417}},
            {"FM21", "L/s", "", {858,282}},
            {"ref5V", "V", "AC", {290,40}}
        },
        .valveSwitchs = {
            {"SV11", {715, 523}, "OPEN"},
            {"SV12", {1010, 435}, "CLOSED"},
            {"SV13", {1012, 578}, "CLOSED"},
            {"SV21", {712, 117}, "OPEN"},
            {"SV22", {975, 205}, "CLOSED"},
            {"SV24", {1012, 60}, "CLOSED"},
            {"SV31", {110, 237}, "CLOSED"},
            {"SV32", {322, 210}, "OPEN"},
            {"SV33", {519, 440}, "CLOSED"},
            {"SV34", {519, 200}, "CLOSED"},
            {"SV35", {1260, 159}, "CLOSED"},
            {"SV36", {1260, 480}, "CLOSED"}
        },
        .statusTable = {{150, 400}},
        .tankPressureIndicators = {
            {"ETH", {627, 312}},
            {"LOX", {627, 312 + 68}}
        }
    };
    tabWidget->addTab(makePidTab(appVM, engCycleCfg, this), "Ingiter cycle");

    PidTabConfig coolCycleCfg{
        .backgroud = {"./pictures/Arrax_cooling.png", {1533, 767}},
        .sensorValueIndicators = {
            {"PS51", "bar", "", {176, 157}},
            {"PS61", "bar", "", {577, 550}},
            {"PS62", "bar", "", {577, 157}},
            {"PS63", "bar", "", {1106, 295}},
            {"PS64", "bar", "", {1239, 295}},
            {"TS61", "°C", "", {1106, 410}},
            {"TS62", "°C", "", {1239, 410}},
            {"FM61", "L/s", "", {1023, 310}},
            {"ref5V", "V", "AC", {290,20}}
        },
        .valveSwitchs = {
            {"SV51", {310, 195}, "OPEN", },
            {"SV52", {465, 450}, "CLOSED"},
            {"SV53", {465, 190}, "CLOSED"},
            {"SV61", {752, 518}, "OPEN"},
            {"SV62", {752, 120}, "OPEN"},
            {"SV63", {904, 227}, "CLOSED"}
        },
        .statusTable = {{200, 420}},
        .tankPressureIndicators ={
            {"H2O", {649, 349}}
        }
    };

    tabWidget->addTab(makePidTab(appVM, coolCycleCfg, this), "Cooling cycle");

    PidTabConfig ignCycleCfg{
        .backgroud = {"./pictures/Arrax_igniter.png", {1498, 807}},
        .sensorValueIndicators = {
            {"PS21", "bar", "", {650, 130}},
            {"PS23", "bar", "", {1205, 427}},
            {"PS31", "bar", "", {172, 197}},
            {"PS71", "bar", "", {1205, 703}},
            {"PS81", "bar", "", {1260, 460}}
        },
        .valveSwitchs = {
            {"SV21", QPoint(710,225), "OPEN"},
            {"SV22", QPoint(880,340), "CLOSED"},
            {"SV24", QPoint(905,130), "CLOSED"},
            {"SV25", QPoint(1030,360), "CLOSED"},
            {"SV31", QPoint(15,240), "CLOSED"},
            {"SV32", QPoint(260,375), "OPEN"},
            {"SV33", QPoint(432,445), "CLOSED"},
            {"SV34", QPoint(432,240), "CLOSED"},
            {"SV35", QPoint(1280,160), "CLOSED"},
            {"SV71", QPoint(1030,670), "CLOSED"}
        },
        .statusTable = {{200, 440}},
        .tankPressureIndicators ={},
        .GlowPlugSwitchs = {
            {"GP", {980, 520}}
        }

    };
    tabWidget->addTab(makePidTab(appVM, ignCycleCfg, this), "Ingiter cycle");

    tabWidget->addTab(makeTestTab(appVM, this), "Test");     // Test tab
    tabWidget->addTab(makeGraphicTab(appVM, this), "Graphic");             // Graphic tab

    // Set the QTabWidget as the central widget of the main window
    this->setCentralWidget(container);

    // Set the window to be borderless and maximized (pseudo-fullscreen)
    // this->setWindowFlags(Qt::FramelessWindowHint);
    this->showMaximized();  // Maximize the window on startup
    // this->showFullScreen();
}

