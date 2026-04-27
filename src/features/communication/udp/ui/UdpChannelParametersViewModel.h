#ifndef UDPCHANNELPARAMETERSVIEWMODEL_H
#define UDPCHANNELPARAMETERSVIEWMODEL_H

#include <QObject>
class UdpChannel;

class UdpChannelParametersViewModel : public QObject{
    Q_OBJECT
public :
    explicit UdpChannelParametersViewModel(
        UdpChannel* udpChannel, QObject* parent = nullptr);
    QString EndpointPort();
    void setEndpointPort(uint16_t port);
    QString EndpointAdress();
    void setEndpointAdress(const QString& adress);
    QString TargetPort();
    void setTargetPort(uint16_t port);
    QString TargetAdress();
    void setTargetAdress(const QString& adress);
    void restartEndpoint();
private :
    uint16_t m_EndpointPort;
    QString m_EndpointAdress;
    uint16_t m_TargetPort;
    QString m_TargetAdress;
    UdpChannel* m_udpChannel;
signals :
    void AdressParametersChanged();
};

#endif // UDPCHANNELPARAMETERSVIEWMODEL_H
