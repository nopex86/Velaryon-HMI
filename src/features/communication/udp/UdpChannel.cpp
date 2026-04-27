#include "UdpChannel.h"
#include "UdpWorker.h"
#include "codecs/UdpCodec.h"
#include "src/services/FileSystem/FileSystem.h"
#include <QDebug>
#include <QTimer>
#include <QTime>


UdpChannel::UdpChannel(
    FileSystem* fileSystem,
    Logger* logger,
    QObject* parent):
    QObject(parent),
    m_fileSystem(fileSystem), m_logger(logger)
{
    setLocalAddr(QHostAddress("192.168.0.101"));
    setLocalPort(12345);
    setRemoteAddr(QHostAddress("192.168.0.100"));
    setRemotePort(5190);

    std::string path;
    if (!m_fileSystem->getDirectory("statesDatas", &path)){
        qDebug() << "File : <<statesDatas>> does not exist";
    }
    qDebug() << path;
    m_udpLogger = new UdpLogger(path, m_logger);
    m_udpWorker = new UdpWorker(m_udpLogger, m_logger);
    m_udpWorker->moveToThread(&m_udpWorkerThread);

    connect(&m_udpWorkerThread, &QThread::finished,
            m_udpWorker, &QObject::deleteLater);

    connect(this, &UdpChannel::startUdpWorker,
            m_udpWorker, &UdpWorker::start);

    connect(this, &UdpChannel::stopUdpWorker,
            m_udpWorker, &UdpWorker::stop);

    connect(m_udpWorker, &UdpWorker::datagramRecieved,
            this, &UdpChannel::onDatagramReceived);

    m_udpWorkerThread.start();
}


int UdpChannel::loggRateHz(){
    int now = QTime::currentTime().msec();
    m_periodOfRefresh = now - m_lastRefresh;
    m_lastRefresh = now;
    return m_udpLogger->cyclesCount() * 1000.0 / m_periodOfRefresh;
}
int UdpChannel::frameLossRateHz(){
    return m_udpLogger->droppedFramesCount() * 1000.0 / m_periodOfRefresh;
}

UdpChannel::~UdpChannel()
{
    qDebug() << "UdpChannel destroyed !";
    stopEndpoint();
    m_udpWorkerThread.quit();
    m_udpWorkerThread.wait();
}

void UdpChannel::setRemoteAddr(const QHostAddress& addr) { m_remoteAddr = addr; }
void UdpChannel::setRemotePort(quint16 port) { m_remotePort = port; }
void UdpChannel::setLocalAddr(const QHostAddress& addr) { m_localAddr = addr; }
void UdpChannel::setLocalPort(quint16 port) {
    qDebug() << "local initialised";
    m_localPort = port; }

QHostAddress UdpChannel::remoteAddr() const { return m_remoteAddr; }
quint16 UdpChannel::remotePort() const { return m_remotePort; }
QHostAddress UdpChannel::localAddr() const { return m_localAddr; }
quint16 UdpChannel::localPort() const {
    qDebug() << "m_localPort";
    return m_localPort; }

void UdpChannel::startEndpoint()
{
    m_running = true;
    m_udpLogger->start();
    emit startUdpWorker(m_localAddr, m_localPort);

    QByteArray data;
    data.append(char(0x00));

    m_udpSocket.writeDatagram(data, m_remoteAddr, m_remotePort);
}

void UdpChannel::stopEndpoint()
{
    emit stopUdpWorker();
    m_udpLogger->stop();
    m_running = false;
}

void UdpChannel::sendData(const Command& command) {
    QByteArray data = ProtocolCodec::encode(command);
    m_udpSocket.writeDatagram(data, m_remoteAddr, m_remotePort);
    qDebug() << data;
}

bool UdpChannel::running(){return m_running;}

void UdpChannel::onDatagramReceived(const QByteArray& datagram){
    auto decoded = ProtocolCodec::decode(datagram);
    if (!decoded)
        return;

    std::visit([this](const auto& msg) {
        using T = std::decay_t<decltype(msg)>;

        if constexpr (std::is_same_v<T, TestBenchStatesList>)
            emit StatesListReceived(msg);
        else if constexpr (std::is_same_v<T, AckBB>)
            emit AckBBReceived(msg);
        else if constexpr (std::is_same_v<T, TextMessage>)
            emit textMessageReceived(msg);
        else if constexpr (std::is_same_v<T, ControlEvent>)
            emit controlEventReceived(msg);
        else if constexpr (std::is_same_v<T, CountdownFrame>)
            emit countdownReceived(msg);

    }, *decoded);
}
