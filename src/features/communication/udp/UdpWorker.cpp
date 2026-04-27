#include "UdpWorker.h"
#include "codecs/UdpCodec.h"
#include "src/services/Logger/Logger.h"
#include <QDebug>
#include <cstdint>

UdpWorker::UdpWorker(UdpLogger* udplogger,
                     Logger* logger,
                     QObject* parent)
    : QObject(parent), m_udplogger(udplogger), m_logger(logger)
{

    m_lastFrameSend = Clock::now();
}

void UdpWorker::start(QHostAddress localAddr, quint16 localPort)
{
    socket = new QUdpSocket(this);

    if (!socket->bind(localAddr, localPort)) {
        m_logger->log(
            TextMessage::Level::Warning,
            "Failed to bind UDP socket to " + localAddr.toString() + ":" + QString::number(localPort));
        return;
    }
    connect(socket, &QUdpSocket::readyRead,
            this, &UdpWorker::processPendingDatagrams);
}

void UdpWorker::stop()
{
    if (socket) {
        socket->close();
    }
}

bool UdpWorker::decimate(int frequency){
    TimePoint now = Clock::now();

    if (now - m_lastFrameSend >= std::chrono::microseconds(1'000'000UL / frequency)) {
        m_lastFrameSend = now;
        return false;
    }
    return true;
}

void UdpWorker::processPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

        if (!ProtocolCodec::isSensorFrame(datagram)){
            emit datagramRecieved(datagram);
        }
        else {
            if (!decimate(60)){
                emit datagramRecieved(datagram);
            }
            m_udplogger->log(
                reinterpret_cast<uint8_t*>(datagram.data()),
                datagram.size());
        }
    }
}

