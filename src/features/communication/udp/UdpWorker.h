#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <chrono>
#include "frames_logger/UdpLogger.h"

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

class ProtocolCodec;
class Logger;
struct SensorFrame;
class TextMessage;
struct ControlEvent;
struct CountdownFrame;

/**
 * @file UdpWorker.h
 * @brief UDP socket worker running on a dedicated thread.
 * @ingroup Network
 */

/**
 * @brief UDP socket worker running on a dedicated thread.
 * @ingroup Network
 *
 * @details UdpWorker owns and drives a QUdpSocket from within a QThread,
 * keeping all blocking I/O off the caller's thread. Responsibilities:
 *  - Bind the socket and receive incoming UDP datagrams.
 *  - Log every telemetry frame via UdpLogger.
 *  - Decimate telemetry frames to 60 Hz before forwarding them.
 *  - Forward raw datagrams to the parent thread via Qt queued signals.
 *
 * @par Threading model
 * This object must be moved to a QThread via @c moveToThread() before
 * @c start() is called. All signals are emitted across the thread boundary
 * using Qt::QueuedConnection.
 */
class UdpWorker : public QObject
{
    Q_OBJECT

public:
    explicit UdpWorker(
        UdpLogger* udplogger,
        Logger* logger,
        QObject* parent = nullptr);
public slots:
    /**
     * @brief Bind the socket and begin receiving datagrams.
     *
     * @details Binds the UDP socket to @p localAddr : @p localPort, then
     * connects the socket's @c readyRead signal to processPendingDatagrams().
     * Must be called from within the worker thread.
     *
     * @param localAddr Local address to bind the socket to.
     * @param localPort Local port to bind the socket to.
     */
    void start(QHostAddress localAddr, quint16 localPort);

    /**
     * @brief Close the socket and stop receiving datagrams.
     */
    void stop();

private slots:
    /**
     * @brief Drain and process all datagrams pending on the socket.
     *
     * @details Called every time the socket emits @c readyRead.
     * For each pending datagram:
     *  - Unconditionally logs it via UdpLogger.
     *  - Applies 60 Hz decimation for telemetry and state frames.
     *  - Emits datagramRecieved() for frames that pass decimation.
     */
    void processPendingDatagrams();

signals:
    /**
     * @brief Emitted when a datagram has passed logging and decimation.
     *
     * @details Connected across the thread boundary to
     * UdpChannel::onDatagramReceived() via Qt::QueuedConnection.
     *
     * @param datagram Raw bytes of the received datagram.
     */
    void datagramRecieved(const QByteArray datagram);
private:
    /**
     * @brief Decimation gate — returns @c true at most once per period.
     * @param frequency Maximum pass-through rate in Hz.
     * @return @c true if the frame should be forwarded, @c false otherwise.
     */
    bool decimate(int frequency);
    QUdpSocket* socket = nullptr;
    TimePoint m_lastFrameSend;
    UdpLogger* m_udplogger;
    Logger* m_logger;
};

#endif // UDPWORKER_H

// // udp_worker.hpp
// class UdpWorker : public QObject {
//     Q_OBJECT
// public:
//     explicit UdpWorker(ProtocolEngine* engine,
//                        SensorStore*    store,
//                        FrameLogger*    logger,
//                        QObject* parent = nullptr);

// public slots:
//     void start();   // appelé depuis le worker thread
//     void stop();
//     void sendCommand(QByteArray frame); // slot thread-safe via queued connection

// private slots:
//     void onReadyRead();

// private:
//     QUdpSocket*      m_socket{nullptr};
//     ProtocolEngine*  m_engine;
//     SensorStore*     m_store;
//     FrameLogger*     m_logger;
//     std::atomic_bool m_running{false};
// };
