#ifndef DEBUGDISPLAY_H
#define DEBUGDISPLAY_H

#include <QFrame>
#include "DebugDisplayViewModel.h"
#include <QLabel>
#include <QVBoxLayout>

class Data : public QLabel{
    Q_OBJECT
public :
    explicit Data(DisplayBinding binding, QWidget* parent);
private :
    DisplayBinding m_binding;
public slots:
    void onRefresh();
};

class DebugDisplay : public QFrame {
    Q_OBJECT
public :
    DebugDisplay(DebugDisplayViewModel* vm, QWidget* parent = nullptr);
private :
    std::array<Data*, DebugDisplayViewModel::MAX_NUMBER_OF_BINDINGS> m_datas;
    QVBoxLayout* m_mainLayout;
    DebugDisplayViewModel* m_vm;
public slots:
    void onNumberOfBindingsChanged();
};
#endif // DEBUGDISPLAY_H
