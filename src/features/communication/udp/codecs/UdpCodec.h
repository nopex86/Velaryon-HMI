#ifndef UDPCODEC_H
#define UDPCODEC_H

#pragma once
#include <QString>
#include "src/core/Protocols/Messages.h"


class ProtocolCodec {
public:
    ProtocolCodec() = delete;
    using Message = std::variant<TestBenchStatesList, CountdownFrame, AckBB, TextMessage, ControlEvent>;
    // Retourne std::nullopt si le datagram ne correspond à rien
    static std::optional<Message> decode(const QByteArray& datagram);
    static QByteArray encode(const Command& command);

    static bool isSensorFrame(const QByteArray& datagram);
    static QHash<QString, int> valveID;
    static QHash<QString, int> tankID;
private:

};



#endif // PROTOCOLCODEC_H
