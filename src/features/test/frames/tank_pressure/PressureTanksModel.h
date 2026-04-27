#ifndef TANKPRESSURESETTINGSMODEL_H
#define TANKPRESSURESETTINGSMODEL_H

#include <QObject>
#include <QMap>

class PressureTanksModel : public QObject{
    Q_OBJECT
public :
    explicit PressureTanksModel(
        QObject* parent = nullptr);
    double getPressureSetting(
        const QString& tankName);
    void setPressureSetting(
        const QString& tankName,
        const double& value);
private :
    QMap<QString, double> m_PressureSettings;
signals :
    void pressureSettingChanged();
};

#endif // TANKPRESSURESETTINGSMODEL_H
