#ifndef ACTUATORSWITCHWIDGET_H
#define ACTUATORSWITCHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ActuatorSwitchViewModel;

class ActuatorSwitchWidget : public QFrame{
    Q_OBJECT
public :
    explicit ActuatorSwitchWidget(
        ActuatorSwitchViewModel* vm,
        QWidget* parent = nullptr);
    ActuatorSwitchViewModel* viewModel();
    QSize sizeHint() const override;
    void virtual display();
    void setFixedSize(int w, int h);
    void setFont(const QFont& font);
protected :
    ActuatorSwitchViewModel* m_vm;
    QLabel* m_title;
    QLabel* m_statusIndicator;
    QLabel* m_defaultStatusIndicator;
    QPushButton* m_enableButton;
    QPushButton* m_disableButton;
    QSize m_size = {106, 86};
public slots :
    void onActuatorStatusChanged();
};

#endif // ACTUATORSWITCHWIDGET_H
