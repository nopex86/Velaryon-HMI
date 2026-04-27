#ifndef TANKPRESSURESETTINGSINDICATORVIEWMODEL_H
#define TANKPRESSURESETTINGSINDICATORVIEWMODEL_H

#include <QObject>

struct SetPressureCommand;
class PressureTanksModel;

class TankPressureSettingsIndicatorViewModel : public QObject {
    Q_OBJECT
public:
    explicit TankPressureSettingsIndicatorViewModel(
        PressureTanksModel* model,
        QObject* parent= nullptr);
    void setParameters(
        const QString& unit,
        const QString& mention = "");
    void setTankName(const QString& name);
    int getPressureSetting();
    QString getTankName();
    QString getValueUnit();
    QString getValueMention();
    void initialise();
private :
    PressureTanksModel* m_model;
    QString m_tankName;
    int m_tankPressureSettingValue = NULL;
    QString m_valueUnit = "";
    QString m_valueMention = "";
public slots:
    void onPressureSettingChanged();

signals:
    void PressureSettingChanged();

};

#endif // TANKPRESSURESETTINGSINDICATORVIEWMODEL_H
