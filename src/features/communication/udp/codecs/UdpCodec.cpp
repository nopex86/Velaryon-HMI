#include "UdpCodec.h"

#include <QDataStream>
#include <QIODevice>
#include <QDebug>

QHash<QString, int> ProtocolCodec::valveID{
    {"SV11", 0},
    {"SV12", 1},
    {"SV13", 2},
    {"SV21", 5},
    {"SV22", 6},
    {"SV24", 3},
    {"SV25", 7},
    {"SV31", 8},
    {"SV32", 9},
    {"SV33", 10},
    {"SV34", 11},
    {"SV35", 12},
    {"SV36", 13},
    {"SV51", 14},
    {"SV52", 15},
    {"SV53", 16},
    {"SV61", 17},
    {"SV62", 18},
    {"SV63", 19},
    {"SV71", 4},
    {"GlowPlug", 24}
};

QHash<QString, int> ProtocolCodec::tankID{
    {"ETH", 1},
    {"LOX", 2},
    {"H2O", 6}
};

static bool hasHeader(const QByteArray& d,
                      unsigned char a,
                      unsigned char b,
                      unsigned char c,
                      unsigned char e) {
    return d.size() >= 4 &&
           (unsigned char)d[0] == a &&
           (unsigned char)d[1] == b &&
           (unsigned char)d[2] == c &&
           (unsigned char)d[3] == e;
}

bool ProtocolCodec::isSensorFrame(const QByteArray& datagram){
    return hasHeader(datagram, 0xFF, 0xFF, 0xFF, 0xFF);
}

