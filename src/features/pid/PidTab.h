#ifndef PIDtab_H
#define PIDtab_H

#include <QMainWindow>
#include <QLabel>
#include <QLayout>

struct PidTabConfig{
    struct BackgroundConfig{
        QString path;
        QPoint size;
    };
    struct SensorValueIndicatorConfig{
        QString name;
        QString unit = "";
        QString mention ="";
        QPoint position;
    };
    struct ValveSwitchConfig{
        QString name;
        QPoint position;
        QString status;
    };
    struct StatusTableConfig{
        QPoint position;
    };
    struct TankPressureIndicadorConfig{
        QString name;
        QPoint position;
    };
    struct GlowPlugSwitchConfig{
        QString name;
        QPoint position;
    };
    BackgroundConfig backgroud;
    QVector<SensorValueIndicatorConfig> sensorValueIndicators;
    QVector<ValveSwitchConfig> valveSwitchs;
    StatusTableConfig statusTable;
    QVector<TankPressureIndicadorConfig> tankPressureIndicators;
    QVector<GlowPlugSwitchConfig> GlowPlugSwitchs;
};

class PidViewModel;
class InitialiseValveButtonViewModel;
class ActuatorSwitchViewModel;
class SensorValueIndicatorViewModel;
class TankPressureSettingsIndicatorViewModel;

struct PidTabDeps{
    PidViewModel* pidVM;
    std::function<InitialiseValveButtonViewModel* (QObject* parent)>
        makeInitialiseValveVM;
    std::function<ActuatorSwitchViewModel* (QObject* parent)>
        makeActuatorSwitchVM;
    std::function<SensorValueIndicatorViewModel* (QObject* parent)>
        makeSensorValueIndicatorVM;
    std::function<TankPressureSettingsIndicatorViewModel* (QObject* parent)>
        makeTankPressureSettingsIndicatorVM;
};

class Locker : public QLabel{
    Q_OBJECT
public :
    explicit Locker(QWidget* parent=nullptr);
    QSize sizeHint() const override;
private :
    QSize m_size = {1533, 767};
};

class PidTab : public QWidget
{
    Q_OBJECT
public :
    explicit PidTab(
        const PidTabDeps& deps,
        const PidTabConfig& config,
        QWidget* parent=nullptr);
private :
    PidViewModel* m_vm = nullptr;
    Locker* m_locker;
public slots :
    void onPIDStateChanged();
};


#endif // PIDtab_H
