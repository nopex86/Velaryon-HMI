#include "src/features/test/TestBenchModel.h"
#include "PlotViewModel.h"
#include "src/services/Timer/Timer.h"
#include <QDebug>
#include <QDateTime>

PlotViewModel::PlotViewModel(
    Timer* timer,
    TestBenchModel* testBenchM,
    QObject* parent):
    QObject(parent), m_timer(timer), m_testBenchM(testBenchM){
    connect(
        m_timer, &Timer::timeout,
        this, &PlotViewModel::onTimerTimout);
    connect(
        m_testBenchM, &TestBenchModel::statesListChanged,
        this, &PlotViewModel::onSensorDataUpdate);
    m_timeRangeButtons = {
        {"1m", 60},
        {"10m", 600},
        {"30m", 1800},
        {"All", 3600}
    };
    // m_curveParameters = {
    //     { "PS11", "#0000FF" },
    //     { "PS12", "#388AFF" },
    //     { "PS21", "#FF0000" },
    //     { "PS22", "#FF6363" },
    //     { "PS31", "#08CC0A" },
    //     { "PS41", "#B26701" },
    //     { "PS42", "#DB7F01" },
    //     { "PS51", "#B700FF" },
    //     { "PS61", "#FF9C00" },
    //     { "PS62", "#F08B08" },
    //     { "PS63", "#FFDD00" },
    //     { "PS64", "#FFBB2A" },
    // };
    // m_title = "Pressure section";
}

bool PlotViewModel::getValue(const size_t& ID, double* value){
    if (!m_testBenchM->getStatus(ID, value)) {
        return false;
    }
    return true;
}

bool PlotViewModel::getValueID(const QString& name, size_t* ID){
    if (!m_testBenchM->getStatusID(name.toStdString(), ID)) {
        return false;
    }
    return true;
}

void PlotViewModel::onSensorDataUpdate(){
    emit curvesValuesChanged();
}

void PlotViewModel::onTimerTimout(){
    emit replot();
}
void PlotViewModel::isVisible(
    const QString& name,
    const bool& status){
    if (status == true){
        if (!m_visibleCurves.contains(name)) {
            m_visibleCurves.append(name);
        }
    }
    if (status == false){
        m_visibleCurves.removeAll(name);
    }
    emit visibleCurvesChanged();
}

QVector<CurveParameters> PlotViewModel::curveParameters(){
    return m_curveParameters;
}

QString PlotViewModel::title(){
    return m_title;
}

void PlotViewModel::addCurve(
    const QString& name,
    const int id,
    const QString& color)
{
    CurveParameters curve;
    curve.name = name;
    curve.id = id;
    curve.color = color;
    m_curveParameters.append(curve);
    curvesParametersChanged();
}

QVector<timeRangeButton> PlotViewModel::timeRangeButtons(){
    return m_timeRangeButtons;
}

QString PlotViewModel::timeRangeSelected(){
    return m_timeRangeSelected;
}

double PlotViewModel::currentTime() const {
    return QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
}

double PlotViewModel::selectedTimeRange() const {
    return m_currentTimeRange;
}

void PlotViewModel::selectTimeRange(const QString& name){
    m_timeRangeSelected = name;
    for (const auto& b : std::as_const(m_timeRangeButtons)) {
        if (b.name == name) {
            m_currentTimeRange = b.timerange;
            break;
        }
    }
    emit SelectedTimeRangeChanged();
}

void PlotViewModel::set(const PlotConfig& config){
    m_title = config.title;
    emit titleChanged();
    m_curveParameters = config.curves;
    emit curvesParametersChanged();
}

void PlotViewModel::initialise(){
    emit titleChanged();
    emit curvesParametersChanged();
    emit SelectedTimeRangeChanged();
    emit visibleCurvesChanged();
}

void PlotViewModel::setCurveID(const QString& curvename,
                               const int& curveID){
    for (auto it = m_curveParameters.begin();
         it != m_curveParameters.end();
         ++it)
    {
        if (it->name == curvename){
            it->id = curveID;
            break;
        }
    }
}

QStringList PlotViewModel::visibleCurves(){
    return m_visibleCurves;
}
