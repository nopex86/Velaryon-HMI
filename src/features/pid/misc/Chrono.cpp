#include "Chrono.h"
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QVBoxLayout>

Chrono::Chrono(QWidget* parent) : QWidget(parent) {
    setGeometry(0, 0, m_size.width(), m_size.height());
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setAlignment(Qt::AlignLeft);


    // Create the date and time label
    QLabel* dateTimeLabel = new QLabel(this);
    dateTimeLabel->setFont(QFont("Arial", 10, QFont::Bold));
    dateTimeLabel->setStyleSheet("QLabel { color: black; }");
    // dateTimeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(dateTimeLabel);

    // Create the chrono label
    QLabel* chronoLabel = new QLabel(this);
    chronoLabel->setFont(QFont("Arial", 10, QFont::Bold));
    chronoLabel->setStyleSheet("QLabel { color: black; }");
    // chronoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(chronoLabel);

    // Store the launch time
    QDateTime launchTime = QDateTime::currentDateTime();

    // Create the timer with the parent to ensure proper ownership
    QTimer* timer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        // Update current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        dateTimeLabel->setText("Date: " + currentDateTime.toString("yyyy/MM/dd") +
                               " Time: " + currentDateTime.toString("hh:mm:ss"));

        // Calculate elapsed time since launch
        qint64 elapsedSecs = launchTime.secsTo(currentDateTime);
        QTime elapsedTime(0, 0); // Start from 00:00:00
        elapsedTime = elapsedTime.addSecs(elapsedSecs);
        QString chronoString = "IHM uptime: " + elapsedTime.toString("hh:mm:ss");
        chronoLabel->setText(chronoString);
    });

    // Start the timer
    timer->start(100);  // Update every 100ms
}

QSize Chrono::sizeHint() const {
    return m_size;
}
