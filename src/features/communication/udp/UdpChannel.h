#ifndef UDPCHANNEL_H
#define UDPCHANNEL_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include "src/core/Protocols/Messages.h"
#include "frames_logger/UdpLogger.h"

class UdpWorker;
class Logger;
class FileSystem;

class UdpChannel : public QObject
{
    Q_OBJECT

public:
    explicit UdpChannel(
        FileSystem* fileSystem,
        Logger* logger,
        QObject* parent = nullptr);
    ~UdpChannel();

    void startEndpoint();
    void stopEndpoint();
    void sendData(const Command& command);

    bool running();

    QHostAddress remoteAddr() const;
    quint16 remotePort() const;
    QHostAddress localAddr() const;
    quint16 localPort() const;
    void setRemoteAddr(const QHostAddress& addr);
    void setRemotePort(quint16 port);
    void setLocalAddr(const QHostAddress& addr);
    void setLocalPort(quint16 port);

    int loggRateHz();
    int frameLossRateHz();

public slots :
    void onDatagramReceived(const QByteArray& datagram);
signals:
    void startUdpWorker(QHostAddress, quint16);
    void stopUdpWorker();

    void StatesListReceived(const TestBenchStatesList& list);
    void AckBBReceived(const AckBB& ack);
    void textMessageReceived(const TextMessage& msg);
    void controlEventReceived(const ControlEvent& event);
    void countdownReceived(const CountdownFrame& frame);

private:
    QThread m_udpWorkerThread;
    UdpWorker* m_udpWorker;
    QUdpSocket m_udpSocket;
    QHostAddress m_remoteAddr;
    quint16 m_remotePort;
    QHostAddress m_localAddr;
    quint16 m_localPort;

    FileSystem* m_fileSystem;
    Logger* m_logger;
    UdpLogger* m_udpLogger;
    int m_lastRefresh = 0;
    int m_periodOfRefresh = 0;
    bool m_running;
};

#endif // UDPCHANNEL_H
