#ifndef SENSORVALUEINDICATORVIEWMODEL_H
#define SENSORVALUEINDICATORVIEWMODEL_H

#include <QObject>


class TestBenchModel;
class Timer;

class SensorValueIndicatorViewModel : public QObject {
    Q_OBJECT
public :
    explicit SensorValueIndicatorViewModel(
        Timer* timer,
        TestBenchModel* testBenchM,
        QObject* parent=nullptr);
    void setName(const QString& name);
    void setParameters(
        const QString& unit,
        const QString& mention = "");
    QString sensorName();
    QString valueUnit();
    QString valueMention();
    bool sensorValue(double& value);
private :
    Timer* m_timer;
    TestBenchModel* m_testBenchM;
    size_t m_valueID = NULL;
    QString m_sensorName = "";
    double m_sensorValue = NULL;
    QString m_valueUnit = "";
    QString m_valueMention = "";
signals:
    void sensorValueChanged();
    void valueNotFound();
};

#endif // SENSORVALUEINDICATORVIEWMODEL_H
