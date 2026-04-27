#include "UdpChannelParametersViewModel.h"
#include "../UdpChannel.h"

UdpChannelParametersViewModel::UdpChannelParametersViewModel(
    UdpChannel* udpChannel, QObject* parent) :
    QObject(parent), m_udpChannel(udpChannel)
{
    m_EndpointPort = m_udpChannel->localPort();
    m_EndpointAdress = m_udpChannel->localAddr().toString();
    m_TargetPort = m_udpChannel->remotePort();
    m_TargetAdress = m_udpChannel->remoteAddr().toString();
}

QString UdpChannelParametersViewModel::EndpointPort(){
    return QString::number(m_EndpointPort);
}
void UdpChannelParametersViewModel::setEndpointPort(uint16_t port){
    m_EndpointPort = port;
    emit AdressParametersChanged();
}
QString UdpChannelParametersViewModel::EndpointAdress(){
    return m_EndpointAdress;
}
void UdpChannelParametersViewModel::setEndpointAdress(const QString& adress){
    m_EndpointAdress = adress;
    emit AdressParametersChanged();
}
QString UdpChannelParametersViewModel::TargetPort(){
    return QString::number(m_TargetPort);
}
void UdpChannelParametersViewModel::setTargetPort(uint16_t port){
    m_TargetPort = port;
    emit AdressParametersChanged();
}
QString UdpChannelParametersViewModel::TargetAdress(){
    return m_TargetAdress;
}
void UdpChannelParametersViewModel::setTargetAdress(const QString& adress){
    m_TargetAdress = adress;
    emit AdressParametersChanged();
}
void UdpChannelParametersViewModel::restartEndpoint(){
    qDebug() << "begin restart";
    m_udpChannel->stopEndpoint();
    qDebug() << "endpoint stopped";
    m_udpChannel->setLocalAddr(QHostAddress(m_EndpointAdress));
    m_udpChannel->setLocalPort(m_EndpointPort);
    m_udpChannel->setRemoteAddr(QHostAddress(m_TargetAdress));
    m_udpChannel->setRemotePort(m_TargetPort);
    qDebug() << "target changed";
    m_udpChannel->startEndpoint();
    qDebug() << "end restart";
}
