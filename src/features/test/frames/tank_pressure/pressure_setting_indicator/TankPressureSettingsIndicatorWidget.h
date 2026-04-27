#ifndef TANKPRESSURESETTINGSINDICATORWIDGET_H
#define TANKPRESSURESETTINGSINDICATORWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>

class TankPressureSettingsIndicatorViewModel;
struct SetPressureCommand;

class TankPressureIndicador : public QLabel
{
    Q_OBJECT
public :
    explicit TankPressureIndicador(
        TankPressureSettingsIndicatorViewModel* vm,
        QPoint position,
        QWidget* parent = nullptr);
    QSize sizeHint() const override;
private :
    TankPressureSettingsIndicatorViewModel* m_vm;
    QSize m_size = {80,30};
public slots :
    void onDataUpdate();
};




#endif // TANKPRESSURESETTINGSINDICATORWIDGET_H