std::optional<ProtocolCodec::Message>
ProtocolCodec::decode(const QByteArray& datagram){
    if (hasHeader(datagram, 0xFF, 0xFF, 0xFF, 0xFF)) {
        QByteArray payload = datagram.mid(4);
        QDataStream s(payload);
        s.setByteOrder(QDataStream::LittleEndian);

        TestBenchStatesList statesList;

        //Defining the data size in bytes
        uint32_t ID = 0, timing = 0;
        int16_t PS11 = 0, PS12 = 0, PS21 = 0, PS22 = 0,  PS23 = 0, PS41 = 0,
            PS42 = 0, PS61 = 0, PS62 = 0, PS63 = 0, PS64 = 0, PS71 = 0, PS81 = 0;
        int32_t PS31 = 0, PS51 = 0;
        int16_t TS11 = 0, TS12 = 0, TS41 = 0, TS42 = 0, TS61 = 0, TS62 = 0;
        uint16_t FM11 = 0, FM21 = 0, FM61 = 0;
        int32_t LC = 0;
        uint16_t ref5V = 0;
        uint16_t glowplug = 0;
        uint32_t valvesState = 0;
        uint8_t actLPos = 0, actRPos = 0;
        uint8_t actLOK = 0, actROK = 0;
        uint8_t state = 0;
        uint8_t test_step = 0;

        //Scrapping the data bytes to get the values
        s >> ID;
        s >> timing;

        s >> PS11;
        s >> PS12;
        s >> PS21;
        s >> PS22;
        s >> PS23;
        s >> PS31;
        s >> PS41;
        s >> PS42;
        s >> PS51;
        s >> PS61;
        s >> PS62;
        s >> PS63;
        s >> PS64;
        s >> PS71;
        s >> PS81;

        s >> TS11;
        s >> TS12;
        s >> TS41;
        s >> TS42;
        s >> TS61;
        s >> TS62;

        s >> FM11;
        s >> FM21;
        s >> FM61;

        s >> LC;
        s >> ref5V;
        s >> glowplug;
        s >> valvesState;

        s >> actLPos;
        s >> actRPos;
        s >> actLOK;
        s >> actROK;

        s >> state;
        s >> test_step;

        //filling the frame
        statesList.append<uint32_t>("time_ms", timing, {});

        statesList.append<uint16_t>("PS11", PS11, {});
        statesList.append<uint16_t>("PS12", PS12, {});
        statesList.append<uint16_t>("PS21", PS21, {});
        statesList.append<uint16_t>("PS22", PS22, {});
        statesList.append<uint16_t>("PS23", PS23, {});
        statesList.append<uint16_t>("PS31", PS31, {});
        statesList.append<uint16_t>("PS41", PS41, {});
        statesList.append<uint16_t>("PS42", PS42, {});
        statesList.append<uint16_t>("PS51", PS51, {});
        statesList.append<uint16_t>("PS61", PS61, {});
        statesList.append<uint16_t>("PS62", PS62, {});
        statesList.append<uint16_t>("PS63", PS63, {});
        statesList.append<uint16_t>("PS64", PS64, {});
        statesList.append<uint16_t>("PS71", PS71, {});
        statesList.append<uint16_t>("PS81", PS81, {});

        statesList.append<int16_t>("TS11", TS11, {});
        statesList.append<int16_t>("TS12", TS12, {});
        statesList.append<int16_t>("TS41", TS41, {});
        statesList.append<int16_t>("TS42", TS42, {});
        statesList.append<int16_t>("TS61", TS61, {});
        statesList.append<int16_t>("TS62", TS62, {});
        statesList.append<int16_t>("FM11", FM11, {});
        statesList.append<int16_t>("FM21", FM21, {});
        statesList.append<int16_t>("FM61", FM61, {});

        statesList.append<uint16_t>("FS01", LC, {});

        statesList.append<uint16_t>("ref5V", ref5V, {});
        statesList.append<uint16_t>("gpTension", glowplug, {});

        statesList.append<uint8_t>("SV11", (valvesState & (1 << valveID["SV11"])) != 0, {});
        statesList.append<uint8_t>("SV12", (valvesState & (1 << valveID["SV12"])) != 0, {});
        statesList.append<uint8_t>("SV13", (valvesState & (1 << valveID["SV13"])) != 0, {});
        statesList.append<uint8_t>("SV21", (valvesState & (1 << valveID["SV21"])) != 0, {});
        statesList.append<uint8_t>("SV22", (valvesState & (1 << valveID["SV22"])) != 0, {});
        statesList.append<uint8_t>("SV24", (valvesState & (1 << valveID["SV24"])) != 0, {});
        statesList.append<uint8_t>("SV25", (valvesState & (1 << valveID["SV25"])) != 0, {});
        statesList.append<uint8_t>("SV31", (valvesState & (1 << valveID["SV31"])) != 0, {});
        statesList.append<uint8_t>("SV32", (valvesState & (1 << valveID["SV32"])) != 0, {});
        statesList.append<uint8_t>("SV33", (valvesState & (1 << valveID["SV33"])) != 0, {});
        statesList.append<uint8_t>("SV34", (valvesState & (1 << valveID["SV34"])) != 0, {});
        statesList.append<uint8_t>("SV35", (valvesState & (1 << valveID["SV35"])) != 0, {});
        statesList.append<uint8_t>("SV36", (valvesState & (1 << valveID["SV36"])) != 0, {});
        statesList.append<uint8_t>("SV51", (valvesState & (1 << valveID["SV51"])) != 0, {});
        statesList.append<uint8_t>("SV52", (valvesState & (1 << valveID["SV52"])) != 0, {});
        statesList.append<uint8_t>("SV53", (valvesState & (1 << valveID["SV53"])) != 0, {});
        statesList.append<uint8_t>("SV61", (valvesState & (1 << valveID["SV61"])) != 0, {});
        statesList.append<uint8_t>("SV62", (valvesState & (1 << valveID["SV62"])) != 0, {});
        statesList.append<uint8_t>("SV63", (valvesState & (1 << valveID["SV63"])) != 0, {});
        statesList.append<uint8_t>("SV71", (valvesState & (1 << valveID["SV71"])) != 0, {});

        statesList.append<uint8_t>("GP", (valvesState & (1 << valveID["GP"])) != 0, {});

        statesList.append<uint16_t>("actLPos", actLPos, {});
        statesList.append<uint16_t>("actRPos", actRPos, {});

        statesList.append<bool>("actLOK", actLOK, {});
        statesList.append<bool>("actROK", actROK, {});


        return statesList;
    }

    else if (hasHeader(datagram, 0xEE, 0xEE, 0xFF, 0xFF)) {
        QByteArray payload = datagram.mid(4);
        QDataStream s(payload);
        s.setByteOrder(QDataStream::BigEndian);
        AckBB ack;
        uint8_t tank = 0, command = 0, header1 = 0, header2 = 0;
        s >> header1;
        s >> header2;
        qDebug() << "AckBB reçu";
        if (header1 == 0xDD && header2 == 0xDD){
            s >> tank;
            s >> command;
            ack.tank = tank;
            ack.enlabled = static_cast<bool>(command);
            qDebug() << "AckBB pris en copte";
            return ack;
        }
    }

    else if (hasHeader(datagram, 0xEE, 0xEE, 0xAA, 0xAA)) {
        return ControlEvent{ControlEventType::AckSequenceReceived};
    }

    else if (hasHeader(datagram, 0xBB, 0xBB, 0xBB, 0xBB)) {
        return ControlEvent{ControlEventType::LaunchConfirm};
    }

    else if (hasHeader(datagram, 0xAB, 0xAB, 0xAB, 0xAB)) {
        QByteArray payload = datagram.mid(4);
        QDataStream s(payload);
        s.setByteOrder(QDataStream::BigEndian);

        int32_t countdown = 0;
        s >> countdown;
        return CountdownFrame{countdown};
    }

    else if (hasHeader(datagram, 0xDD, 0xDD, 0xDD, 0xDD)) {
        TextMessage msg;
        msg.level = TextMessage::Level::Warning;
        msg.text = QString::fromUtf8(datagram.mid(4));
        return msg;
    }

    else if (hasHeader(datagram, 0xCC, 0xCC, 0xCC, 0xCC)) {
        TextMessage msg;
        msg.level = TextMessage::Level::Error;
        msg.text = QString::fromUtf8(datagram.mid(4));
        return msg;
    }

    else if (hasHeader(datagram, 0xAB, 0xCD, 0xAB, 0xCD)) {
        return ControlEvent{ControlEventType::EndTest};
    }

    return std::nullopt;
}

