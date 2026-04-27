#ifndef INITIALISEVALVEBUTTONVIEWMODEL_H
#define INITIALISEVALVEBUTTONVIEWMODEL_H

#include <QObject>

class UdpChannel;

class InitialiseValveButtonViewModel : public QObject {
    Q_OBJECT
public :
    explicit InitialiseValveButtonViewModel(
        UdpChannel* udpChannel,
        QObject* parent = nullptr);
public slots:
    void initialiseValve();
private :
    UdpChannel* m_udpChannel = nullptr;
};

#endif // INITIALISEVALVEBUTTONVIEWMODEL_H
