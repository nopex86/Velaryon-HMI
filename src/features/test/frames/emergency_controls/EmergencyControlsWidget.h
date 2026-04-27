#ifndef EMERGENCYCONTROLSWIDGET_H
#define EMERGENCYCONTROLSWIDGET_H

#include <QPushButton>
#include <QLabel>

class EmergencyControlsViewModel;

class EmergencyControls : public QWidget {
    Q_OBJECT
public :
    explicit EmergencyControls(
        EmergencyControlsViewModel* vm,
        QWidget* parent);
};

#endif // EMERGENCYCONTROLSWIDGET_H
