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

class UdpWorker : public QObject
{
    Q_OBJECT

public:
    explicit UdpWorker(
        UdpLogger* udplogger,
        Logger* logger,
        QObject* parent = nullptr);
    bool decimate(int frequency);
public slots:
    void start(QHostAddress localAddr, quint16 localPort);
    void stop();

private slots:
    void processPendingDatagrams();

signals:
    void datagramRecieved(const QByteArray datagram);
    void logDatagram(const QByteArray datagram);
private:
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