QByteArray ProtocolCodec::encode(const Command& command){
    QByteArray data;

    // std::visit est une manière propre de gérer les différents types du variant
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, ValveCommand>) {
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<uint8_t>(valveID[arg.valveName]));
            data.append(static_cast<uint8_t>(arg.closed ? 1 : 0));
        }
        else if constexpr (std::is_same_v<T, GlowPlugCommand>) {
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xAA));
            data.append(static_cast<char>(0xAA));
            data.append(static_cast<uint8_t>(valveID[arg.glowPlugName]));
            data.append(static_cast<uint8_t>(arg.on ? 1 : 0));
        }
        else if constexpr (std::is_same_v<T, TVCTestCommand>) {
            data.append(static_cast<char>(0xEE));
            data.append(static_cast<char>(0xEE));
            data.append(static_cast<char>(0xDD));
            data.append(static_cast<char>(0xDD));
            data.append(arg.shape);
        }
        else if constexpr (std::is_same_v<T, BBControlCommand>) {
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xDD));
            data.append(static_cast<char>(0xDD));
            data.append(static_cast<uint8_t>(tankID[arg.tankName]));
            data.append(static_cast<uint8_t>(arg.activated ? 1 : 0));
        }
        else if constexpr (std::is_same_v<T, SetPressureCommand>) {
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xFF));
            data.append(static_cast<char>(0xEE));
            data.append(static_cast<char>(0xEE));
            data.append(static_cast<uint8_t>(tankID[arg.tankName]));
            // Conversion de la pression en mbar sur 16 bits
            data.append(static_cast<uint16_t>(arg.pressure * 1000));
        }
        else if constexpr (std::is_same_v<T, SequenceCommand>) {
            data.append(static_cast<char>(0xAA));
            data.append(static_cast<char>(0xAA));
            data.append(static_cast<char>(0xAA));
            data.append(static_cast<char>(0xAA));
            for (int value : arg.values) {
                // Chaque valeur est encodée sur 16 bits
                data.append(static_cast<uint16_t>(value));
            }
        }
        else if constexpr (std::is_same_v<T, TestAbortionCommand>) {
            data.append(static_cast<char>(0xCC));
            data.append(static_cast<char>(0xCC));
            data.append(static_cast<char>(0xCC));
            data.append(static_cast<char>(0xCC));
        }
        else if constexpr (std::is_same_v<T, TestLauchConfirmation>) {
            data.append(static_cast<char>(0xBB));
            data.append(static_cast<char>(0xBB));
            data.append(static_cast<char>(0xBB));
            data.append(static_cast<char>(0xBB));
        }
    }, command);
    return data;
}



