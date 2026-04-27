#include "LogTerminalViewModel.h"
#include "src/services/Logger/Logger.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "src/core/Protocols/Messages.h"
#include <QDebug>

LogTerminalViewModel::LogTerminalViewModel(
    Logger* logger,
    UdpChannel* udpChannel,
    QObject* parent):
    QObject(parent),
    m_Logger(logger),
    m_udpChannel(udpChannel)
{
    connect(m_Logger, &Logger::messageLogged,
            this, &LogTerminalViewModel::onLogReceived);
    connect(m_udpChannel, &UdpChannel::textMessageReceived,
            this, &LogTerminalViewModel::onLogReceived);
}

void LogTerminalViewModel::onLogReceived(const TextMessage& message)
{
    emit displayLog(message);
}
