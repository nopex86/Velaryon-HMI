#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QPlainTextEdit>

class AppViewModel;
class TankPressureControlFrame;
class TestLauncherViewModel;
class EmergencyControlsViewModel;
class CountdownClockViewModel;
class LogTerminalViewModel;

struct TestTabDeps{
    TankPressureControlFrame* TpcFrame;
    std::function<TestLauncherViewModel* (QObject* parent)> makeTestLauncherVM;
    std::function<EmergencyControlsViewModel* (QObject* parent)> makeEmergencyControlsVM;
    std::function<CountdownClockViewModel* (QObject* parent)> makeCountdownClockVM;
    std::function<LogTerminalViewModel* (QObject* parent)> makeLogTerminalVM;
};

class TestTab : public QWidget
{
    Q_OBJECT

public :
    explicit TestTab(
        const TestTabDeps& deps,
        QWidget* parent=nullptr);
};

#endif // TEST_H
