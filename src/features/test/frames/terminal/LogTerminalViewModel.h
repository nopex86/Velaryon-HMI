#ifndef LOGTERMINALVIEWMODEL_H
#define LOGTERMINALVIEWMODEL_H

#include <QObject>
#include "src/core/Protocols/Messages.h"

class Logger;
class UdpChannel;

class LogTerminalViewModel : public QObject {
    Q_OBJECT
public:
    explicit LogTerminalViewModel(
        Logger* logger,
        UdpChannel* udpChannel,
        QObject* parent = nullptr);
private:
    Logger* m_Logger;
    UdpChannel* m_udpChannel;
public slots:
    void onLogReceived(const TextMessage& message);
signals:
    void displayLog(TextMessage message);
};

#endif // LOGTERMINALVIEWMODEL_H
