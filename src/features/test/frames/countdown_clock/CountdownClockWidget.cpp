#include <QVBoxLayout>
#include <QTimer>

#include "CountdownClockWidget.h"
#include "CountDownClockViewModel.h"

CountdownClock ::CountdownClock (
    CountdownClockViewModel* vm,
    QWidget* parent) :
    QFrame(parent){
    m_vm = vm;

    this->setFrameShape(QFrame::StyledPanel);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    m_clock = new QLabel("--.---", this);
    m_clock->setStyleSheet(R"(font-size: 24px;font-weight: bold;)");

    QVBoxLayout *frameLayout = new QVBoxLayout(this);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    frameLayout->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(m_clock);

    connect(
        vm, &CountdownClockViewModel::timeRemainingChanged,
        this, &CountdownClock::onTimeRemainingChanged);
    vm->initialise();
};

void CountdownClock ::onTimeRemainingChanged(){
    int timeRemaining = m_vm->timeRemaining();
    int seconds = (timeRemaining % 60000) / 1000;
    int milliseconds = qAbs(timeRemaining % 1000);
    m_clock->setText(QString::asprintf("%02d.%03d",seconds, milliseconds));
}


// Countdown before start of ignition
