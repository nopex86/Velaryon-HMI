#ifndef INITIALISEVALVEBUTTONWIDGET_H
#define INITIALISEVALVEBUTTONWIDGET_H

#include <QPushButton>
#include <QPoint>

class InitialiseValveButtonViewModel;

class InitialiseValveButton : public QPushButton{
    Q_OBJECT
public :
    explicit InitialiseValveButton(
        InitialiseValveButtonViewModel* vm,
        QWidget* parent = nullptr);
    QSize sizeHint() const override;
private :
    InitialiseValveButtonViewModel* m_vm;
    QSize m_size = {100, 30};
};

#endif // INITIALISEVALVEBUTTONWIDGET_H
