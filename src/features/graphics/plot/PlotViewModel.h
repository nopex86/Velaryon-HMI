#ifndef PLOTVIEWMODEL_H
#define PLOTVIEWMODEL_H

#include "src/core/Protocols/Messages.h"
#include <QObject>
#include <QColor>
class UdpReceiver;

struct CurveParameters{
    QString name;
    QString color;
    int id = 0;
};
struct PlotConfig{
    QString title;
    QVector<CurveParameters> curves;
};

struct timeRangeButton{
    QString name = "";
    double timerange = 0;
};

class TestBenchModel;
class Timer;

class PlotViewModel : public QObject {
    Q_OBJECT
public :
    explicit PlotViewModel(
        Timer* timer,
        TestBenchModel* testBenchM,
        QObject* parent = nullptr);
    bool getValue(const size_t& ID, double* value);
    bool getValueID(const QString& name, size_t* ID);
    QVector<CurveParameters> curveParameters();
    QString title();
    void addCurve(const QString& name,
                  const int id,
                  const QString& color);
    QVector<timeRangeButton> timeRangeButtons();
    QStringList visibleCurves();
    QString timeRangeSelected();
    double currentTime() const;
    double selectedTimeRange() const;
    void selectTimeRange(const QString& name);
    void set(const PlotConfig& config);
    void setCurveID(const QString& curvename,
                    const int& curveID);
    void initialise();
private :
    Timer* m_timer = nullptr;
    TestBenchModel* m_testBenchM = nullptr;
    QString m_title;
    QStringList m_visibleCurves = {};
    QVector<CurveParameters> m_curveParameters;
    QString m_timeRangeSelected = "All";
    QVector<timeRangeButton> m_timeRangeButtons;
    double m_currentTime = 0;
    double m_currentTimeRange = 0;
public slots :
    void isVisible(const QString& name,
                   const bool& status);
    void onTimerTimout();
    void onSensorDataUpdate();
signals :
    void curvesValuesChanged();
    void replot();
    void visibleCurvesChanged();
    void curvesParametersChanged();
    void SelectedTimeRangeChanged();
    void titleChanged();
};

#endif // PLOTVIEWMODEL_H
