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

/**
 * @file UdpChannel.h
 * @brief UDP communication channel between the microcontroller and the HMI.
 * @ingroup Network
 */

/**
 * @brief UDP communication channel between the microcontroller and the HMI.
 * @ingroup Network
 *
 * @details UdpChannel provides a reliable UDP interface to communicate with
 * remote embedded devices (e.g. a Teensy microcontroller). Responsibilities:
 *  - Send command frames via UDP.
 *  - Receive and decode incoming UDP datagrams.
 *  - Dispatch decoded messages to the rest of the system via Qt signals.
 *  - Log incoming telemetry frames at high frequency via UdpLogger.
 */
class UdpChannel : public QObject
{
    Q_OBJECT

public:
    explicit UdpChannel(FileSystem *fileSystem, Logger *logger,
                        QObject *parent = nullptr);
    ~UdpChannel();

    /**
     * @brief Start the UDP channel and its subsystems.
     *
     * @details Initializes and starts the UdpLogger, launches the UdpWorker
     * on its dedicated thread, then sends an initial handshake frame to the
     * remote device to trigger telemetry streaming.
     */
    void startEndpoint();

    /**
     * @brief Stop the UDP channel and its subsystems.
     *
     * @details Gracefully stops the UdpWorker and the UdpLogger.
     */
    void stopEndpoint();

    /**
     * @brief Send a command to the remote device via UDP.
     * @param command Command structure to be serialized and transmitted.
     */
    void sendData(const Command &command);

    /**
     * @brief Returns whether the UDP channel is currently active.
     * @return @c true if the channel is running, @c false otherwise.
     */
    bool running();

    /** @brief Returns the remote host address. */
    QHostAddress remoteAddr() const;

    /** @brief Returns the remote host port. */
    quint16 remotePort() const;

    /** @brief Returns the local bind address. */
    QHostAddress localAddr() const;

    /** @brief Returns the local bind port. */
    quint16 localPort() const;

    /** @brief Sets the remote host address. @param addr Target IP address. */
    void setRemoteAddr(const QHostAddress &addr);

    /** @brief Sets the remote host port. @param port Target port number. */
    void setRemotePort(quint16 port);

    /** @brief Sets the local bind address. @param addr Local IP address. */
    void setLocalAddr(const QHostAddress &addr);

    /** @brief Sets the local bind port. @param port Local port number. */
    void setLocalPort(quint16 port);

    /**
     * @brief Returns the telemetry frame logging rate.
     * @return Logging rate in Hz.
     */
    int loggRateHz();

    /**
     * @brief Returns the frame loss rate when the logger buffer is full.
     * @return Frame loss rate in Hz.
     */
    int frameLossRateHz();

public slots :

    /**
     * @brief Decode and dispatch an incoming UDP datagram.
     *
     * @details Parses the binary frame header to identify the message type,
     * deserializes the payload, and emits the corresponding signal.
     *
     * @param datagram Raw bytes received from the UDP socket.
     */
    void onDatagramReceived(const QByteArray& datagram);
signals:

    /**
     * @brief Instructs the UdpWorker to start listening.
     * @param remoteHostAdress IP address of the remote device.
     * @param remoteHostPort   Port of the remote device.
     */
    void startUdpWorker(QHostAddress remoteHostAdress, quint16 remoteHostPort);

    /** @brief Instructs the UdpWorker to stop. */
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
