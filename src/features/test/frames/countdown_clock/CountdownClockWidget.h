#ifndef COUNTDOWNCLOCKWIDGET_H
#define COUNTDOWNCLOCKWIDGET_H

#include <QLabel>

class CountdownClockViewModel;

class CountdownClock : public QFrame {
    Q_OBJECT
public :
    explicit CountdownClock(
        CountdownClockViewModel* vm,
        QWidget* parent = nullptr);
private :
    QLabel* m_clock;
    CountdownClockViewModel* m_vm;
public slots:
    void onTimeRemainingChanged();
};

#endif // COUNTDOWNCLOCKWIDGET_H
