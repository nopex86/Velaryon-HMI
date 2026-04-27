#ifndef MESSAGES_H
#define MESSAGES_H

#include <variant>
#include <cstdint>
#include <variant>
#include <string>
#include <QByteArray>
#include <QHash>
#include <QString>
#include <QObject>
#include <QMap>

class Message{
public :
    virtual ~Message() = default;
};

class ValveReading : Message {
public :
    bool status = 0;
};

class SensorReading : Message {
public :
    double value = NULL;
    QString unit;
    int decimals = 2;
    QString prefix;

    QString toDisplayString() const {
        QString v = QString::number(value, 'f', decimals);
        if (unit.isEmpty()) return prefix + v;
        return prefix + v + " " + unit;
    }
};

struct CountdownFrame{
    int32_t countdown_ms = 0;
};

using SequenceParameters = std::vector<std::tuple<
    std::string, double, std::string>>;
class SequenceFileFrame : Message {
private :

public :
    QString name;
    QString path;
    SequenceParameters parameters;
};

class AckBB : Message {
public :
    uint8_t tank = 0;
    bool enlabled = 0;
};

enum class ControlEventType {
    AckSequenceReceived,
    LaunchConfirm,
    EndTest,
};

class GlowPlugCommand : Message {
public :
    QString glowPlugName;
    bool on;
};

class ValveCommand : Message {
public :
    QString valveName;
    bool closed;
};

class TVCTestCommand : Message {
public :
    uint8_t shape;
};

class BBControlCommand : Message {
public :
    QString tankName;
    bool activated;
};

class SetPressureCommand : Message {
public :
    QString tankName;
    float pressure; // en bar
};

class SequenceCommand : Message {
public :
    QList<double> values;
};

class TestAbortionCommand : Message {};
class TestLauchConfirmation : Message {};
using Command = std::variant<
    ValveCommand,
    GlowPlugCommand,
    TVCTestCommand,
    BBControlCommand,
    SetPressureCommand,
    SequenceCommand,
    TestAbortionCommand,
    TestLauchConfirmation>;

struct ControlEvent{
    ControlEventType type;
};

class TextMessage : Message {
public :
    enum class Level { Info, Warning, Error, Debug };
    Level level = Level::Info;
    QString text;
};

struct metaData{
    std::string unit;
};

class TestBenchStatesList{
    using Rawtypes = std::variant<uint8_t, uint16_t, int16_t, uint32_t, int32_t, bool, double>;
    std::vector<std::tuple<Rawtypes, metaData>> m_valuesDatas;
    std::vector<std::string> m_valuesNames;
public :
    template<typename T>
    bool append(
        const std::string& name,
        const Rawtypes& value,
        const metaData& meta
        ){
        T valueNormalised = std::visit([](auto value){return static_cast<T>(value);}, value);
        m_valuesDatas.push_back({valueNormalised, meta});
        m_valuesNames.push_back(name);
        return true;
    }
    template<typename T>
    bool getValue(const std::string& name, T* value){
        int ID;
        for (size_t i = 0; i < m_valuesNames.size(); i++){
            if (m_valuesNames[i] == name){
                ID = i;
                *value =  std::visit(
                    [](auto v) { return static_cast<T>(v); },
                    std::get<0>(m_valuesDatas[ID])
                    );
                return true;
            }
        }
        return false;
    }
    template<typename T>
    bool getValue(size_t ID, T* value){
        if (ID >= m_valuesDatas.size()){
            return false;
        }
        *value =  std::visit(
            [](auto v) { return static_cast<T>(v); },
            std::get<0>(m_valuesDatas[ID])
            );
        return true;
    }
    bool getID(const std::string& name, size_t* ID){
        for (size_t i = 0; i < m_valuesNames.size(); i++){
            if (m_valuesNames[i] == name){
                *ID = i;
                return true;
            }
        }
        return false;
    }
};

#endif // MESSAGES_H
