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
 * @brief UDP Communicaton channel between the microcontroler and the HMI
 * @ingroup UdpChannel
 *
 * @details Udp channel as for objective to provide a reliable UDP interface
 * to comunicate with foreign devices (teensy being an exemple).
 * Functions :
 *  - send data via UDP
 *  - receive data via UDP
 *  - dispatch various messages comming from devices to the rest of the system
 *
 *  @note The UDP worker uses  Qt libraries for the socket and for the thread.
 *  It would be nice if it was changed.
 */
class UdpChannel : public QObject
{
    Q_OBJECT

public:
    explicit UdpChannel(FileSystem *fileSystem, Logger *logger,
                        QObject *parent = nullptr);
    ~UdpChannel();

    /**
   * @brief Start UDP channel and his subsystems
   *
   * @details Begin to start the UDP logger (to log the telemetry frames comming
   * at high frequency from others devices), start the UDP worker and send the
   * first message to the distant device in order for it to begin sending the
   * telemetry frames.
   */
    void startEndpoint();

    /**
   * @brief Stop UDP endpoint and his subsystems
   *
   * @details Stop UDP worker and UDP logger.
   */
    void stopEndpoint();

    /**
   * @brief Send data via UDP to other devices
   * @param command Struct contenant diverses instruction qui seront converties
   * en trames puis envoyés.
   */
    void sendData(const Command &command);

    /**
   * @brief Returns UDP channel status
   * @return true if UDP channel is running, false if not
   */
    bool running();

    QHostAddress remoteAddr() const;
    quint16 remotePort() const;
    QHostAddress localAddr() const;
    quint16 localPort() const;
    void setRemoteAddr(const QHostAddress &addr);
    void setRemotePort(quint16 port);
    void setLocalAddr(const QHostAddress &addr);
    void setLocalPort(quint16 port);

    /**
   * @brief Return the rate of telemetry frames being logged by the UDP logger
   * @return logging rate in Hertz.
   */
    int loggRateHz();

    /**
   * @brief Return the rate of telemetry trames being ditched by the UDP logger
   * when buffers are full.
   * @return ditching rate in Hertz.
   */
    int frameLossRateHz();

public slots :

    /**
     * @brief Decode and dispatch the data received via UDP for it to be used
     * in the entire program.
     * @param datagram contain the bytes comming from the UDP socket waiting to
     * be decoded.
     */
    void onDatagramReceived(const QByteArray& datagram);
signals:

    /**
     * @brief Signal to the UDP worker that it should start.
     *
     * @param remoteHostAdress IP adress of the remote host.
     * @param remoteHostPort Designated remote port.
     */
    void startUdpWorker(QHostAddress remoteHostAdress, quint16 remoteHostPort);

    /**
     * @brief Signal to the UDP worker that it should stop.
     */
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
