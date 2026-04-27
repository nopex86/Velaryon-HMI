#ifndef PRESSURISEDTANK_H
#define PRESSURISEDTANK_H

#include <QObject>
#include <QFont>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>

class TankPressureControlerViewModel;

class TankPressureControler : public QWidget
{
    Q_OBJECT

public:
    explicit TankPressureControler(
        TankPressureControlerViewModel* vm,
        QWidget* parent=nullptr);

    //Setting handlers :
    void set_color(QColor backgroundColor);
public slots :
    void onsensorDataChanged();
    void onBBControlStatusChanged();
private:
    TankPressureControlerViewModel* m_vm=nullptr;
    QFont m_font = QFont("Arial", 10, QFont::Bold);
    QPushButton* m_BB_button;
    QLabel* m_tankLogo;
    QDoubleSpinBox* m_pressureSelector;
    QLabel* m_pressureIndicator;
};


#endif // PRESSURISEDTANK_H
