#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "dependencies/QCustomPlot/qcustomplot.h"
#include "PlotViewModel.h"

class Plot : public QWidget {
    Q_OBJECT
public :
    explicit Plot(
        PlotViewModel* vm,
        QWidget* parent = nullptr);
private :
    PlotViewModel* m_vm;
    QCustomPlot* m_plot;
    QFont m_font;
    QMap<QString, QPushButton*> m_timeRangeButtons;
    QGridLayout* m_curveSelectionGrid;
    QString m_TRBtnUnselectedStyle;
    QString m_TRBtnSelectedStyle;
    std::function<QString(const QString&)> m_checkboxCheckedStyle;
    QString m_checkboxUncheckedStyle = "";
    struct Binding{
        QString name;
        size_t valueID;
        QCPGraph* graph;
    };
    void initialiseBindings();
    std::vector<Binding> m_bindings;
public slots :
    void onCurvesValuesChanged();
    void onCurvesParametersChanged();
    void onSelectedTimeRangeChanged();
    void onVisibleCurvesChanged();
    void onReplot();
signals :
    void isVisible(
        const QString& name,
        const bool& status);
    void selectTimeRange(const QString& name);
};

#endif // PLOTWIDGET_H
