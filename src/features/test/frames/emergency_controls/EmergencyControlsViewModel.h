#ifndef EMERGENCYCONTROLSVIEWMODEL_H
#define EMERGENCYCONTROLSVIEWMODEL_H

#include <QObject>

class UdpChannel;
class TestBenchModel;

class EmergencyControlsViewModel : public QObject{
    Q_OBJECT
public :
    explicit EmergencyControlsViewModel(
        UdpChannel* udpChannel,
        TestBenchModel* testBenchM,
        QObject* parent = nullptr);
private :
    UdpChannel* m_udpChannel = nullptr;
    TestBenchModel* m_testBenchM = nullptr;
public slots:
    void onTestAbortion();
};

#endif // EMERGENCYCONTROLSVIEWMODEL_H
