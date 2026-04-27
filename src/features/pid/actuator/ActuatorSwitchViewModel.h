#ifndef ACTUATORSWITCHVIEWMODEL_H
#define ACTUATORSWITCHVIEWMODEL_H

#include <QObject>

class UdpChannel;
class TestBenchModel;
class Timer;

class ActuatorSwitchViewModel : public QObject{
    Q_OBJECT
public :
    explicit ActuatorSwitchViewModel(
        Timer* timer,
        UdpChannel* udpChannel,
        TestBenchModel* testBenchM,
        QObject* parent = nullptr);
    void setName(const QString& name);
    void setStatus(const QString& status);
    void setDefaultStatus(const QString& status);
    void setStatusTexts(const QStringList& list);
    QString name();
    QString status();
    QString statusColor();
    QString defaultStatus();
    void initialise();
    void updateStatus();
private :
    Timer* m_timer;
    UdpChannel* m_udpChannel = nullptr;
    TestBenchModel* m_testBenchM = nullptr;
    QString m_name = "";
    QString m_status = "NO DATA";
    QString m_statusColor = "red";
    QString m_defaultStatus = "";
    QStringList m_statusTexts = {"ENABLED", "DISABLED", "FAULTY"};
    size_t m_statusID = NULL;
public slots :
    void enable();
    void disable();
signals:
    void statusChanged();
};

#endif // ACTUATORSWITCHVIEWMODEL_H
